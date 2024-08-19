use anyhow::anyhow;
use futures::{future::join_all, StreamExt, TryFutureExt};
use iroh_willow::session::intents::IntentHandle;
use mee_data_sync::{
    mdn::{
        node::{MdnAgentDataNodeDelegation, MdnAgentDataNodeNetwork, MdnAgentDataNodeUser},
        store::MdnAgentDataNodeKvStore,
        willow_impl::node::MdnAgentDataNodeWillowImpl,
    },
    willow::{
        peer::{delegation_manager::ImportCapabilitiesFromRemotePeer, WillowPeer},
        utils::display_path,
    },
};
use rand_chacha::{rand_core::SeedableRng, ChaCha12Rng};
use std::time::Duration;
use tokio::{select, time::sleep};

pub fn create_rng(seed: &str) -> ChaCha12Rng {
    let seed = iroh_base::hash::Hash::new(seed);
    ChaCha12Rng::from_seed(*(seed.as_bytes()))
}

async fn progress_session_intents(mut sync_event_stream: IntentHandle) {
    loop {
        while let Some(ev) = sync_event_stream.next().await {
            match ev {
                iroh_willow::session::intents::EventKind::CapabilityIntersection {
                    area,
                    namespace,
                } => {
                    log::info!(
                        "CapabilityIntersection: {namespace} {}",
                        display_path(area.path())
                    );
                }
                iroh_willow::session::intents::EventKind::InterestIntersection {
                    area,
                    namespace,
                } => {
                    log::info!(
                        "InterestIntersection: {namespace} {}",
                        display_path(area.area.path())
                    );
                }
                iroh_willow::session::intents::EventKind::Reconciled { area, namespace } => {
                    log::info!("Reconciled: {namespace} {}", display_path(area.area.path()));
                }
                iroh_willow::session::intents::EventKind::ReconciledAll => {
                    log::info!("Reconciled all");
                }
                iroh_willow::session::intents::EventKind::Abort { error } => {
                    log::error!("Abort session intent: {error:#}");
                }
            };
        }

        log::info!("No more session intent events. Trying again...");

        sleep(Duration::from_secs(1)).await;
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

    let oyt_mdn_node = MdnAgentDataNodeWillowImpl::new(willow_peer).await?;

    let alice_user_id = "alice";
    let bob_user_id = "bob";
    let address_attribute = "address";
    let address_sub_attribute_city = "city";
    let address_sub_attribute_zip = "zip";
    let alice_city = "Rome";
    let bob_city = "Milan";
    let alice_zip = "123";
    let bob_email = "bob@bob.com";

    let alice_address_path = format!("{alice_user_id}/{address_attribute}");

    let alice_city_path =
        format!("{alice_user_id}/{address_attribute}/0/{address_sub_attribute_city}");

    let bob_city_path = format!("{bob_user_id}/{address_attribute}/0/{address_sub_attribute_city}");

    let alice_zip_path =
        format!("{alice_user_id}/{address_attribute}/0/{address_sub_attribute_zip}");

    let alice_cvv_path = format!("{alice_user_id}/payment_card/0/cvv");
    let bob_email_path = format!("{bob_user_id}/email");
    let temp_bob_phone_path = format!("{bob_user_id}/phone");
    let temp_bob_phone = b"911";

    oyt_mdn_node
        .set_value(&temp_bob_phone_path, temp_bob_phone.to_vec())
        .await?;

    oyt_mdn_node
        .set_value(&alice_city_path, alice_city.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .set_value(&bob_city_path, bob_city.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .set_value(&alice_zip_path, alice_zip.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .set_value(&alice_cvv_path, b"123".to_vec())
        .await?;

    oyt_mdn_node
        .set_value(&bob_email_path, bob_email.as_bytes().to_vec())
        .await?;

    let all_cities_res = oyt_mdn_node
        .get_values_stream_by_attr(&address_attribute)
        .await?
        .collect::<Vec<_>>()
        .await;

    assert_eq!(all_cities_res.len(), 3);

    let bob_res = oyt_mdn_node
        .get_values_stream_by_user(&bob_user_id)
        .await?
        .collect::<Vec<_>>()
        .await
        .pop()
        .unwrap();

    assert_eq!(bob_res.value, bob_email.as_bytes());
    assert_eq!(bob_res.key, bob_email_path);

    let res = oyt_mdn_node
        .get_all_values_stream()
        .await?
        .collect::<Vec<_>>()
        .await
        .into_iter()
        .find(|e| (&e.key, e.value.as_slice()) == (&alice_city_path, alice_city.as_bytes()))
        .unwrap();

    assert_eq!(res.value, alice_city.as_bytes());
    assert_eq!(res.key, alice_city_path);

    let bob_phone = oyt_mdn_node
        .get_all_values_stream()
        .await?
        .collect::<Vec<_>>()
        .await
        .into_iter()
        .find(|e| e.key == temp_bob_phone_path);

    assert!(bob_phone.is_some());

    // TODO wait for empty `iroh-willow` payload bug fix
    // let res = oyt_mdn_node.del_value(&temp_bob_phone_path).await?;

    // assert!(res);

    // let bob_phone = oyt_mdn_node
    //     .get_all_values_stream()
    //     .await?
    //     .collect::<Vec<_>>()
    //     .await;

    // assert!(bob_phone
    //     .iter()
    //     .find(|e| e.key == temp_bob_phone_path)
    //     .is_none());

    // Untied node
    let mut rng = create_rng("untied node");
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let untied_mdn_node = MdnAgentDataNodeWillowImpl::new(willow_peer).await?;

    // The ID actually comes with a first Untied request to OYT after MDS discovery process
    let untied_willow_node_user_id = untied_mdn_node.user_id().await?;

    // single value sub-attribute sharing
    let cap_for_untied = oyt_mdn_node
        .delegate_read_access(&alice_city_path, untied_willow_node_user_id)
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
    let cap_for_untied = oyt_mdn_node
        .delegate_read_access(&alice_address_path, untied_willow_node_user_id)
        .await?;

    let caps = ImportCapabilitiesFromRemotePeer {
        node_ticket: oyt_node_ticket.to_string(),
        caps: cap_for_untied,
    };

    let sync_event_stream = untied_mdn_node
        .import_capabilities_from_remote_peer(caps)
        .await?;

    let intent_handler2 = tokio::spawn(progress_session_intents(sync_event_stream));

    let delegations = tokio::spawn(async move {
        loop {
            let res = untied_mdn_node
                .get_all_values_stream()
                .await?
                .collect::<Vec<_>>()
                .await;

            log::info!("delegated data: {res:#?}");

            let has_zip_value = res.iter().any(|e| e.value == alice_zip.as_bytes().to_vec());

            let has_city_value = res
                .iter()
                .any(|e| e.value == alice_city.as_bytes().to_vec());

            let has_all_required_values = res
                .iter()
                .any(|e| e.value == alice_city.as_bytes().to_vec())
                && has_city_value
                && has_zip_value;

            if has_all_required_values {
                assert_eq!(res.len(), 2);

                break;
            }

            sleep(Duration::from_secs(1)).await;
        }

        oyt_mdn_node
            .revoke_shared_access(&alice_address_path, untied_willow_node_user_id)
            .await?;

        loop {
            let res = untied_mdn_node.read_revocation_list().await?;

            log::info!("revocation metadata: {res:#?}");

            sleep(Duration::from_secs(1)).await;
        }

        // TODO wait for empty `iroh-willow` payload bug fix
        // removes entry in source store
        // let del = oyt_mdn_node.del_value(&alice_city_path).await?;

        // assert!(del);

        // loop {
        //     let res = untied_mdn_node
        //         .get_all_values_stream()
        //         .await?
        //         .collect::<Vec<_>>()
        //         .await;

        //     let has_no_city_value = res.iter().find(|e| e.key == alice_city_path);

        //     // should be no value after sync
        //     if has_no_city_value.is_none() {
        //         break;
        //     }

        //     tokio::time::sleep(Duration::from_secs(1)).await;
        // }

        Ok(()) as anyhow::Result<()>
    });

    let delegations = tokio::time::timeout(Duration::from_secs(10), delegations).map_err(|e| {
        anyhow!(format!(
            "{e}: no entries meeting the required criteria were found"
        ))
    });

    let intent_handlers = join_all([intent_handler1, intent_handler2]);

    select! {
        res = intent_handlers => {
            for r in res {
                r?;
            }
        },
        res = delegations => {
            res???;
        },
    };

    Ok(())
}
