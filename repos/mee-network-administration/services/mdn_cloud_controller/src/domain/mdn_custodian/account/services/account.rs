use crate::{
    db_models::mdn_custodians,
    domain::mdn_custodian::account::repositories::mdn_custodians::{
        CreateUserCustodianAccountDto, MdnCustodiansRepository,
    },
    error::{MdnCloudControllerErr, MdnCloudControllerResult},
};

pub struct MdnCustodiansService<'a> {
    mdn_custodians_repository:
        Box<dyn MdnCustodiansRepository + Send + Sync + 'a>,
}

impl<'a> MdnCustodiansService<'a> {
    pub fn new(
        mdn_custodians_repository: Box<
            dyn MdnCustodiansRepository + Send + Sync + 'a,
        >,
    ) -> Self {
        Self {
            mdn_custodians_repository,
        }
    }
    pub async fn create_user_custodian_account(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<mdn_custodians::Model> {
        let mdn_custodian_uid = uuid::Uuid::new_v4().to_string();

        let res = self
            .mdn_custodians_repository
            .create_user_custodian_account(CreateUserCustodianAccountDto {
                mdn_custodian_uid: format!("mdn_custodian-{mdn_custodian_uid}"),
                mdn_user_custodian_id: mdn_user_id,
            })
            .await?;

        Ok(res)
    }

    pub async fn get_user_custodian(
        &self,
        mdn_user_id: i64,
    ) -> MdnCloudControllerResult<mdn_custodians::Model> {
        let res = self
            .mdn_custodians_repository
            .get_user_custodian(mdn_user_id)
            .await?
            .ok_or_else(|| {
                MdnCloudControllerErr::MdnUserAccountManagement(
                    "User custodian has not found".to_string(),
                )
            })?;

        Ok(res)
    }
    pub async fn get_custodian_by_uid(
        &self,
        mdn_custodian_uid: &str,
    ) -> MdnCloudControllerResult<mdn_custodians::Model> {
        self.mdn_custodians_repository
            .get_custodian_by_uid_required(mdn_custodian_uid)
            .await
    }
}
