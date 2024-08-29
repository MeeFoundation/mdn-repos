use futures::{future::join_all, StreamExt};
use iroh_net::ticket::NodeTicket;
use iroh_willow::proto::keys::UserId;
use mee_data_sync::{
    error::MeeDataSyncResult,
    mdn::{
        provider::delegation::manager::ImportCapabilitiesFromProvider,
        traits::node::MdnAgentProviderNode,
    },
    willow::utils::progress_session_intents,
};
use std::{sync::Arc, time::Duration};
use tokio::{select, sync::mpsc::Sender, time::sleep};

pub enum TestCase {
    DeleteEntry,
    RevokeCapability { other_willow_node_user_id: UserId },
    End,
}

pub struct ShareDataAndSyncParams {
    pub node_name: String,
    pub delegate_from_node: Arc<dyn MdnAgentProviderNode + Send + Sync>,
    pub other_mdn_node: Arc<dyn MdnAgentProviderNode + Send + Sync>,
    pub delegate_from_ticket: NodeTicket,
    pub alice_address_path: String,
    pub alice_city_path: String,
    pub alice_zip: String,
    pub alice_city: String,
    pub ready_for_next_test_scenario_tx: Sender<TestCase>,
}

const SLEEP_BETWEEN_FETCH_MS: u64 = 500;

pub async fn share_data_and_sync(
    ShareDataAndSyncParams {
        node_name,
        other_mdn_node,
        delegate_from_node,
        delegate_from_ticket,
        alice_address_path,
        alice_city,
        alice_zip,
        alice_city_path,
        ready_for_next_test_scenario_tx,
    }: ShareDataAndSyncParams,
) -> MeeDataSyncResult {
    // The ID actually comes with a first Other node request to OYT after MDS discovery process
    let other_willow_node_user_id = other_mdn_node.user_id().await?;

    // single value sub-attribute sharing
    let cap_for_other = delegate_from_node
        .mdn_delegation_manager()
        .delegate_read_access_to_provider(&alice_city_path, other_willow_node_user_id)
        .await?;

    let caps = ImportCapabilitiesFromProvider {
        provider_node_ticket: delegate_from_ticket.to_string(),
        caps: cap_for_other,
    };

    let sync_event_stream = other_mdn_node
        .mdn_delegation_manager()
        .import_capabilities_from_provider(caps)
        .await?;

    let intent_handler1 = tokio::spawn(progress_session_intents(sync_event_stream));

    // multiple values root attribute sharing
    let cap_for_other = delegate_from_node
        .mdn_delegation_manager()
        .delegate_read_access_to_provider(&alice_address_path, other_willow_node_user_id)
        .await?;

    let caps = ImportCapabilitiesFromProvider {
        provider_node_ticket: delegate_from_ticket.to_string(),
        caps: cap_for_other,
    };

    let sync_event_stream = other_mdn_node
        .mdn_delegation_manager()
        .import_capabilities_from_provider(caps)
        .await?;

    let intent_handler2 = tokio::spawn(progress_session_intents(sync_event_stream));

    let delegations = tokio::spawn({
        let node_name = node_name.clone();

        async move {
            loop {
                let res = other_mdn_node
                    .get_all_values_stream()
                    .await?
                    .collect::<Vec<_>>()
                    .await;

                log::info!("[{node_name}]: delegated data: {}", res.len());

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

                sleep(Duration::from_millis(SLEEP_BETWEEN_FETCH_MS)).await;
            }

            ready_for_next_test_scenario_tx
                .send(TestCase::DeleteEntry)
                .await?;

            loop {
                let res = other_mdn_node
                    .get_all_values_stream()
                    .await?
                    .collect::<Vec<_>>()
                    .await;

                log::info!("[{node_name}] delegated data after deletion: {}", res.len());

                let has_no_city_value = res.iter().find(|e| e.key == alice_city_path);

                // should be no value after sync
                if has_no_city_value.is_none() {
                    break;
                }

                tokio::time::sleep(Duration::from_millis(SLEEP_BETWEEN_FETCH_MS)).await;
            }

            ready_for_next_test_scenario_tx
                .send(TestCase::RevokeCapability {
                    other_willow_node_user_id,
                })
                .await?;

            loop {
                let res = other_mdn_node
                    .get_all_values_stream()
                    .await?
                    .collect::<Vec<_>>()
                    .await;

                log::info!(
                    "[{node_name}] delegated data after cap revocation: {}",
                    res.len()
                );

                if res.is_empty() {
                    break;
                }

                sleep(Duration::from_millis(SLEEP_BETWEEN_FETCH_MS)).await;
            }

            ready_for_next_test_scenario_tx.send(TestCase::End).await?;

            Ok(()) as anyhow::Result<()>
        }
    });

    let intent_handlers = join_all([intent_handler1, intent_handler2]);

    select! {
        res = intent_handlers => {
            for r in res {
                r?;
            }
        },
        res = delegations => {
            res??;
        },
    };

    Ok(())
}
