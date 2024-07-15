use super::{
    account::{api_methods::*, api_types::*},
    cloud_nodes::{api_methods::*, api_types::*},
};
use mee_http_utils::interservice::INTER_SERVICE_API_SECRET_HEADER;
use service_utils::mee_provider_manager::api_types::*;
use utoipa::{
    openapi::security::{
        ApiKey, ApiKeyValue, HttpAuthScheme, HttpBuilder, SecurityScheme,
    },
    Modify, OpenApi,
};

#[derive(OpenApi)]
#[openapi(
      paths(
          register_provider,
          login_provider,
          list_cloud_nodes,
          attach_cloud_node,
          is_cloud_node_linked_with_provider,
          provider_profile,
      ),
      components(
          schemas(
            ProviderAccountInfoResponse,
            IsCloudNodeLinkedRequest,
            CloudNodeAttachmentRequest,
            CloudNodeAttachmentResponse,
            CreateProviderAccountRequest,
            ProviderAccountLoginRequest,
            ProviderAccountLoginResponse,
          ),
      ),
      modifiers(&SecurityAddon),
      tags(
          (name = "Provider related functionality", description = "REST API"),
      )
  )]
pub struct ApiDoc;

struct SecurityAddon;

impl Modify for SecurityAddon {
    fn modify(&self, openapi: &mut utoipa::openapi::OpenApi) {
        if let Some(components) = openapi.components.as_mut() {
            components.add_security_scheme(
                "token_biscuit",
                SecurityScheme::Http(
                    HttpBuilder::new()
                        .scheme(HttpAuthScheme::Bearer)
                        .bearer_format("JWT")
                        .build(),
                ),
            );

            components.add_security_scheme(
                "inter_service_api_secret",
                SecurityScheme::ApiKey(ApiKey::Header(ApiKeyValue::new(
                    INTER_SERVICE_API_SECRET_HEADER,
                ))),
            );
        }
    }
}

pub const OPEN_API_PATH: &str = "/providers/openapi.json";
