use anyhow::anyhow;
use futures::{StreamExt, TryFutureExt};
use iroh_willow::{
    auth::{DelegateTo, RestrictArea},
    proto::{grouping::Area, meadowcap::AccessMode},
    session::intents::IntentHandle,
};
use mee_data_sync::{
    mdn::{
        agent_data_node::MdnAgentDataNodeWillowImpl,
        traits::{
            MdnAgentDataNodeDelegation, MdnAgentDataNodeNetwork, MdnAgentDataNodeStore,
            MdnAgentDataNodeUser,
        },
    },
    willow::peer::{delegation_manager::ImportCapabilitiesFromRemotePeer, WillowPeer},
};
use rand_chacha::{rand_core::SeedableRng, ChaCha12Rng};
use std::time::Duration;
use tokio::select;

pub fn create_rng(seed: &str) -> ChaCha12Rng {
    let seed = iroh_base::hash::Hash::new(seed);
    ChaCha12Rng::from_seed(*(seed.as_bytes()))
}

async fn progress_session_intents(mut sync_event_stream: IntentHandle) {
    loop {
        select! {
            _ev = sync_event_stream.next() => {},
            _ = tokio::time::sleep(Duration::from_secs(1)) => {},
        }
    }
}

#[tokio::test]
async fn two_provider_nodes_sync() -> anyhow::Result<()> {
    // iroh_test::logging::setup_multithreaded();
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
    let address_attribute = "address";
    let address_sub_attribute_city = ["city"];
    let address_sub_attribute_zip = ["zip"];
    let city = "Rome";
    let zip = "123";

    let city_record_key =
        oyt_mdn_node.make_entry_path(user_id, address_attribute, &address_sub_attribute_city)?;

    oyt_mdn_node
        .set_user_data(
            user_id,
            address_attribute,
            &address_sub_attribute_city,
            city.as_bytes().to_vec(),
        )
        .await?;

    oyt_mdn_node
        .set_user_data(
            user_id,
            address_attribute,
            &address_sub_attribute_zip,
            zip.as_bytes().to_vec(),
        )
        .await?;

    oyt_mdn_node
        .set_user_data(user_id, "payment_card", &["cvv"], b"123".to_vec())
        .await?;

    oyt_mdn_node
        .set_user_data("bob", "email", &[], b"bob@bob.com".to_vec())
        .await?;

    let res = oyt_mdn_node
        .get_user_data(user_id, address_attribute, &address_sub_attribute_city)
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

    // single value sub-attribute sharing
    let cap_for_untied = oyt_mdn_node
        .delegate_capabilities(
            AccessMode::ReadOnly,
            DelegateTo::new(untied_willow_node_user_id, oyt_data_subset_restriction),
        )
        .await?;

    let oyt_node_ticket = oyt_mdn_node.network_node_ticket().await?;

    let caps = ImportCapabilitiesFromRemotePeer {
        node_ticket: oyt_node_ticket.to_string(),
        caps: cap_for_untied,
    };

    let sync_event_stream = untied_mdn_node
        .import_capabilities_from_remote_peer(caps)
        .await?;

    let intent_handler1 = tokio::spawn(progress_session_intents(sync_event_stream));

    // multiple values root attribute sharing
    let address_records_key = oyt_mdn_node.make_entry_path(user_id, address_attribute, &[])?;
    let oyt_data_root_attribute_restriction =
        RestrictArea::Restrict(Area::path(address_records_key.clone()));

    let cap_for_untied = oyt_mdn_node
        .delegate_capabilities(
            AccessMode::ReadOnly,
            DelegateTo::new(
                untied_willow_node_user_id,
                oyt_data_root_attribute_restriction,
            ),
        )
        .await?;

    let caps = ImportCapabilitiesFromRemotePeer {
        node_ticket: oyt_node_ticket.to_string(),
        caps: cap_for_untied,
    };

    let sync_event_stream = untied_mdn_node
        .import_capabilities_from_remote_peer(caps)
        .await?;

    let intent_handler2 = tokio::spawn(progress_session_intents(sync_event_stream));

    let queries = tokio::spawn(async move {
        loop {
            let res = untied_mdn_node.get_user_data("bob", "email", &[]).await?;

            log::warn!("non-auth res {res:#?}");

            let zip_res = untied_mdn_node
                .get_user_data(user_id, address_attribute, &address_sub_attribute_zip)
                .await?;

            let has_zip_value = zip_res.iter().any(|e| e.value == zip.as_bytes().to_vec());

            let city_res = untied_mdn_node
                .get_user_data(user_id, address_attribute, &address_sub_attribute_city)
                .await?;

            let has_city_value = city_res.iter().any(|e| e.value == city.as_bytes().to_vec());

            let address_res = untied_mdn_node
                .get_user_data(user_id, address_attribute, &[])
                .await?;

            let has_all_required_values = address_res
                .iter()
                .any(|e| e.value == city.as_bytes().to_vec())
                && has_city_value
                && has_zip_value;

            if has_all_required_values {
                assert_eq!(zip_res.len(), 1);
                assert_eq!(city_res.len(), 1);
                assert_eq!(address_res.len(), 2);

                break;
            }

            tokio::time::sleep(Duration::from_secs(1)).await;
        }

        Ok(()) as anyhow::Result<()>
    });

    let queries = tokio::time::timeout(Duration::from_secs(10), queries).map_err(|e| {
        anyhow!(format!(
            "{e}: no entries meeting the required criteria were found"
        ))
    });

    select! {
        r1 = intent_handler1 => r1?,
        r2 = intent_handler2 => r2?,
        r3 = queries => r3???,
    };

    Ok(())
}
