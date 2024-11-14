use super::{
    user_account::api::account::{methods::*, types::*},
    user_devices::api::devices::{methods::*, types::*},
};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
          register_user,
          login_user,
          register_user_device,
          approve_user_device_linkage,
          list_user_device_linkage_requests,
      ),
      components(
          schemas(
              CreateUserAccountRequest,
              UserAccountLoginRequest,
              UserAccountLoginResponse,
              RegisterUserDeviceRequest,
              ApproveUserDeviceLinkageRequest,
              UserDeviceLinkageRequest,
          ),
      ),
      tags(
          (name = "MDN user related functionality", description = "REST API"),
      )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/mdn_users/openapi.json";
