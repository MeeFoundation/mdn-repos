use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Debug, Deserialize, Serialize, ToSchema)]
pub struct ShareSearchSchemasNsWithProviderRequest {
    pub provider_id: String,
}
