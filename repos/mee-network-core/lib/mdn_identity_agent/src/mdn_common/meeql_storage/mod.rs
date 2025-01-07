use super::mdn_custodian_willow_storage::MdnCustodianWillowStorage;
use crate::error::MdnIdentityAgentResult;
use async_trait::async_trait;

#[async_trait]
pub trait MdnCustodianMeeqlDataManager {
    ///
    async fn write_context_data(
        &self,
        mdn_identity_context_uid: &str,
        meeql_query: &str,
        value: Vec<u8>,
    ) -> MdnIdentityAgentResult;
    ///
    async fn read_context_data(
        &self,
        context_scoped_subject_uid: &str,
        meeql_query: &str,
    ) -> MdnIdentityAgentResult<Vec<Vec<u8>>>;
}

pub struct MdnCustodianMeeqlDataManagerWillowImpl {
    mdn_custodian_willow_storage: MdnCustodianWillowStorage,
}

impl MdnCustodianMeeqlDataManagerWillowImpl {
    pub fn new(mdn_custodian_willow_storage: MdnCustodianWillowStorage) -> Self {
        Self {
            mdn_custodian_willow_storage,
        }
    }
}

#[async_trait]
impl MdnCustodianMeeqlDataManager for MdnCustodianMeeqlDataManagerWillowImpl {
    async fn write_context_data(
        &self,
        mdn_identity_context_uid: &str,
        meeql_query: &str,
        value: Vec<u8>,
    ) -> MdnIdentityAgentResult {
        let Some(ctx) = self
            .mdn_custodian_willow_storage
            .context_namespaces()
            .await?
            .into_iter()
            .find(|c| c.mdn_identity_context_uid == mdn_identity_context_uid)
        else {
            return Ok(());
        };

        // TODO add real MeeQL query parser and executor
        self.mdn_custodian_willow_storage
            .willow_data_storage_manager
            .set_value(ctx.willow_ns, meeql_query, value)
            .await?;

        Ok(())
    }
    ///
    async fn read_context_data(
        &self,
        context_scoped_subject_uid: &str,
        meeql_query: &str,
    ) -> MdnIdentityAgentResult<Vec<Vec<u8>>> {
        let mut res = vec![];

        // TODO add real MeeQL query parser and executor
        for ctx in self
            .mdn_custodian_willow_storage
            .context_namespaces()
            .await?
            .into_iter()
            .filter(|c| c.mdn_context_scoped_uid == context_scoped_subject_uid)
        {
            if let Some(value) = self
                .mdn_custodian_willow_storage
                .willow_data_storage_manager
                .get_value(ctx.willow_ns, &meeql_query)
                .await?
            {
                res.push(value);
            }
        }

        Ok(res)
    }
}
