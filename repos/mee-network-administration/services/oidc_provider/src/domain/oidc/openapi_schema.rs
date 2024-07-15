use crate::domain::oidc::{
    provider::{api_methods::*, api_types::*},
    registrar::domain::OidcClientType,
};
use service_utils::mee_provider_manager::api_types::ProviderAccountInfoResponse;
use utoipa::{
    openapi::security::{HttpAuthScheme, HttpBuilder, SecurityScheme},
    Modify, OpenApi,
};

#[derive(OpenApi)]
#[openapi(
        paths(
            provider_metadata,
            jwks,
            authorize,
            authorize_consent,
            issue_token,
            refresh_token,
            user_login_page,
            new_client,
            get_client,
        ),
        modifiers(&SecurityAddon),
        components(
            schemas(
                OidcClientType,
                OidcProviderRegistrarCreateResponse,
                ProviderAccountInfoResponse,
                OidcProviderRegistrarCreateRequest,
                OidcProviderRegistrarCreateResponse,
                JwkSetTO,
                JwkTO,
                ConfigTO,
                OAuthResponseTO,
            ),
        ),
        tags(
            (name = "OIDC", description = "OIDC API")
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
        }
    }
}
