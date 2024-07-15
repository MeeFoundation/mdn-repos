use crate::db_models::provider_mdn_license_application::*;
use crate::error::*;
use sea_orm::entity::prelude::*;
use sea_orm::Condition;
use sea_orm::IntoActiveModel;
use sea_orm::Set;
use sea_orm::{QueryOrder, QuerySelect, QueryTrait};

use super::domain::MdnLicenseApplicationStatus;
use super::domain::ProviderMdnLicenseApplicationModel;
use super::dto::ModelPage;

#[async_trait::async_trait]
pub trait ProviderMdnLicenseApplicationRepo {
    async fn find_by_provider_and_meeid(
        &self,
        provider_meeid: &str,
        meeid: &str,
    ) -> MdnLicenseManagerResult<Option<ProviderMdnLicenseApplicationModel>>;

    async fn get_by_provider_and_meeid(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn find_all_by_provider(
        &self,
        provider_meeid: &str,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModel>>;

    async fn find_all(
        &self,
        limit: Option<u64>,
        offset: Option<u64>,
        search: Option<String>,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<ModelPage<ProviderMdnLicenseApplicationModel>>;

    async fn create(
        &self,
        ent: ProviderMdnLicenseApplicationModel,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel>;

    async fn update(
        &self,
        ent: ProviderMdnLicenseApplicationModel,
    ) -> MdnLicenseManagerResult<()>;

    async fn delete(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<()>;
}

pub struct ProviderMdnLicenseApplicationRepoImpl<'a, C: ConnectionTrait> {
    db_conn: &'a C,
}

impl<'a, C: ConnectionTrait> ProviderMdnLicenseApplicationRepoImpl<'a, C> {
    pub fn new(db_conn: &'a C) -> Self {
        Self { db_conn }
    }
}

#[async_trait::async_trait]
impl<'a, C: ConnectionTrait> ProviderMdnLicenseApplicationRepo
    for ProviderMdnLicenseApplicationRepoImpl<'a, C>
{
    async fn find_by_provider_and_meeid(
        &self,
        provider_meeid: &str,
        meeid: &str,
    ) -> MdnLicenseManagerResult<Option<ProviderMdnLicenseApplicationModel>>
    {
        let result = Entity::find()
            .filter(Column::Meeid.eq(meeid))
            .filter(Column::ProviderMeeid.eq(provider_meeid))
            .one(self.db_conn)
            .await?;

        Ok(result.map(|x| x.into()))
    }

    async fn get_by_provider_and_meeid(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let res = self
            .find_by_provider_and_meeid(&provider_meeid, &meeid)
            .await?;
        res.ok_or(not_found(provider_meeid, meeid))
    }

    async fn find_all_by_provider(
        &self,
        provider_meeid: &str,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<Vec<ProviderMdnLicenseApplicationModel>> {
        let result = Entity::find()
            .filter(Column::ProviderMeeid.eq(provider_meeid))
            .apply_if(statuses, |q, v| q.filter(Column::Status.is_in(v)))
            .order_by_desc(Column::UpdatedAt)
            .all(self.db_conn)
            .await?;

        Ok(result.into_iter().map(|x| x.into()).collect::<Vec<_>>())
    }

    async fn find_all(
        &self,
        limit: Option<u64>,
        offset: Option<u64>,
        search: Option<String>,
        statuses: Option<Vec<MdnLicenseApplicationStatus>>,
    ) -> MdnLicenseManagerResult<ModelPage<ProviderMdnLicenseApplicationModel>>
    {
        let q = Entity::find()
            .order_by_desc(Column::UpdatedAt)
            .apply_if(statuses, |q, v| q.filter(Column::Status.is_in(v)))
            .apply_if(search, |q, v| {
                q.filter(
                    Condition::any()
                        .add(Column::ContactEmail.like(format!("%{v}%")))
                        .add(Column::CompanyName.like(format!("%{v}%")))
                        .add(Column::CompanyUri.like(format!("%{v}%")))
                        .add(
                            Column::CloudNodeDiscoveryUrl
                                .like(format!("%{v}%")),
                        )
                        .add(Column::DecentralizedId.like(format!("%{v}%"))),
                )
            });

        let data = q
            .clone()
            .apply_if(limit, QuerySelect::limit)
            .apply_if(offset, QuerySelect::offset)
            .all(self.db_conn)
            .await?;

        let total = q.count(self.db_conn).await?;
        let data = data.into_iter().map(|x| x.into()).collect();

        Ok(ModelPage { data, total })
    }

    async fn create(
        &self,
        ent: ProviderMdnLicenseApplicationModel,
    ) -> MdnLicenseManagerResult<ProviderMdnLicenseApplicationModel> {
        let model: Model = ent.into();
        let active_model = model.into_active_model();
        let res = active_model.insert(self.db_conn).await?;
        Ok(res.into())
    }

    async fn update(
        &self,
        ProviderMdnLicenseApplicationModel {
            meeid,
            provider_meeid,
            contact_email,
            company_name,
            company_uri,
            cloud_node_discovery_url,
            decentralized_id,
            status,
            created_at,
            updated_at,
        }: ProviderMdnLicenseApplicationModel,
    ) -> MdnLicenseManagerResult<()> {
        let res = Entity::update_many()
            .filter(Column::Meeid.eq(&meeid))
            .filter(Column::ProviderMeeid.eq(&provider_meeid))
            .set(ActiveModel {
                meeid: Set(meeid.clone()),
                provider_meeid: Set(provider_meeid.clone()),
                contact_email: Set(contact_email),
                company_name: Set(company_name),
                company_uri: Set(company_uri),
                cloud_node_discovery_url: Set(cloud_node_discovery_url),
                decentralized_id: Set(decentralized_id),
                status: Set(status),
                updated_at: Set(updated_at),
                created_at: Set(created_at),
                ..Default::default()
            })
            .exec(self.db_conn)
            .await?;

        if res.rows_affected == 0 {
            Err(not_found(provider_meeid, meeid))
        } else {
            Ok(())
        }
    }

    async fn delete(
        &self,
        provider_meeid: String,
        meeid: String,
    ) -> MdnLicenseManagerResult<()> {
        let res = Entity::delete_many()
            .filter(Column::Meeid.eq(&meeid))
            .filter(Column::ProviderMeeid.eq(&provider_meeid))
            .exec(self.db_conn)
            .await?;

        if res.rows_affected == 0 {
            return Err(not_found(provider_meeid, meeid));
        } else {
            Ok(())
        }
    }
}

pub fn not_found(
    provider_meeid: String,
    meeid: String,
) -> MdnLicenseManagerErr {
    MdnLicenseManagerErr::DependedEntityNotFound(
        "Provider MDN License Application".to_string(),
        meeid,
        "provider".to_string(),
        provider_meeid,
    )
}
