use crate::{
    app_ctl::AppCtl, config::AppConfig,
    domain::oidc::router::OAUTH2_AUTHORIZE_PATH,
};
use axum::{
    extract::{Query, Request},
    response::IntoResponse,
    routing::get,
    Router,
};

use serde::{Deserialize, Serialize};
use serde_json::json;
use std::{collections::HashMap, time::Duration};
use tokio::{
    net::TcpListener,
    select,
    sync::mpsc::{self, Sender},
    time::sleep,
};
use tracing::level_filters::LevelFilter;
use tracing_subscriber::EnvFilter;
use url::Url;
use uuid::Uuid;

const MEE_OIDC_SERVER_HOST: &str = "127.0.0.1";
const ITS_MEE_SERVER_PORT: u16 = 8003;

const OIDC_CLIENT_HOST: &str = "127.0.0.1";
const OIDC_CLIENT_PORT: u16 = 8013;

#[derive(Debug, Deserialize)]
pub struct OidcCodeParam {
    code: String,
    state: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct MeeOidcResponse {
    pub token_type: String,
    pub scope: String,
    pub access_token: String,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub refresh_token: Option<String>,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub expires_in: Option<i64>,

    #[serde(skip_serializing_if = "Option::is_none")]
    pub error: Option<String>,
}

const OIDC_REDIRECT_PATH: &str = "/oauth2redirect";

async fn oidc_client_endpoint(
    oidc_params: Option<Query<OidcCodeParam>>,
    req: Request,
    redirect_uri: String,
    client_id: String,
    state: String,
    _app_config: AppConfig,
    ready_tx: Sender<Result<(), String>>,
) -> impl IntoResponse {
    println!("redirection: {req:#?}");

    assert_eq!(
        Some(state.as_str()),
        oidc_params.as_ref().map(|p| p.state.as_str())
    );

    let client = reqwest::Client::new();

    let mut params = HashMap::new();
    params.insert("grant_type", "authorization_code");

    if let Some(ref code) = oidc_params {
        params.insert("code", &code.0.code);
    }

    params.insert("redirect_uri", &redirect_uri);
    params.insert("client_id", &client_id);

    let r = client
        .post(format!(
            "http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/oauth2/token"
        ))
        .form(&params)
        .build()
        .unwrap();

    let res = client.execute(r).await.unwrap().text().await.unwrap();

    println!("MeeOidcResponse: {}", res);

    match serde_json::from_str::<MeeOidcResponse>(&res) {
        Ok(v) => {
            // let mee_authority_service =
            //     MeeAuthoritySignatureServiceDefault::new(
            //         app_config.mee_signature_secret_path.clone(),
            //         Arc::new(SimpleFileSecretsManagerClient::new(format!(
            //             "{}/../target",
            //             env!("CARGO_MANIFEST_DIR")
            //         ))),
            //     );

            // let biscuit = mee_authority_service
            //     .parse_mee_issued_biscuit(&v.access_token)
            //     .await
            //     .unwrap();

            // mee_authority_service
            //     .is_biscuit_expired(&biscuit)
            //     .await
            //     .unwrap();

            ready_tx.send(Ok(())).await.unwrap();

            serde_json::to_string_pretty(&v).unwrap()
        }
        Err(e) => {
            let err = serde_json::to_string_pretty(&json!({
                "error": e.to_string(),
                "original_response": res,
            }))
            .unwrap();

            ready_tx.send(Err(err.clone())).await.unwrap();

            err
        }
    }
}

async fn run_oidc_client_handler(
    redirect_uri: String,
    client_id: String,
    state: String,
    app_config: AppConfig,
    ready_tx: Sender<Result<(), String>>,
) {
    let listener =
        TcpListener::bind(format!("{OIDC_CLIENT_HOST}:{OIDC_CLIENT_PORT}"))
            .await
            .unwrap();

    let app = Router::new().route(
        OIDC_REDIRECT_PATH,
        get(|oidc_params: Option<Query<OidcCodeParam>>, req: Request| {
            oidc_client_endpoint(
                oidc_params,
                req,
                redirect_uri,
                client_id,
                state,
                app_config,
                ready_tx,
            )
        }),
    );

    tokio::spawn(async move {
        axum::serve(listener, app).await.unwrap();
    });
}

// TODO: move the test to a separate integration testing crate with user/provider/oidc client creation automation
#[ignore = "requires manual interactions"]
#[tokio::test]
async fn oidc_client() {
    tracing_subscriber::fmt()
        .with_env_filter(
            EnvFilter::builder()
                .with_default_directive(LevelFilter::DEBUG.into())
                .parse("")
                .unwrap(),
        )
        .init();

    let app_config = AppConfig {
        oidc_issuer:format!("http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}").parse().unwrap(),
        oidc_authorization_endpoint:format!("http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/oauth2/authorize").parse().unwrap(),
        oidc_token_endpoint:format!("http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/oauth2/token").parse().unwrap(),
        oidc_jwks_uri:format!("http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/jwks.json").parse().unwrap(),
        server_host:MEE_OIDC_SERVER_HOST.to_string(),
        server_port:ITS_MEE_SERVER_PORT,
        database_url:"sqlite://../target/mee_oidc_provider.sqlite?mode=rwc".parse().unwrap(),
        mdn_license_manager_url: "http://127.0.0.1:8008".parse().unwrap(),
        user_manager_url: "http://127.0.0.1:8000".parse().unwrap(),
        provider_manager_url: "http://127.0.0.1:8001".parse().unwrap(),
        mee_signature_secret_path: "../target/dev_mee_signature".to_string(),
        inter_service_api_secret: "inter_service_api_secret".to_string(),
        db_pool_size: 5
    };

    let itsmeeserver = tokio::spawn({
        let app_config = app_config.clone();

        async {
            AppCtl::try_new(Some(app_config))
                .await
                .unwrap()
                .run()
                .await
                .unwrap();
        }
    });

    let http_client = reqwest::ClientBuilder::new().build().unwrap();

    loop {
        let res = http_client
            .get(format!(
                "http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/health"
            ))
            .send()
            .await;

        let reason = match res {
            Ok(res) => {
                if res.status().is_success() {
                    break;
                } else {
                    format!("{:?}", res.text().await)
                }
            }
            Err(e) => e.to_string(),
        };

        println!("itsmeeorg is not ready yet: {:?}", reason);
        sleep(Duration::from_secs(1)).await;
    }

    // let user_email = "bob_user@mail.com";
    // let user_password = "bob_user";

    // let _logged_in_user: Result<MeeNetworkUserLoginResponse, String> = json_response_handle_error(
    //     http_client
    //         .post(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/users/register"))
    //         .json(&json!({
    //             "email": user_email,
    //             "password": user_password
    //         }))
    //         .send()
    //         .await
    //         .unwrap(),
    //     std::convert::identity,
    // )
    // .await;

    // let email = "oyt_provider@mail.com";
    // let password = "oyt_provider";

    // let _logged_in_provider: Result<MeeNetworkProviderLoginResponse, String> = json_response_handle_error(
    //     http_client
    //         .post(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/providers/register"))
    //         .json(&json!({
    //             "email": email,
    //             "password": password
    //         }))
    //         .send()
    //         .await
    //         .unwrap(),
    //     std::convert::identity,
    // )
    // .await;

    // let logged_in_provider: MeeNetworkProviderLoginResponse = json_response_handle_error(
    //     http_client
    //         .post(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/providers/login"))
    //         .json(&json!({
    //             "email": email,
    //             "password": password
    //         }))
    //         .send()
    //         .await
    //         .unwrap(),
    //     std::convert::identity,
    // )
    // .await.unwrap();

    // let submitted_provider: Result<MeeNetworkHilApplicationResponse, String> = json_response_handle_error(
    //     http_client
    //         .post(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/providers/hil_application_draft"))
    //         .json(&json!({
    //             "contact_email": email,
    //             "company_name": "Olde York Times",
    //             "cloud_node_discovery_url": format!("http://127.0.0.1:9000"),
    //             "decentralized_id": "did:key:z6MkgyCnyynXHNsYggg3QAUK22gBmktMfbJeHy3gf2BPDeas"
    //         }))
    //         .bearer_auth(&logged_in_provider.auth_token)
    //         .send()
    //         .await
    //         .unwrap(),
    //     std::convert::identity,
    // )
    // .await;

    // if let Ok(submitted_provider) = submitted_provider {
    //     let _approved_provider: Result<MeeNetworkHilApplicationResponse, String> = json_response_handle_error(
    //         http_client
    //             .post(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/providers/submit_hil_application"))
    //             .json(&json!({
    //                 "application_uid": submitted_provider.application_uid,
    //             }))
    //             .bearer_auth(&logged_in_provider.auth_token)
    //             .send()
    //             .await
    //             .unwrap(),
    //         std::convert::identity,
    //     )
    //     .await;
    // }

    let redirect_uri = format!(
        "http://{OIDC_CLIENT_HOST}:{OIDC_CLIENT_PORT}{OIDC_REDIRECT_PATH}"
    );

    let client_id =
        "a05b325a-1e33-424c-b29e-3e35b9a93640.itsmee.org".to_string();

    // let registered_oidc_client: OidcProviderRegistrarCreateResponse = json_response_handle_error(
    //     http_client
    //         .post(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/providers/oidc_client"))
    //         .json(&json!({
    //             "redirect_uri": redirect_uri
    //         }))
    //         .bearer_auth(&logged_in_provider.auth_token)
    //         .send()
    //         .await
    //         .unwrap(),
    //     std::convert::identity,
    // )
    // .await
    // .unwrap();

    // loop {
    //     let oidc_client: Option<MeeNetworkHilApplicationReadResponse> = json_response_handle_error(
    //         http_client
    //             .get(format!("http://{ITS_MEE_SERVER_HOST}:{ITS_MEE_SERVER_PORT}/api/v1/providers/oidc_client/{}", registered_oidc_client.client_id))
    //             .bearer_auth(&logged_in_provider.auth_token)
    //             .send()
    //             .await
    //             .unwrap(),
    //         std::convert::identity,
    //     )
    //     .await
    //     .unwrap();

    //     if oidc_client.is_some() {
    //         break;
    //     }

    //     sleep(Duration::from_secs(1)).await;
    // }

    let state = Uuid::new_v4().to_string();

    let (ready_tx, mut ready_rx) = mpsc::channel(1);

    tokio::spawn({
        let state = state.clone();
        let redirect_uri = redirect_uri.clone();
        let client_id = client_id.clone();

        async {
            run_oidc_client_handler(
                redirect_uri,
                client_id,
                state,
                app_config,
                ready_tx,
            )
            .await;
        }
    });

    let mut url: Url =
        format!("http://{MEE_OIDC_SERVER_HOST}:{ITS_MEE_SERVER_PORT}{OAUTH2_AUTHORIZE_PATH}")
            .parse()
            .unwrap();

    url.query_pairs_mut()
        .append_pair("scope", "openid")
        .append_pair("response_type", "code")
        .append_pair("client_id", &client_id)
        .append_pair("redirect_uri", &redirect_uri)
        .append_pair("state", &state);

    webbrowser::open(url.as_ref()).unwrap();

    let res: Result<(), String> = select! {
        _ = sleep(Duration::from_secs(60)) => {
            Err("test timeout".to_string())
        },
        _ = itsmeeserver => {
            Err("itsmeeserver has shuted down".to_string())
        }
        r = ready_rx.recv() => {
            r.unwrap()
        }
    };

    res.unwrap();
}
