use crate::mdn_iiw38::{
    common::mdn_node::{create_provider_node, create_virtual_agent_node},
    mdn_providers::helpers::{share_data_and_sync, ShareDataAndSyncParams, TestCase},
};
use anyhow::anyhow;
use futures::{future::join_all, StreamExt};
use mee_data_sync::mdn_iiw38::provider_agent::delegation::manager::ImportCapabilitiesFromVirtualAgent;
use std::{collections::HashSet, time::Duration};
use tokio::{sync::mpsc, time::sleep};

const SHARED_WITH_PEERS_COUNT: usize = 10;

#[ignore = "flaky"]
#[tokio::test]
async fn providers_read_access_sharing() -> anyhow::Result<()> {
    // iroh_test::logging::setup_multithreaded();
    let _ = env_logger::Builder::new()
        .filter_level(log::LevelFilter::Info)
        .filter_module("iroh", log::LevelFilter::Warn)
        .filter_module("iroh-willow", log::LevelFilter::Warn)
        .filter_module("tracing::span", log::LevelFilter::Warn)
        .try_init();

    let oyt_mdn_node = create_provider_node().await?;
    let virtual_agent_node = create_virtual_agent_node().await?;
    let via_node_ticket = virtual_agent_node.network_node_ticket().await?;

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

    let alice_city_path = format!("{alice_address_path}/0/{address_sub_attribute_city}");

    let bob_city_path = format!("{bob_user_id}/{address_attribute}/0/{address_sub_attribute_city}");

    let alice_zip_path = format!("{alice_address_path}/0/{address_sub_attribute_zip}");

    let alice_cvv_path = format!("{alice_user_id}/payment_card/0/cvv");
    let bob_email_path = format!("{bob_user_id}/email");
    let temp_bob_phone_path = format!("{bob_user_id}/phone");
    let temp_bob_phone = b"911";

    let caps = virtual_agent_node
        .mdn_delegation_manager()
        .share_search_schemas_ns_with_provider(oyt_mdn_node.user_id().await?)
        .await?;

    let _intent = oyt_mdn_node
        .mdn_delegation_manager()
        .import_search_schemas_ns_from_virtual_agent(ImportCapabilitiesFromVirtualAgent {
            virtual_agent_node_ticket: via_node_ticket.to_string(),
            caps,
        })
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&temp_bob_phone_path, temp_bob_phone.to_vec())
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&alice_city_path, alice_city.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&bob_city_path, bob_city.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&alice_zip_path, alice_zip.as_bytes().to_vec())
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&alice_cvv_path, b"123".to_vec())
        .await?;

    oyt_mdn_node
        .mdn_data_store()
        .set_value(&bob_email_path, bob_email.as_bytes().to_vec())
        .await?;

    let all_cities_res = oyt_mdn_node
        .mdn_data_store()
        .get_values_stream_by_attr(&address_attribute)
        .await?
        .collect::<Vec<_>>()
        .await;

    assert_eq!(all_cities_res.len(), 3);

    let bob_res = oyt_mdn_node
        .mdn_data_store()
        .get_values_stream_by_user(&bob_user_id)
        .await?
        .collect::<Vec<_>>()
        .await
        .pop()
        .unwrap();

    assert_eq!(bob_res.value, bob_email.as_bytes());
    assert_eq!(bob_res.key, bob_email_path);

    let res = oyt_mdn_node
        .mdn_data_store()
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
        .mdn_data_store()
        .get_all_values_stream()
        .await?
        .collect::<Vec<_>>()
        .await
        .into_iter()
        .find(|e| e.key == temp_bob_phone_path);

    assert!(bob_phone.is_some());

    let res = oyt_mdn_node
        .mdn_data_store()
        .del_value(&temp_bob_phone_path)
        .await?;

    assert!(!res.is_empty());

    let bob_phone = oyt_mdn_node
        .mdn_data_store()
        .get_all_values_stream()
        .await?
        .collect::<Vec<_>>()
        .await;

    assert!(bob_phone
        .iter()
        .find(|e| e.key == temp_bob_phone_path)
        .is_none());

    let oyt_node_ticket = oyt_mdn_node.network_node_ticket().await?;

    let (ready_for_next_test_scenario_tx, mut ready_for_next_test_scenario_rx) =
        mpsc::channel(SHARED_WITH_PEERS_COUNT);

    let mut peers_tasks = vec![];
    // we hold references to make sure other nodes are still alive until end of the test
    let mut other_nodes = vec![];

    for c in 0..SHARED_WITH_PEERS_COUNT {
        let node_name = format!("peer-{c}");
        let other_mdn_node = create_provider_node().await?;
        other_nodes.push(other_mdn_node.clone());

        let peer_task = tokio::spawn(share_data_and_sync(ShareDataAndSyncParams {
            node_name,
            other_mdn_node,
            virtual_agent_ticket: via_node_ticket.clone(),
            virtual_agent_node: virtual_agent_node.clone(),
            delegate_from_node: oyt_mdn_node.clone(),
            delegate_from_ticket: oyt_node_ticket.clone(),
            alice_address_path: alice_address_path.clone(),
            alice_city_path: alice_city_path.clone(),
            alice_zip: alice_zip.to_string(),
            alice_city: alice_city.to_string(),
            ready_for_next_test_scenario_tx: ready_for_next_test_scenario_tx.clone(),
        }));

        peers_tasks.push(peer_task);
    }

    let test_progressor_task = tokio::spawn(async move {
        let mut next_test_scenario_counter = 0;
        let mut other_peers_user_ids = vec![];

        while let Some(ev) = ready_for_next_test_scenario_rx.recv().await {
            next_test_scenario_counter += 1;

            if next_test_scenario_counter == SHARED_WITH_PEERS_COUNT {
                match ev {
                    TestCase::DeleteEntry => {
                        let del = oyt_mdn_node
                            .mdn_data_store()
                            .del_value(&alice_city_path)
                            .await?;

                        assert!(!del.is_empty());
                    }
                    TestCase::RevokeCapability {
                        other_willow_node_user_id,
                    } => {
                        other_peers_user_ids.push(other_willow_node_user_id);

                        let cap_list = oyt_mdn_node
                            .mdn_delegation_manager()
                            .delegated_caps()
                            .await?;

                        for user_id in other_peers_user_ids.iter() {
                            for cap in cap_list.iter().filter(|c| &c.cap_receiver == user_id) {
                                oyt_mdn_node
                                    .mdn_delegation_manager()
                                    .revoke_shared_access_from_provider(
                                        &cap.capability_id,
                                        &cap.shared_data_path,
                                        *user_id,
                                    )
                                    .await?;
                            }
                        }
                    }
                    TestCase::End {
                        virtual_agent_schemas,
                    } => {
                        loop {
                            let schemas: HashSet<_> = virtual_agent_node
                                .search_schemas_store()
                                .get_all_values_stream()
                                .await?
                                .collect()
                                .await;

                            if oyt_mdn_node
                                .mdn_delegation_manager()
                                .is_revocation_list_empty()
                                .await?
                                && virtual_agent_schemas == schemas
                            {
                                break;
                            }

                            sleep(Duration::from_secs(1)).await;
                        }

                        break;
                    }
                };
                next_test_scenario_counter = 0;
            } else {
                match ev {
                    TestCase::RevokeCapability {
                        other_willow_node_user_id,
                    } => {
                        other_peers_user_ids.push(other_willow_node_user_id);
                    }
                    _ => {}
                }
            }
        }

        Ok(())
    });

    let mut tasks = vec![test_progressor_task];

    tasks.extend(peers_tasks);

    let res = join_all(tasks);

    let res = tokio::time::timeout(Duration::from_secs(60), res)
        .await
        .map_err(|e| {
            anyhow!(format!(
                "{e}: No entries were found that met the required criteria."
            ))
        })?;

    for r in res {
        r??;
    }

    Ok(())
}
