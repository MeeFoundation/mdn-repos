use mee_data_sync::mdn::common::store::ReadDataRecord;
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
pub struct DelegateReadAccessToProviderRequest {
    pub data_path: String,
    pub provider_id: String,
}
