use crate::sql_storage::{RbdStorage, RdbStorageConfig};
use sea_orm_migration::MigratorTrait;

pub async fn run_db_migrator<M>(
    conf: impl Into<RdbStorageConfig>,
) -> anyhow::Result<()>
where
    M: MigratorTrait,
{
    tracing_subscriber::fmt::try_init().map_err(|e| anyhow::anyhow!(e))?;

    RbdStorage::try_new::<M>(conf.into()).await?;

    Ok(())
}
