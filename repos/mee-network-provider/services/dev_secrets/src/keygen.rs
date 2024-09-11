use clap::Parser;
use mee_secrets_manager::dev_keygen::{keygen_init, KeyGenInitParams};

#[tokio::main(flavor = "current_thread")]
async fn main() -> anyhow::Result<()> {
    keygen_init(KeyGenInitParams::parse()).await?;

    Ok(())
}
