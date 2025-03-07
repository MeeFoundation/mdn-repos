use iroh_base::SecretKey;

pub fn create_iroh_secret_key() -> SecretKey {
    let rng = rand::thread_rng();
    let iroh_node_secret_key = SecretKey::generate(rng);

    iroh_node_secret_key
}
