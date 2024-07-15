use super::dto::CloudNodeAttachmentDto;
use crate::{
    db_models::{prelude::*, provider_cloud_nodes},
    error::MeeProviderManagerResult,
};
use sea_orm::{prelude::*, ActiveValue::NotSet, Set};

#[async_trait::async_trait]
pub trait ProviderCloudNodesRepository {
    async fn list_cloud_nodes(
        &self,
        provider_id: i32,
    ) -> MeeProviderManagerResult<Vec<provider_cloud_nodes::Model>>;
    async fn attach_cloud_node(
        &self,
        create_dto: CloudNodeAttachmentDto,
    ) -> MeeProviderManagerResult<provider_cloud_nodes::Model>;
}

pub struct ProviderCloudNodesRepositoryDefault<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> ProviderCloudNodesRepositoryDefault<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> ProviderCloudNodesRepository
    for ProviderCloudNodesRepositoryDefault<'a, C>
{
    async fn list_cloud_nodes(
        &self,
        provider_id: i32,
    ) -> MeeProviderManagerResult<Vec<provider_cloud_nodes::Model>> {
        let res = ProviderCloudNodes::find()
            .filter(provider_cloud_nodes::Column::ProviderId.eq(provider_id))
            .all(self.db_conn)
            .await?;

        Ok(res)
    }
    async fn attach_cloud_node(
        &self,
        CloudNodeAttachmentDto {
            cloud_node_discovery_url,
            cloud_node_did,
            provider_id,
            cloud_node_uid,
        }: CloudNodeAttachmentDto,
    ) -> MeeProviderManagerResult<provider_cloud_nodes::Model> {
        let res = provider_cloud_nodes::ActiveModel {
            cloud_node_id: NotSet,
            cloud_node_uid: Set(cloud_node_uid),
            cloud_node_discovery_url: Set(cloud_node_discovery_url),
            cloud_node_did: Set(cloud_node_did),
            provider_id: Set(provider_id),
        }
        .insert(self.db_conn)
        .await?;

        Ok(res)
    }
}
