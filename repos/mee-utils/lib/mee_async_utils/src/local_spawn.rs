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
    pub fn new() -> Self {
        let (send, mut recv) = mpsc::unbounded_channel::<T>();

        let rt = Builder::new_current_thread().enable_all().build().unwrap();

        std::thread::spawn(move || {
            let local = LocalSet::new();

            local.spawn_local(async move {
                while let Some(new_task) = recv.recv().await {
                    tokio::task::spawn_local(new_task.run());
                }
            });

            rt.block_on(local);
        });

        Self { send }
    }

    pub fn spawn(&self, task: T) {
        self.send
            .send(task)
            .expect("Thread with LocalSet has shut down.");
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

    let spawner = LocalSpawner::new();

    let (send, response) = oneshot::channel();

    spawner.spawn(Task::AddOne(10, send));
    spawner.spawn(Task::PrintNumber(123));

    let eleven = response.await.unwrap();
    assert_eq!(eleven, 11);
}
