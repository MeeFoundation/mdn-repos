use super::mdn_license_application::{api_methods::*, api_types::*, domain::MdnLicenseApplicationStatus};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
         mdn_license_approved_provider_access_token,
         create,
           get_by_meeid,
           get_all_by_provider,
           get_all, 
           update_draft,
           to_processing,
           to_canceled,
           to_approved,
           to_rejected,
           to_draft,
      ),
      // security(
      //     ("authorization" = []),
      // ),
      components(
          schemas(
              MdnLicenseApprovedProviderAccessTokenRequest,
              MdnLicenseApprovedProviderAccessTokenResponse,
              ProviderMdnLicenseApplicationWriteRequest,
              ProviderMdnLicenseApplicationModelResponse,
              ProviderMdnLicenseApplicationListRequest,
              ProviderMdnLicenseApplicationListResponse,
              MdnLicenseApplicationStatus,
              StatusesQueryParam,
          ),
      ),
      // modifiers(&SecurityAddon),
      tags(
          (name = "Provider Mee data network licenses application management", description = "REST API"),
      )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/providers/mdn_license_applications/openapi.json";
