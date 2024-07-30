use super::{api_methods::*, api_types::*};
use utoipa::OpenApi;

#[derive(OpenApi)]
#[openapi(
      paths(
        select,
        merge,
        delete,
        update,
      ),
      // security(
      //     ("authorization" = []),
      // ),
      components(
          schemas(
              SelectingField,
              SelectQueryRequest,
              Aggregation,
              Operation,
              SelectQueryResponse,

              MergeQueryRequest,
              MergeQueryResponse,
              MergeQueryCollectionStrategy,
              MergeQueryFieldStrategy,
              DeleteQueryRequest,
              DeleteQueryResponse,

              UpdateQueryRequest,
              UpdateQueryResponse,
                UpdateClause,
                WhereClause,
                CheckOperator,

                FieldName,
                ObjectId,
                SchemaName,
          ),
      ),
      // modifiers(&SecurityAddon),
      tags(
          (name = "Mee query language", description = "MeeQl REST API"),
      )
  )]
pub struct ApiDoc;

// pub const OPEN_API_PATH: &str = "/providers/mdn_license_applications/openapi.json";
