use crate::common::{mdn_node::create_node, utils::progress_session_intents};
use anyhow::anyhow;
use futures::{future::join_all, StreamExt};
use mee_data_sync::mdn::provider::delegation::{
    ImportCapabilitiesFromProvider, MdnAgentProviderNodeDelegation,
};
use std::time::Duration;
use tokio::{sync::mpsc, time::sleep};

#[tokio::test]
async fn local_wallet_write_caps() -> anyhow::Result<()> {
    env_logger::Builder::new()
        .filter_level(log::LevelFilter::Info)
        .filter_module("iroh_net", log::LevelFilter::Warn)
        .filter_module("tracing::span", log::LevelFilter::Warn)
        .init();

    let oyt_mdn_node = create_node("oyt node").await?;
    let oyt_node_ticket = oyt_mdn_node.network_node_ticket().await?;

    let untied_mdn_node = create_node("untied node").await?;
    let untied_peer_id = untied_mdn_node.user_id().await?;

    let alice_wallet_node = create_node("alice wallet node").await?;
    let alice_peer_id = alice_wallet_node.user_id().await?;

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

    // let cap_for_alice = oyt_mdn_node
    //     .mdn_delegation_manager()
    //     .delegate_full_access_to_owner(alice_peer_id)
    //     .await?;

    // let caps = ImportCapabilitiesForDataOwner {
    //     node_ticket: oyt_node_ticket.to_string(),
    //     caps: String::new(),
    // };

    // let sync_event_stream = untied_mdn_node
    //     .mdn_delegation_manager()
    //     .import_capabilities_for_data_owner(caps)
    //     .await?;

    // let alice_handler = tokio::spawn(progress_session_intents(sync_event_stream));

    Ok(())
}
