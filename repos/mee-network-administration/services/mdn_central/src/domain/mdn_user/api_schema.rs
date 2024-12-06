use super::user_account::api::{methods::*, types::*};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
          register_user,
          login_user,
      ),
      components(
          schemas(
              CreateUserAccountRequest,
              UserAccountLoginRequest,
              UserAccountLoginResponse,
          ),
      ),
      tags(
          (name = "MDN user related functionality", description = "REST API"),
      )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/mdn_users/openapi.json";
