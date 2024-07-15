use sea_orm::{DeriveActiveEnum, EnumIter};
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
pub enum OidcClientType {
    #[sea_orm(string_value = "Android")]
    Android,
    #[sea_orm(string_value = "Ios")]
    Ios,
    #[sea_orm(string_value = "Web")]
    Web,
}
