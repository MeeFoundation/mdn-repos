use reqwest::Response;
use serde::de::DeserializeOwned;

pub async fn json_response_handle_error<T, E, Fun>(
    res: Response,
    error_wrap: Fun,
) -> Result<T, E>
where
    T: DeserializeOwned,
    Fun: Fn(String) -> E,
{
    if res.status().is_client_error() || res.status().is_server_error() {
        let err = res.text().await.map_err(|e| {
            error_wrap(format!("HTTP response body handling error: {e}"))
        })?;

        Err(error_wrap(format!("HTTP response error: {err}")))?
    } else {
        res.json().await.map_err(|e| error_wrap(e.to_string()))
    }
}

pub async fn any_response_handle_error<Fun, E>(
    res: Response,
    error_wrap: Fun,
) -> Result<Response, E>
where
    Fun: Fn(String) -> E,
{
    if res.status().is_client_error() || res.status().is_server_error() {
        let err = res.text().await.map_err(|e| {
            error_wrap(format!("HTTP response body handling error: {e}"))
        })?;

        Err(error_wrap(format!("HTTP response error: {err}")))?
    } else {
        Ok(res)
    }
}
