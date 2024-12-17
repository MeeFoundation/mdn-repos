use sea_orm_migration::prelude::*;

#[derive(DeriveMigrationName)]
pub struct Migration;

static SQL_UP: &[u8] = include_bytes!("up.sql");
static SQL_DOWN: &[u8] = include_bytes!("down.sql");

#[async_trait::async_trait]
impl MigrationTrait for Migration {
    async fn up(&self, manager: &SchemaManager) -> Result<(), DbErr> {
        let sql = String::from_utf8_lossy(SQL_UP);

        let db = manager.get_connection();

        db.execute_unprepared(&sql).await?;

        Ok(())
    }

    async fn down(&self, manager: &SchemaManager) -> Result<(), DbErr> {
        let sql = String::from_utf8_lossy(SQL_DOWN);

        let db = manager.get_connection();

        db.execute_unprepared(&sql).await?;

        Ok(())
    }
}
