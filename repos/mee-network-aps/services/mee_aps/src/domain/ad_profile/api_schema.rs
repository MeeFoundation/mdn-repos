use super::sda_profiles::{api_methods::*, api_types::*};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
          add_sda_profile,
      ),
      components(
          schemas(
            CreateSdaProfileRequest,
          ),
      ),
      tags(
          (name = "SDA profile related functionality", description = "REST API"),
      )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/sda_profile/openapi.json";
