use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

#[derive(Serialize, Deserialize, ToSchema)]
pub struct CreateSdaProfileRequest {
    pub user_uid: String,
    pub sda_profile: serde_json::Value,
}
