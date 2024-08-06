use crate::error::{MeeDataSyncErr, MeeDataSyncResult};
use iroh_net::{ticket::NodeTicket, Endpoint, NodeId};
use iroh_willow::{
    engine::{AcceptOpts, Engine},
    net::ALPN,
};
use std::sync::{Arc, Mutex};
use tokio::task::JoinHandle;

#[derive(Debug, Clone)]
pub struct WillowNode {
    pub(crate) endpoint: Endpoint,
    pub(crate) engine: Engine,
    accept_task: Arc<Mutex<Option<JoinHandle<MeeDataSyncResult<()>>>>>,
}

impl WillowNode {
    pub async fn run(
        iroh_node_secret_key: iroh_net::key::SecretKey,
        accept_opts: AcceptOpts,
    ) -> MeeDataSyncResult<Self> {
        let endpoint = Endpoint::builder()
            .secret_key(iroh_node_secret_key)
            .alpns(vec![ALPN.to_vec()])
            .bind(0)
            .await?;

        let node_ticket = NodeTicket::new(endpoint.node_addr().await?)?;
        
        log::info!("iroh node has started. Node ticket: {node_ticket}");

        let payloads = iroh_blobs::store::mem::Store::default();
        let create_store = move || iroh_willow::store::memory::Store::new(payloads);
        let engine = Engine::spawn(endpoint.clone(), create_store, accept_opts);

        let accept_task = tokio::task::spawn({
            let engine = engine.clone();
            let endpoint = endpoint.clone();

            async move {
                while let Some(mut conn) = endpoint.accept().await {
                    let alpn = conn.alpn().await?;

                    if alpn != ALPN {
                        continue;
                    }

                    engine.handle_connection(conn.await?).await?;
                }
                MeeDataSyncResult::Ok(())
            }
        });

        Ok(Self {
            endpoint,
            engine,
            accept_task: Arc::new(Mutex::new(Some(accept_task))),
        })
    }

    pub async fn shutdown(self) -> MeeDataSyncResult<()> {
        let accept_task = self
            .accept_task
            .lock()
            .map_err(|e| MeeDataSyncErr::StdMutex(e.to_string()))?
            .take();

        if let Some(accept_task) = accept_task {
            accept_task.abort();

            match accept_task.await {
                Err(err) if err.is_cancelled() => {}
                Ok(Ok(())) => {}
                Err(err) => Err(err)?,
                Ok(Err(err)) => Err(err)?,
            }
        }

        self.engine.shutdown().await?;
        self.endpoint.close(0u8.into(), b"").await?;

        Ok(())
    }

    pub fn iroh_node_id(&self) -> NodeId {
        self.endpoint.node_id()
    }
}
