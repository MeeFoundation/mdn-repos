use mee_data_sync::mdn::{
    common::store::ReadDataRecord,
    provider_agent::delegation::manager::MdnProviderCapabilityPack,
};
use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

use crate::error::AgentServiceErr;

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
