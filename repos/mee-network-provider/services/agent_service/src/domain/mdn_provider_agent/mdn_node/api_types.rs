use crate::error::AgentServiceErr;
use chrono::TimeZone;
use mee_data_sync::{
    mdn_iiw38::{
        common::store::ReadDataRecord,
        provider_agent::delegation::manager::MdnProviderCapabilityPack,
    },
    willow::{
        proto::{
            grouping::RangeEnd,
            meadowcap::{McCapability, ReadAuthorisation},
        },
        utils::display_path,
    },
};
use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct SetPersonaAttributesRequest {
    pub key: String,
    pub value: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct GetPersonaAttributesResponse {
    pub key: String,
    pub value: String,
}

impl TryFrom<ReadDataRecord> for GetPersonaAttributesResponse {
    type Error = AgentServiceErr;

    fn try_from(
        ReadDataRecord { key, value }: ReadDataRecord,
    ) -> Result<Self, Self::Error> {
        Ok(Self {
            key,
            value: String::from_utf8(value)?,
        })
    }
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct GetPersonaAttributesRequest {
    pub key: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct DelPersonaAttributesRequest {
    pub key: String,
}

#[derive(Debug, Serialize, Deserialize, ToSchema)]
pub struct DelegateReadAccessToProviderRequest {
    pub data_path: String,
    pub provider_id: String,
}

#[derive(Debug, Clone, Serialize, Deserialize, ToSchema)]
pub struct DelegatedCap {
    pub capability_id: String,
    pub cap_receiver: String,
    pub shared_data_path: String,
}

impl From<MdnProviderCapabilityPack> for DelegatedCap {
    fn from(
        MdnProviderCapabilityPack {
            capability_id,
            cap_receiver,
            shared_data_path,
            ..
        }: MdnProviderCapabilityPack,
    ) -> Self {
        Self {
            capability_id,
            cap_receiver: cap_receiver.to_string(),
            shared_data_path,
        }
    }
}

#[derive(Serialize, Deserialize, ToSchema)]
pub struct ImportedCapability {
    pub namespace_kind: String,
    pub namespace: String,
    pub owner: String,
    pub receiver: String,
    pub granted_data_path: String,
    pub granted_until: Option<String>,
}

impl From<ReadAuthorisation> for ImportedCapability {
    fn from(value: ReadAuthorisation) -> Self {
        let namespace_kind = match value.read_cap() {
            McCapability::Owned(_) => "Owned".to_string(),
            McCapability::Communal(_) => "Communal".to_string(),
        };

        let area = value.read_cap().granted_area();

        let granted_until = match area.times().end {
            RangeEnd::Closed(t) => chrono::Utc
                .timestamp_opt(t as i64, 0)
                .single()
                .map(|t| t.to_rfc2822()),
            RangeEnd::Open => Some("Never".to_string()),
        };

        Self {
            namespace_kind,
            namespace: value.read_cap().granted_namespace().to_string(),
            owner: value.read_cap().progenitor().to_string(),
            receiver: value.read_cap().receiver().to_string(),
            granted_data_path: display_path(area.path()),
            granted_until,
        }
    }
}
