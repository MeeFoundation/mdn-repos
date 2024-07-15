CREATE TABLE IF NOT EXISTS mee_network_persona_model_schemas(
  schema_id SERIAL PRIMARY KEY NOT NULL,
  schema_uid TEXT NOT NULL,
  schema_definition TEXT NOT NULL,
  user_meeid TEXT NOT NULL,
  provider_meeid TEXT NOT NULL
);
