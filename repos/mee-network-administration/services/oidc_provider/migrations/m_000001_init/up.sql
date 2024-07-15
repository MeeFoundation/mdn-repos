CREATE TABLE IF NOT EXISTS oidc_provider_registrar(
  record_id SERIAL PRIMARY KEY NOT NULL,
  client_id TEXT NOT NULL,
  client_type TEXT NOT NULL,
  default_scope TEXT NOT NULL,
  redirect_uri TEXT NOT NULL,
  provider_uid TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS oidc_provider_grants(
  record_id SERIAL PRIMARY KEY NOT NULL,
  grant_code TEXT NOT NULL,
  client_id TEXT NOT NULL,
  owner_id TEXT NOT NULL,
  scope TEXT NOT NULL,
  redirect_uri TEXT NOT NULL,
  until TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS oidc_provider_issued_tokens(
  record_id SERIAL PRIMARY KEY NOT NULL,

  token_uid TEXT NOT NULL,
  access_token TEXT NOT NULL,
  refresh_token TEXT NOT NULL,

  grant_client_id TEXT NOT NULL,
  grant_owner_id TEXT NOT NULL,
  grant_scope TEXT NOT NULL,
  grant_redirect_uri TEXT NOT NULL,
  grant_until TEXT NOT NULL
);
