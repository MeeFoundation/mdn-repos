use iroh_net::key::SecretKey;

pub fn create_iroh_secret_key() -> SecretKey {
    let mut rng = rand::thread_rng();
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);

    iroh_node_secret_key
}
