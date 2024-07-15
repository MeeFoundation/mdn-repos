use super::{
    api_types::{CloudNodeAttachmentRequest, CloudNodeAttachmentResponse},
    dto::CloudNodeAttachmentDto,
    repository::ProviderCloudNodesRepository,
};
use crate::{
    db_models::provider_cloud_nodes,
    domain::provider::account::service::ProviderAccountService,
    error::MeeProviderManagerResult,
};
use service_utils::mee_provider_manager::auth::LoggedInProvider;
use uuid::Uuid;

pub struct ProviderCloudNodesService<'a> {
    provider_cloud_nodes_repository:
        Box<dyn ProviderCloudNodesRepository + Send + Sync + 'a>,
    provider_account_service: ProviderAccountService<'a>,
}

impl<'a> ProviderCloudNodesService<'a> {
    pub fn new(
        provider_cloud_nodes_repository: Box<
            dyn ProviderCloudNodesRepository + Send + Sync + 'a,
        >,
        provider_account_service: ProviderAccountService<'a>,
    ) -> Self {
        Self {
            provider_cloud_nodes_repository,
            provider_account_service,
        }
    }
    pub async fn list_cloud_nodes(
        &self,
        logged_in_provider: LoggedInProvider,
    ) -> MeeProviderManagerResult<Vec<CloudNodeAttachmentResponse>> {
        let provider_acc = self
            .provider_account_service
            .get_account_by_meeid_err(&logged_in_provider.meeid)
            .await?;

        let res = self
            .provider_cloud_nodes_repository
            .list_cloud_nodes(provider_acc.provider_id)
            .await?
            .into_iter()
            .map(Into::into)
            .collect();

        Ok(res)
    }
    pub async fn attach_cloud_node(
        &self,
        CloudNodeAttachmentRequest {
            cloud_node_discovery_url,
            cloud_node_did,
        }: CloudNodeAttachmentRequest,
        logged_in_provider: LoggedInProvider,
    ) -> MeeProviderManagerResult<CloudNodeAttachmentResponse> {
        let provider_acc = self
            .provider_account_service
            .get_account_by_meeid_err(&logged_in_provider.meeid)
            .await?;

        let provider_cloud_nodes::Model {
            cloud_node_uid,
            cloud_node_discovery_url,
            cloud_node_did,
            ..
        } = self
            .provider_cloud_nodes_repository
            .attach_cloud_node(CloudNodeAttachmentDto {
                cloud_node_uid: Uuid::new_v4().to_string(),
                cloud_node_discovery_url,
                cloud_node_did,
                provider_id: provider_acc.provider_id,
            })
            .await?;

        let res = CloudNodeAttachmentResponse {
            cloud_node_uid,
            cloud_node_discovery_url,
            cloud_node_did,
        };
        Ok(res)
    }
}
