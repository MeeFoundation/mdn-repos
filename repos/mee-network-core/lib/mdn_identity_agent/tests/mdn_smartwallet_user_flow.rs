use mdn_identity_agent::native_agent::identity_agent_controller::{
    MdnIdentityAgentController, MdnIdentityAgentControllerConfig, MdnIdentityAgentControllerImpl,
    MdnIdentityAgentControllerInitStatus,
};
use mee_test_utils::cargo_target_level_filename;
use std::sync::Arc;
use tracing_subscriber::{filter::LevelFilter, EnvFilter};

async fn create_identity_agent_controller_instance(
    MdnIdentityAgentControllerConfig {
        local_db_file_path,
        mdn_api_base_url,
    }: MdnIdentityAgentControllerConfig,
) -> Arc<dyn MdnIdentityAgentController> {
    let identity_agent_ctl =
        MdnIdentityAgentControllerImpl::try_new(MdnIdentityAgentControllerConfig {
            local_db_file_path,
            mdn_api_base_url,
        })
        .await
        .unwrap();

    Arc::new(identity_agent_ctl)
}

#[ignore = "requires external services"]
#[tokio::test]
async fn mdn_smartwallet_user_flow() {
    tracing_subscriber::fmt()
        .with_env_filter(
            EnvFilter::builder()
                .with_default_directive(LevelFilter::DEBUG.into())
                .parse("")
                .unwrap(),
        )
        .init();

    let local_db_file_path = cargo_target_level_filename!("mdn_smartwallet_user_flow_local_db1");

    log::info!(
        "remove old db: {:?}",
        std::fs::remove_file(&local_db_file_path)
    );

    let identity_agent_ctl =
        create_identity_agent_controller_instance(MdnIdentityAgentControllerConfig {
            local_db_file_path,
            mdn_api_base_url: "http://127.0.0.1:8899".parse().unwrap(),
        })
        .await;

    let email = "alice@email.com";
    let password = "alice_password";

    if let MdnIdentityAgentControllerInitStatus::LoginRequired =
        identity_agent_ctl.init().await.unwrap()
    {
        let res = identity_agent_ctl
            .mdn_user_account_manager()
            .register(email.to_string(), password.to_string())
            .await;

        log::info!("Registration result: {res:#?}");

        identity_agent_ctl
            .mdn_user_account_manager()
            .login(email.to_string(), password.to_string())
            .await
            .unwrap();

        if let MdnIdentityAgentControllerInitStatus::LoginRequired =
            identity_agent_ctl.init().await.unwrap()
        {
            panic!("Something goes wrong with the user login");
        }
    };

    let auth_token = identity_agent_ctl
        .mdn_user_account_manager()
        .get_user_auth_decoded_token_required()
        .await
        .unwrap();

    let mdn_node_manager = identity_agent_ctl.mdn_node_manager();

    // creates context for itself
    mdn_node_manager
        .create_context(
            auth_token.mdn_user_custodian_uid,
            "Alice self-custodian context".to_string(),
        )
        .await
        .unwrap();

    let mut ctxs = mdn_node_manager.list_contexts().await.unwrap();

    assert!(ctxs.len() > 0);

    let Some(ctx) = ctxs.pop() else {
        panic!("empty context list");
    };

    let phone_path = "phone";
    let phone_value = "123";

    mdn_node_manager
        .write_context_data(
            &ctx.mdn_identity_context_uid,
            phone_path,
            phone_value.as_bytes().to_vec(),
        )
        .await
        .unwrap();

    let res = mdn_node_manager
        .read_context_data(&ctx.context_scoped_subject_uid, phone_path)
        .await
        .unwrap();

    assert_eq!(vec![phone_value.as_bytes()], res);
}
