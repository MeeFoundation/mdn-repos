use crate::error::MeeDataSyncResult;
use iroh_net::{ticket::NodeTicket, Endpoint, NodeId};
use iroh_willow::{
    engine::{AcceptOpts, Engine},
    ALPN,
};
use mee_macro_utils::let_clone;
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
            .relay_mode(iroh_net::relay::RelayMode::Disabled)
            .alpns(vec![ALPN.to_vec()])
            .bind()
            .await?;

        let addr = endpoint.node_addr().await?;
        let node_ticket = NodeTicket::new(addr.clone())?;

        log::info!(
            "iroh node ({}) has started. Node ticket: {node_ticket}",
            addr.node_id
        );

        let payloads = iroh_blobs::store::mem::Store::default();
        let create_store = move || iroh_willow::store::memory::Store::new(payloads);
        let engine = Engine::spawn(endpoint.clone(), create_store, accept_opts);

        let accept_task = tokio::task::spawn({
            let_clone!(engine);
            let_clone!(endpoint);

            async move {
                while let Some(incoming) = endpoint.accept().await {
                    let Ok(mut connecting) = incoming.accept() else {
                        continue;
                    };
                    let Ok(alpn) = connecting.alpn().await else {
                        continue;
                    };
                    if alpn != ALPN {
                        continue;
                    }
                    let Ok(conn) = connecting.await else {
                        continue;
                    };
                    engine.handle_connection(conn).await?;
                }
                Result::Ok(())
            }
        });

        Ok(Self {
            endpoint,
            engine,
            accept_task: Arc::new(Mutex::new(Some(accept_task))),
        })
    }

    pub async fn shutdown(self) -> MeeDataSyncResult<()> {
        let accept_task = self.accept_task.lock()?.take();

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
    pub fn endpoint(&self) -> Endpoint {
        self.endpoint.clone()
    }
    pub fn engine(&self) -> Engine {
        self.engine.clone()
    }
}
