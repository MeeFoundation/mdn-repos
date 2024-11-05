use super::api_methods::*;

// use serde_json::Value;
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
        execute,
        insert_many,
      ),
      // security(
      //     ("authorization" = []),
      // ),
      // components(
      //     schemas(
      //       Value,
      //     ),
      // ),
      // modifiers(&SecurityAddon),
      tags(
          (name = "Mee query language", description = "MeeQl REST API"),
      )
  )]
pub struct ApiDoc;

// pub const OPEN_API_PATH: &str = "/providers/mdn_license_applications/openapi.json";
