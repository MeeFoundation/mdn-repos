use crate::error::{MdnLicenseManagerErr::*, MdnLicenseManagerResult};
use chrono::Utc;
use sea_orm::{entity::prelude::*, DeriveActiveEnum};
use serde::{Deserialize, Serialize};
use strum_macros::{Display, EnumString};
use utoipa::ToSchema;

#[derive(
    Debug,
    Serialize,
    Deserialize,
    ToSchema,
    PartialEq,
    Clone,
    Display,
    EnumString,
    EnumIter,
    DeriveActiveEnum,
    Eq,
)]
#[sea_orm(rs_type = "String", db_type = "String(None)")]
pub enum MdnLicenseApplicationStatus {
    /// The newly created application (isn't submitted yet)
    #[sea_orm(string_value = "Draft")]
    Draft,
    /// The application is in process of approving by the Mee Foundation
    #[sea_orm(string_value = "Processing")]
    Processing,
    /// The application was canceled by the Provider itself
    #[sea_orm(string_value = "Canceled")]
    Canceled,
    /// The application was rejected by the Mee Foundation
    #[sea_orm(string_value = "Rejected")]
    Rejected,
    /// The application was approved by the Mee Foundation
    #[sea_orm(string_value = "Approved")]
    Approved,
    /// The application was replaced by the newly approved one
    #[sea_orm(string_value = "Discontinued")]
    Discontinued,
}

#[derive(Debug, Serialize, Deserialize, Clone, Eq, PartialEq)]
pub struct ProviderMdnLicenseApplicationModel {
    pub meeid: String,
    pub provider_meeid: String,
    pub contact_email: String,
    pub company_name: String,
    pub company_uri: String,
    pub cloud_node_discovery_url: String,
    pub decentralized_id: String,
    pub status: MdnLicenseApplicationStatus,
    pub created_at: DateTimeUtc,
    pub updated_at: DateTimeUtc,
}

pub struct ProviderMdnLicenseApplicationUpdateModel {
    pub contact_email: String,
    pub company_name: String,
    pub company_uri: String,
    pub cloud_node_discovery_url: String,
    pub decentralized_id: String,
}

impl ProviderMdnLicenseApplicationModel {
    pub fn update(
        &mut self,
        ProviderMdnLicenseApplicationUpdateModel {
            contact_email,
            company_name,
            company_uri,
            cloud_node_discovery_url,
            decentralized_id,
        }: ProviderMdnLicenseApplicationUpdateModel,
    ) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Draft {
            self.contact_email = contact_email;
            self.company_name = company_name;
            self.company_uri = company_uri;
            self.cloud_node_discovery_url = cloud_node_discovery_url;
            self.decentralized_id = decentralized_id;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationUpdateNotDraftError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }

    pub fn to_processing(&mut self) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Draft {
            self.status = MdnLicenseApplicationStatus::Processing;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationToProcessingError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }

    pub fn to_rejected(&mut self) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Processing {
            self.status = MdnLicenseApplicationStatus::Rejected;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationToRejectedError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }

    pub fn to_approved(&mut self) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Processing {
            self.status = MdnLicenseApplicationStatus::Approved;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationToApprovedError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }

    pub fn to_canceled(&mut self) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Processing {
            self.status = MdnLicenseApplicationStatus::Canceled;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationToCanceledError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }

    pub fn to_draft(&mut self) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Canceled {
            self.status = MdnLicenseApplicationStatus::Draft;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationToDraftError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }

    pub fn to_discontinued(&mut self) -> MdnLicenseManagerResult<()> {
        if self.status == MdnLicenseApplicationStatus::Approved {
            self.status = MdnLicenseApplicationStatus::Discontinued;
            self.updated_at = Utc::now();
            Ok(())
        } else {
            Err(MdnLicenseApplicationToDiscontinuedError(
                self.meeid.clone(),
                self.status.to_string(),
            ))
        }
    }
}

pub type ProviderNodeSsiJwt = String;
pub type ApprovedProviderMdnLicenseAccessToken = String;
