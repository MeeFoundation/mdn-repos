use crate::common::mdn_node::{create_data_owner_node, create_provider_node};
use futures::StreamExt;
use mee_data_sync::{
    error::MeeDataSyncResult,
    mdn::{
        common::{network::MdnAgentDataNodeNetworkOps, user::MdnAgentDataNodeUserOps},
        provider_agent::delegation::manager::{
            ImportCapabilitiesForDataOwner, ImportCapabilitiesFromProvider,
        },
    },
    willow::debug::progress_session_intents,
};
use std::time::Duration;
use tokio::{select, time::sleep};

#[tokio::test]
async fn local_wallet_write_caps() -> anyhow::Result<()> {
    let _ = env_logger::Builder::new()
        .filter_level(log::LevelFilter::Info)
        .filter_module("iroh_net", log::LevelFilter::Warn)
        .filter_module("tracing::span", log::LevelFilter::Warn)
        .try_init();

    let oyt_mdn_node = create_provider_node("oyt node").await?;
    let oyt_peer_id = oyt_mdn_node.user_id().await?;
    let oyt_node_ticket = oyt_mdn_node.network_node_ticket().await?;

    let untied_mdn_node = create_provider_node("untied node").await?;
    let untied_peer_id = untied_mdn_node.user_id().await?;
    let untied_node_ticket = untied_mdn_node.network_node_ticket().await?;

    let alice_wallet_node = create_data_owner_node("alice wallet node").await?;
    let alice_peer_id = alice_wallet_node.user_id().await?;
    let alice_node_ticket = alice_wallet_node.network_node_ticket().await?;

    let alice_user_id = "alice";
    let address_attribute = "address";
    let address_sub_attribute_city = "city";
    let address_sub_attribute_zip = "zip";
    let alice_city = "Rome";
    let alice_zip = "123";

    let alice_address_path = format!("{alice_user_id}/{address_attribute}");
    let alice_city_path = format!("{alice_address_path}/0/{address_sub_attribute_city}");
    let alice_zip_path = format!("{alice_address_path}/0/{address_sub_attribute_zip}");

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&alice_city_path, alice_city.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&alice_zip_path, alice_zip.as_bytes().to_vec())
        .await?;

    let caps = alice_wallet_node
        .mdn_delegation_manager
        .share_cap_list_with_provider(oyt_peer_id)
        .await?;

    // import capability with a right to populate data owner cap list for oyt provider
    oyt_mdn_node
        .mdn_delegation_manager()
        .import_cap_list_from_data_owner(ImportCapabilitiesForDataOwner {
            data_owner_node_ticket: alice_node_ticket.to_string(),
            caps,
        })
        .await?;

    let caps = alice_wallet_node
        .mdn_delegation_manager
        .share_cap_list_with_provider(untied_peer_id)
        .await?;

    // import capability with a right to populate data owner cap list for untied provider
    untied_mdn_node
        .mdn_delegation_manager()
        .import_cap_list_from_data_owner(ImportCapabilitiesForDataOwner {
            data_owner_node_ticket: alice_node_ticket.to_string(),
            caps,
        })
        .await?;

    // share read access with untied
    let cap_for_untied = oyt_mdn_node
        .mdn_delegation_manager()
        .delegate_read_access_to_provider(&alice_address_path, untied_peer_id)
        .await?;

    let caps = ImportCapabilitiesFromProvider {
        provider_node_ticket: oyt_node_ticket.to_string(),
        caps: cap_for_untied,
    };

    let sync_event_stream = untied_mdn_node
        .mdn_delegation_manager()
        .import_capabilities_from_provider(caps)
        .await?;

    let privileged_access_from_oyt = oyt_mdn_node
        .mdn_delegation_manager()
        .delegate_privileged_access_to_owner(oyt_node_ticket.to_string(), alice_peer_id)
        .await?;

    let privileged_access_from_untied = untied_mdn_node
        .mdn_delegation_manager()
        .delegate_privileged_access_to_owner(untied_node_ticket.to_string(), alice_peer_id)
        .await?;

    alice_wallet_node
        .mdn_delegation_manager
        .import_privileged_access_from_provider(privileged_access_from_oyt)
        .await?;

    alice_wallet_node
        .mdn_delegation_manager
        .import_privileged_access_from_provider(privileged_access_from_untied)
        .await?;

    let untied_handler = tokio::spawn(progress_session_intents(sync_event_stream));

    let wallet_handler = tokio::spawn(async move {
        loop {
            let res: Vec<_> = untied_mdn_node
                .mdn_data_store()
                .get_all_values_stream()
                .await?
                .collect()
                .await;

            if res.len() > 0 {
                log::warn!("untied res: {res:#?}");
                break;
            }

            sleep(Duration::from_secs(1)).await;
        }

        loop {
            let mut cap_list = alice_wallet_node
                .mdn_delegation_manager
                .data_owner_cap_list()
                .await?;

            if let Some(cap) = cap_list.pop() {
                alice_wallet_node
                    .mdn_delegation_manager
                    .revoke_shared_access_from_provider(cap)
                    .await?;

                break;
            }

            sleep(Duration::from_secs(1)).await;
        }

        loop {
            let res: Vec<_> = untied_mdn_node
                .mdn_data_store()
                .get_all_values_stream()
                .await?
                .collect()
                .await;

            let oyt_delegated_caps = oyt_mdn_node
                .mdn_delegation_manager()
                .delegated_caps()
                .await?;

            if res.len() == 0
                && oyt_mdn_node
                    .mdn_delegation_manager()
                    .is_revocation_list_empty()
                    .await?
                && oyt_delegated_caps.is_empty()
            {
                break;
            }

            sleep(Duration::from_secs(1)).await;
        }

        loop {
            let cap_list = alice_wallet_node
                .mdn_delegation_manager
                .data_owner_cap_list()
                .await?;

            if cap_list.len() == 0 {
                break;
            }

            sleep(Duration::from_secs(1)).await;
        }

        MeeDataSyncResult::Ok(())
    });

    select! {
        r = untied_handler => {
            r?;
        },
        r = wallet_handler => {
            r??;
        },
    }

    Ok(())
}
