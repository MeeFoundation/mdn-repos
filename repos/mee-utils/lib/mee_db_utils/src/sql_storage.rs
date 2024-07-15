use sea_orm::{ConnectOptions, Database, DatabaseConnection};
use sea_orm_migration::MigratorTrait;
use std::sync::Arc;
use url::Url;

pub struct RdbStorageConfig {
    pub database_url: Url,
    pub db_pool_size: u32,
}

// TODO refactor to use it everywhere, instead of a concrete implementation
pub trait IRbdStorage {
    fn connection(&self) -> Arc<DatabaseConnection>;
}

impl IRbdStorage for RbdStorage {
    fn connection(&self) -> Arc<DatabaseConnection> {
        self.connection.clone()
    }
}

#[derive(Clone)]
pub struct RbdStorage {
    connection: Arc<DatabaseConnection>,
}

impl RbdStorage {
    pub async fn try_new<M>(
        RdbStorageConfig {
            database_url,
            db_pool_size,
        }: RdbStorageConfig,
    ) -> anyhow::Result<Self>
    where
        M: MigratorTrait,
    {
        let mut opt = ConnectOptions::new(database_url.as_str());
        opt.sqlx_logging(true).max_connections(db_pool_size);

        let connection = Database::connect(opt).await?;
        let connection = Arc::new(connection);

        M::up(connection.as_ref(), None).await?;

        Ok(Self { connection })
    }
    pub fn connection(&self) -> Arc<DatabaseConnection> {
        self.connection.clone()
    }
}
