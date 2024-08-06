use std::time::Duration;

use futures::StreamExt;
use iroh_willow::{
    auth::{DelegateTo, RestrictArea},
    proto::{grouping::Area, meadowcap::AccessMode},
    session::intents::EventKind,
};
use mee_data_sync::{
    mdn::agent_data_node::{
        MdnAgentDataNodeDelegation, MdnAgentDataNodeNetwork, MdnAgentDataNodeStore,
        MdnAgentDataNodeUser, MdnAgentDataNodeWillowImpl,
    },
    willow::peer::{delegation_manager::ImportCapabilitiesFromRemotePeer, WillowPeer},
};
use rand_chacha::{rand_core::SeedableRng, ChaCha12Rng};
use tokio::select;

pub fn create_rng(seed: &str) -> ChaCha12Rng {
    let seed = iroh_base::hash::Hash::new(seed);
    ChaCha12Rng::from_seed(*(seed.as_bytes()))
}

#[tokio::test]
async fn data_write_data_read() -> anyhow::Result<()> {
    env_logger::Builder::new()
        .filter_level(log::LevelFilter::Info)
        .filter_module("iroh_net", log::LevelFilter::Warn)
        .filter_module("tracing::span", log::LevelFilter::Warn)
        .init();

    let mut rng = create_rng("oyt node");
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;
    let provider_id = "oyt";

    let oyt_mdn_node =
        MdnAgentDataNodeWillowImpl::new(willow_peer, provider_id.to_string()).await?;

    let user_id = "alice";
    let attribute_name = "address";
    let sub_attribute_path = ["city"];
    let city = "Rome";

    let city_record_key =
        oyt_mdn_node.make_entry_path(user_id, attribute_name, &sub_attribute_path)?;

    oyt_mdn_node
        .set_user_data(
            user_id,
            attribute_name,
            &sub_attribute_path,
            city.as_bytes().to_vec(),
        )
        .await?;

    let res = oyt_mdn_node
        .get_user_data(user_id, attribute_name, &sub_attribute_path)
        .await?
        .pop()
        .unwrap();

    assert_eq!(res.value, city.as_bytes());
    assert_eq!(res.key, city_record_key);

    // Untied node
    let mut rng = create_rng("untied node");
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;
    let provider_id = "untied";

    let untied_mdn_node =
        MdnAgentDataNodeWillowImpl::new(willow_peer, provider_id.to_string()).await?;

    // The ID actually comes with a first Untied request to OYT after MDS discovery process
    let untied_willow_node_user_id = untied_mdn_node.user_id().await?;

    let oyt_data_subset_restriction = RestrictArea::Restrict(Area::path(city_record_key.clone()));

    let cap_for_untied = oyt_mdn_node
        .delegate_capabilities(
            AccessMode::ReadOnly,
            DelegateTo::new(untied_willow_node_user_id, RestrictArea::None),
        )
        .await?;

    let oyt_node_ticket = oyt_mdn_node.network_node_ticket().await?;

    let caps = ImportCapabilitiesFromRemotePeer {
        node_ticket: oyt_node_ticket.to_string(),
        caps: cap_for_untied,
    };

    let mut sync_event_stream = untied_mdn_node
        .import_capabilities_from_remote_peer(caps)
        .await?;

    loop {
        select! {
            ev = sync_event_stream.next() => {
                log::info!("ev: {ev:#?}");
                if let Some(EventKind::ReconciledAll) = &ev {
                    break;
                }
                if ev.is_none() {
                    break;
                }
            },
            _ = tokio::time::sleep(Duration::from_secs(1)) => {},
        }
    }

    let res = untied_mdn_node
        .get_user_data(user_id, attribute_name, &sub_attribute_path)
        .await?
        .pop()
        .unwrap();

    assert_eq!(res.value, city.as_bytes());
    assert_eq!(res.key, city_record_key);

    Ok(())
}
