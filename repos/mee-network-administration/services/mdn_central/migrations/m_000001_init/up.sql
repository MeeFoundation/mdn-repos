CREATE TABLE IF NOT EXISTS mdn_users(
  mdn_user_id bigint generated always as identity primary key,
  mdn_user_uid varchar unique not null,
  mdn_user_email varchar unique not null,
  mdn_user_phone varchar unique,
  mdn_user_name varchar,
  mdn_user_role varchar not null,
  is_user_active boolean not null,
  is_user_verified boolean not null,
  salt varchar not null,
  password varchar not null
);

CREATE TABLE IF NOT EXISTS mdn_providers(
  mdn_provider_id bigint generated always as identity primary key,
  mdn_provider_uid varchar unique not null,
  mdn_provider_email varchar unique not null,
  mdn_provider_name varchar,
  mdn_provider_role varchar not null,
  is_provider_active boolean not null,
  is_provider_verified boolean not null,
  salt varchar not null,
  password varchar not null
);

CREATE TABLE IF NOT EXISTS mdn_custodians(
  mdn_custodian_id bigint generated always as identity primary key,
  mdn_custodian_uid varchar unique not null,
  mdn_user_custodian_id bigint,
  FOREIGN KEY (mdn_user_custodian_id) REFERENCES mdn_users(mdn_user_id),
  mdn_provider_custodian_id bigint,
  FOREIGN KEY (mdn_provider_custodian_id) REFERENCES mdn_providers(mdn_provider_id)
);

CREATE TABLE IF NOT EXISTS mdn_nodes(
  mdn_node_id bigint generated always as identity primary key,
  mdn_node_uid varchar unique not null,
  mdn_node_willow_peer_id varchar not null,
  mdn_node_iroh_node_id varchar not null,
  mdn_node_custodian_id bigint not null,
  FOREIGN KEY (mdn_node_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_context_scoped_ids(
  mdn_context_scoped_id bigint generated always as identity primary key,
  mdn_context_scoped_uid varchar unique not null,
  mdn_user_id bigint,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  for_mdn_custodian_id bigint not null,
  FOREIGN KEY (for_mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_node_signing_pub_keys(
  mdn_node_signing_pub_key_id bigint generated always as identity primary key,
  mdn_node_signing_pub_key_did varchar unique not null,
  mdn_node_id bigint not null,
  FOREIGN KEY (mdn_node_id) REFERENCES mdn_nodes(mdn_node_id)
);

CREATE TABLE IF NOT EXISTS mdn_custodian_context_operation_caps(
  mdn_custodian_context_operation_cap_id bigint generated always as identity primary key,
  mdn_custodian_context_operation_cap_uid varchar unique not null,
  mdn_custodian_context_operation_cap_token varchar not null,
  from_mdn_user_id bigint,
  FOREIGN KEY (from_mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  to_mdn_custodian_id bigint not null,
  FOREIGN KEY (to_mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_identity_contexts(
  mdn_identity_context_id bigint generated always as identity primary key,
  mdn_identity_context_uid varchar unique not null,
  willow_namespace_id varchar not null,
  mdn_subject_id bigint not null,
  FOREIGN KEY (mdn_subject_id) REFERENCES mdn_context_scoped_ids(mdn_context_scoped_id)
);

CREATE TABLE IF NOT EXISTS mdn_custodian_context_data_access_caps(
  mdn_custodian_context_data_access_cap_id bigint generated always as identity primary key,
  mdn_custodian_context_data_access_cap_uid varchar unique not null,
  mdn_custodian_context_data_access_cap_token varchar not null,
  mdn_identity_context_id bigint not null,
  FOREIGN KEY (mdn_identity_context_id) REFERENCES mdn_identity_contexts(mdn_identity_context_id),
  from_mdn_user_id bigint,
  FOREIGN KEY (from_mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  to_mdn_custodian_id bigint not null,
  FOREIGN KEY (to_mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_identity_contexts_on_nodes(
  mdn_identity_context_on_node_id bigint generated always as identity primary key,
  mdn_identity_context_on_node_uid varchar unique not null,
  mdn_identity_context_id bigint not null,
  FOREIGN KEY (mdn_identity_context_id) REFERENCES mdn_identity_contexts(mdn_identity_context_id),
  mdn_node_id bigint not null,
  FOREIGN KEY (mdn_node_id) REFERENCES mdn_nodes(mdn_node_id)
);

CREATE TABLE IF NOT EXISTS mdn_node_caps(
  mdn_node_cap_id bigint generated always as identity primary key,
  mdn_node_cap_uid varchar unique not null,
  mdn_node_willow_cap_token varchar not null,
  mdn_custodian_context_data_access_cap_id bigint not null,
  FOREIGN KEY (mdn_custodian_context_data_access_cap_id) REFERENCES mdn_custodian_context_data_access_caps(mdn_custodian_context_data_access_cap_id),
  mdn_identity_context_on_node_id bigint not null,
  FOREIGN KEY (mdn_identity_context_on_node_id) REFERENCES mdn_identity_contexts_on_nodes(mdn_identity_context_on_node_id)
);
