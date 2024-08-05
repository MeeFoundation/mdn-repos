use mee_data_sync::{
    mdn::agent_data_node::{MdnAgentDataNode, MdnAgentDataNodeWillowImpl},
    willow::peer::WillowPeer,
};
use rand_chacha::{rand_core::SeedableRng, ChaCha12Rng};

pub fn create_rng(seed: &str) -> ChaCha12Rng {
    let seed = iroh_base::hash::Hash::new(seed);
    ChaCha12Rng::from_seed(*(seed.as_bytes()))
}

#[tokio::test]
async fn data_write_data_read() -> anyhow::Result<()> {
    let mut rng = create_rng("MDN smoke");
    let iroh_node_secret_key = iroh_net::key::SecretKey::generate_with_rng(&mut rng);
    let willow_peer = WillowPeer::new(iroh_node_secret_key).await?;

    let mdn = MdnAgentDataNodeWillowImpl::new(willow_peer, "oyt".to_string()).await?;

    let user_id = "alice";
    let attribute_name = "address";
    let sub_attribute_path = ["city"];
    let city = "Rome";

    mdn.set_user_data(
        user_id,
        attribute_name,
        &sub_attribute_path,
        city.as_bytes().to_vec(),
    )
    .await?;

    let res = mdn
        .get_user_data(user_id, attribute_name, &sub_attribute_path)
        .await?
        .pop()
        .unwrap();

    assert_eq!(res.value, city.as_bytes());

    Ok(())
}
