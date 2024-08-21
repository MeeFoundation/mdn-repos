use super::node::MdnAgentDataNodeWillowImpl;
use crate::{
    error::MeeDataSyncResult,
    mdn::store::{key_components, MdnAgentDataNodeKvStore, ReadDataRecord},
    willow::utils::path_from_bytes_slice,
};
use async_trait::async_trait;
use futures::stream::BoxStream;

#[async_trait]
impl MdnAgentDataNodeKvStore for MdnAgentDataNodeWillowImpl {
    async fn set_value(&self, key: &str, value: Vec<u8>) -> MeeDataSyncResult {
        let path = Self::data_entry_path_from_key_components(key_components(key)?)?;

        self.willow_peer
            .willow_data_manager
            .insert_entry(
                self.mdn_ns_store_manager.get_agent_node_data_ns().await?.0,
                path,
                value,
            )
            .await?;

        Ok(())
    }

    async fn del_value(&self, key: &str) -> MeeDataSyncResult<bool> {
        let res = self.remove_entries(key).await?.pop().unwrap_or(false);

        Ok(res)
    }

    async fn get_values_stream_by_user(
        &self,
        user_id: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let user_prefix = path_from_bytes_slice(&[user_id.as_bytes()])?;

        let res = self
            .all_values_filter(move |e| user_prefix.is_prefix_of(e.path()))
            .await?;

        Ok(res)
    }

    async fn get_values_stream_by_attr(
        &self,
        attribute_name: &str,
    ) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let attribute_name = attribute_name.to_string();

        let res = self
            .all_values_filter(move |e| {
                let attribute_name_component = e.path().get_component(1);
                if let Some(attr) =
                    attribute_name_component.and_then(|c| String::from_utf8(c.to_vec()).ok())
                {
                    attr == attribute_name
                } else {
                    false
                }
            })
            .await?;

        Ok(res)
    }

    async fn get_all_values_stream(&self) -> MeeDataSyncResult<BoxStream<'_, ReadDataRecord>> {
        let res = self.all_values_filter(|_| true).await?;

        Ok(res)
    }
}
