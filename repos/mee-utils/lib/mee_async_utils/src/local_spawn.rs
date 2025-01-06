use tokio::{runtime::Builder, sync::mpsc, task::LocalSet};

#[async_trait::async_trait(?Send)]
pub trait TaskRunner {
    async fn run(self);
}

pub struct LocalSpawner<T> {
    send: mpsc::UnboundedSender<T>,
}

impl<T> Clone for LocalSpawner<T> {
    fn clone(&self) -> Self {
        Self {
            send: self.send.clone(),
        }
    }
}

impl<T: TaskRunner + Send + 'static> LocalSpawner<T> {
    pub fn try_new() -> anyhow::Result<Self> {
        let (send, mut recv) = mpsc::unbounded_channel::<T>();

        let rt = Builder::new_current_thread().enable_all().build()?;

        std::thread::spawn(move || {
            let local = LocalSet::new();

            local.spawn_local(async move {
                while let Some(new_task) = recv.recv().await {
                    tokio::task::spawn_local(new_task.run());
                }
            });

            rt.block_on(local);
        });

        Ok(Self { send })
    }

    pub fn spawn(&self, task: T) -> anyhow::Result<()> {
        self.send
            .send(task)
            .map_err(|_| anyhow::anyhow!("Thread with LocalSet has shut down."))?;

        Ok(())
    }
}

#[tokio::test]
async fn enum_task() {
    use tokio::sync::oneshot;

    #[derive(Debug)]
    enum Task {
        PrintNumber(u32),
        AddOne(u32, oneshot::Sender<u32>),
    }

    #[async_trait::async_trait(?Send)]
    impl TaskRunner for Task {
        async fn run(self) {
            match self {
                Task::PrintNumber(n) => {
                    println!("{}", n);
                }
                Task::AddOne(n, response) => {
                    let _ = response.send(n + 1);
                }
            }
        }
    }

    let spawner = LocalSpawner::try_new().unwrap();

    let (send, response) = oneshot::channel();

    spawner.spawn(Task::AddOne(10, send)).unwrap();
    spawner.spawn(Task::PrintNumber(123)).unwrap();

    let eleven = response.await.unwrap();
    assert_eq!(eleven, 11);
}
