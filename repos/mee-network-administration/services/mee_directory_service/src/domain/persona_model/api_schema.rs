
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
          
      ),
      components(
          schemas(
              
          ),
      ),
      tags(
          (name = "User related functionality", description = "REST API"),
      )
  )]
pub struct ApiDoc;

pub const OPEN_API_PATH: &str = "/persona_model/openapi.json";
