use crate::common::{
    mdn_node::{create_data_owner_node, create_provider_node},
    utils::progress_session_intents,
};
use mee_data_sync::mdn::{
    provider::delegation::manager::{
        ImportCapabilitiesForDataOwner, ImportCapabilitiesFromProvider,
    },
    traits::{network::MdnAgentDataNodeNetworkOps, user::MdnAgentDataNodeUserOps},
};

#[tokio::test]
async fn local_wallet_write_caps() -> anyhow::Result<()> {
    env_logger::Builder::new()
        .filter_level(log::LevelFilter::Info)
        .filter_module("iroh_net", log::LevelFilter::Warn)
        .filter_module("tracing::span", log::LevelFilter::Warn)
        .init();

    let oyt_mdn_node = create_provider_node("oyt node").await?;
    let oyt_peer_id = oyt_mdn_node.user_id().await?;
    let oyt_node_ticket = oyt_mdn_node.network_node_ticket().await?;

    let untied_mdn_node = create_provider_node("untied node").await?;
    let untied_peer_id = untied_mdn_node.user_id().await?;

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
        .set_value(&alice_city_path, alice_city.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
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
            node_ticket: alice_node_ticket.to_string(),
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
            node_ticket: alice_node_ticket.to_string(),
            caps,
        })
        .await?;

    // share read access with untied
    let cap_for_untied = oyt_mdn_node
        .mdn_delegation_manager()
        .delegate_read_access_to_provider(&alice_address_path, untied_peer_id)
        .await?;

    let caps = ImportCapabilitiesFromProvider {
        node_ticket: oyt_node_ticket.to_string(),
        caps: cap_for_untied,
    };

    let sync_event_stream = untied_mdn_node
        .mdn_delegation_manager()
        .import_capabilities_from_provider(caps)
        .await?;

    let untied_handler = tokio::spawn(progress_session_intents(sync_event_stream));

    Ok(())
}
