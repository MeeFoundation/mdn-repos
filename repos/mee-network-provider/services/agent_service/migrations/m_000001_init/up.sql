CREATE TABLE IF NOT EXISTS issued_access_tokens(
  record_id SERIAL PRIMARY KEY,
  record_uid TEXT UNIQUE NOT NULL,
  token_iss TEXT NOT NULL,
  token_aud TEXT NOT NULL,
  token_sub TEXT NOT NULL,
  token_nonce TEXT,
  token_auth_time TIMESTAMP,
  token_iat TIMESTAMP NOT NULL,
  token_exp TIMESTAMP NOT NULL,
  refresh_token TEXT NOT NULL
);
