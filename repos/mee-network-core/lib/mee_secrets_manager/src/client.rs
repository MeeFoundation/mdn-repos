use std::io::ErrorKind;

#[async_trait::async_trait]
pub trait SecretsManagerClient {
    async fn get_secret(&self, key: &str) -> Result<Option<Vec<u8>>, anyhow::Error>;
    async fn set_secret(&self, key: &str, val: Vec<u8>) -> Result<(), anyhow::Error>;
    async fn del_secret(&self, key: &str) -> Result<Option<()>, anyhow::Error>;
}

pub struct SimpleFileSecretsManagerClient {
    base_path: String,
}

impl SimpleFileSecretsManagerClient {
    pub fn new(base_path: String) -> Self {
        Self { base_path }
    }

    fn file_path(&self, key: &str) -> String {
        if self.base_path.is_empty() {
            key.to_string()
        } else {
            format!("{}/{}", self.base_path, key)
        }
    }
}

fn handle_file_not_found<T>(res: Result<T, std::io::Error>) -> anyhow::Result<Option<T>> {
    Ok(match res {
        Ok(v) => Some(v),
        Err(e) => {
            if let ErrorKind::NotFound = e.kind() {
                None
            } else {
                Err(e)?
            }
        }
    })
}

#[async_trait::async_trait]
impl SecretsManagerClient for SimpleFileSecretsManagerClient {
    async fn get_secret(&self, key: &str) -> Result<Option<Vec<u8>>, anyhow::Error> {
        let res = tokio::fs::read(self.file_path(key)).await;

        handle_file_not_found(res)
    }
    async fn set_secret(&self, key: &str, val: Vec<u8>) -> Result<(), anyhow::Error> {
        tokio::fs::write(self.file_path(key), val).await?;

        Ok(())
    }
    async fn del_secret(&self, key: &str) -> Result<Option<()>, anyhow::Error> {
        let res = tokio::fs::remove_file(self.file_path(key)).await;

        handle_file_not_found(res)
    }
}
