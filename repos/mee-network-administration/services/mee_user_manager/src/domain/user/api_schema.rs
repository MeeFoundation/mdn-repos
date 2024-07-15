use super::account::{api_methods::*, api_types::*};
use service_utils::mee_user_manager::api_types::{
    AuthorizeUserRequest, AuthorizeUserResponse,
};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
          register_user,
          login_user,
          authorize_user,
      ),
      components(
          schemas(
              AuthorizeUserRequest,
              AuthorizeUserResponse,
              CreateUserAccountRequest,
              UserAccountLoginRequest,
              UserAccountLoginResponse,
          ),
      ),
      tags(
          (name = "User related functionality", description = "REST API"),
      )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/users/openapi.json";
