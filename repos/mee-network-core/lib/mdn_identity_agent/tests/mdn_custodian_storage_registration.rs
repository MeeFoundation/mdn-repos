use mdn_identity_agent::agent_device::identity_agent_controller::{
    MdnIdentityAgentController, MdnIdentityAgentControllerConfig,
};
use mee_test_utils::cargo_target_level_filename;
use tracing_subscriber::{filter::LevelFilter, EnvFilter};

#[tokio::test]
async fn mdn_custodian_storage_registration_flow() {
    tracing_subscriber::fmt()
        .with_env_filter(
            EnvFilter::builder()
                .with_default_directive(LevelFilter::DEBUG.into())
                .parse("")
                .unwrap(),
        )
        .init();

    let local_db_file_path =
        cargo_target_level_filename!("mdn_custodian_storage_registration_flow_local_db1");

    log::info!(
        "remove old db: {:?}",
        std::fs::remove_file(&local_db_file_path)
    );

    let identity_agent_ctl =
        MdnIdentityAgentController::try_new(MdnIdentityAgentControllerConfig {
            local_db_file_path,
            mdn_api_base_url: "http://127.0.0.1:8899".parse().unwrap(),
        })
        .await
        .unwrap();

    let email = "alice@email.com";
    let password = "alice_password";

    let res = identity_agent_ctl
        .mdn_user_account_manager
        .register(email.to_string(), password.to_string())
        .await;

    log::info!("Registration result: {res:#?}");

    identity_agent_ctl
        .mdn_user_account_manager
        .login(email.to_string(), password.to_string())
        .await
        .unwrap();

    identity_agent_ctl
        .mdn_user_account_manager
        .get_user_auth_decoded_token_required()
        .await
        .unwrap();

    identity_agent_ctl
        .mdn_user_nodes_manager
        .register()
        .await
        .unwrap();

    let custodian_storages = identity_agent_ctl
        .mdn_user_nodes_manager
        .list_all()
        .await
        .unwrap();

    assert!(custodian_storages.len() > 0);

    log::info!("custodian_storages: {custodian_storages:#?}");

    identity_agent_ctl
        .mdn_capabilities_manager
        .issue_owner_context_ops_cap()
        .await
        .unwrap();

    let ctx_ops_caps = identity_agent_ctl
        .mdn_capabilities_manager
        .context_ops_caps()
        .await
        .unwrap();

    assert!(ctx_ops_caps.len() > 0);

    log::info!("ctx_ops_caps: {ctx_ops_caps:#?}");
}
