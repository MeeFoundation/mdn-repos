use mdn_identity_agent::mdn_device::agent_device::{MdnAgentDevice, MdnAgentDeviceConfig};
use mee_test_utils::cargo_target_level_filename;
use tracing_subscriber::{filter::LevelFilter, EnvFilter};

#[tokio::test]
async fn device_registration_flow() {
    tracing_subscriber::fmt()
        .with_env_filter(
            EnvFilter::builder()
                .with_default_directive(LevelFilter::DEBUG.into())
                .parse("")
                .unwrap(),
        )
        .init();

    let agent_device = MdnAgentDevice::try_new(MdnAgentDeviceConfig {
        local_db_file_path: cargo_target_level_filename!("device_registration_flow_local_db1"),
        mdn_api_base_url: "http://127.0.0.1:8899".parse().unwrap(),
    })
    .await
    .unwrap();

    let email = "alice@email.com";
    let password = "alice_password";

    let res = agent_device
        .mdn_user_account_manager
        .register(email.to_string(), password.to_string())
        .await;

    log::info!("Registration result: {res:#?}");

    agent_device
        .mdn_user_account_manager
        .login(email.to_string(), password.to_string())
        .await
        .unwrap();

    assert!(agent_device
        .mdn_user_account_manager
        .get_user_auth_token()
        .await
        .unwrap()
        .is_some());

    agent_device
        .mdn_user_devices_manager
        .register(Some("Alice's mobile device".to_string()))
        .await
        .unwrap();

    let devices = agent_device
        .mdn_user_devices_manager
        .list_all()
        .await
        .unwrap();

    assert!(devices.iter().find(|d| d.is_device_linked).is_some());

    log::info!("devices: {devices:#?}");
}
