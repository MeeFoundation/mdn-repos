pub mod data;
pub mod query;
pub mod schema;

use query::*;

trait QueryEngine {
    fn select(&self, query: SelectQuery, execution_stats: bool) -> SelectQueryResult;
    fn insert(&self, query: InsertQuery, execution_stats: bool) -> InsertQueryResult;
    fn delete(&self, query: DeleteQuery, execution_stats: bool) -> DeleteQueryResult;
    fn update(&self, query: UpdateQuery, execution_stats: bool) -> UpdateQueryResult;
}
