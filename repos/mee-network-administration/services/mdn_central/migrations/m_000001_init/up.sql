CREATE TABLE IF NOT EXISTS mdn_users(
  mdn_user_id bigint generated always as identity primary key,
  mdn_user_uid varchar unique not null,
  mdn_user_email varchar unique not null,
  mdn_user_phone varchar unique,
  mdn_user_name varchar,
  mdn_user_role varchar not null,
  mdn_user_created_at timestamp with time zone not null,
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
  mdn_provider_created_at timestamp with time zone not null,
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

CREATE TABLE IF NOT EXISTS mdn_custodian_storages(
  mdn_custodian_storage_id bigint generated always as identity primary key,
  mdn_custodian_storage_uid varchar unique not null,
  willow_peer_id varchar not null,
  iroh_node_id varchar not null,
  mdn_custodian_id bigint not null,
  FOREIGN KEY (mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_context_scoped_ids(
  mdn_context_scoped_id bigint generated always as identity primary key,
  mdn_context_scoped_uid varchar unique not null,
  mdn_user_id bigint not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  for_mdn_custodian_id bigint not null,
  FOREIGN KEY (for_mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_user_signing_pub_keys(
  mdn_user_signing_pub_key_id bigint generated always as identity primary key,
  mdn_user_signing_pub_key_did varchar unique not null,
  mdn_custodian_storage_id bigint,
  FOREIGN KEY (mdn_custodian_storage_id) REFERENCES mdn_custodian_storages(mdn_custodian_storage_id),
  mdn_user_id bigint not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id)
);

CREATE TABLE IF NOT EXISTS mdn_custodian_context_operation_caps(
  mdn_custodian_context_operation_cap_id bigint generated always as identity primary key,
  mdn_custodian_context_operation_cap_uid varchar unique not null,
  mdn_custodian_context_operation_cap_token varchar not null,
  mdn_custodian_context_operation_cap_expires timestamp with time zone not null,
  from_mdn_user_id bigint not null,
  FOREIGN KEY (from_mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  to_mdn_custodian_id bigint not null,
  FOREIGN KEY (to_mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_identity_contexts(
  mdn_identity_context_id bigint generated always as identity primary key,
  mdn_identity_context_uid varchar unique not null,
  willow_namespace_id varchar not null,
  context_scoped_subject_id bigint not null,
  FOREIGN KEY (context_scoped_subject_id) REFERENCES mdn_context_scoped_ids(mdn_context_scoped_id)
);

CREATE TABLE IF NOT EXISTS mdn_custodian_context_data_access_caps(
  mdn_custodian_context_data_access_cap_id bigint generated always as identity primary key,
  mdn_custodian_context_data_access_cap_uid varchar unique not null,
  mdn_custodian_context_data_access_cap_token varchar not null,
  mdn_custodian_context_data_access_cap_expires timestamp with time zone not null,
  mdn_identity_context_id bigint not null,
  FOREIGN KEY (mdn_identity_context_id) REFERENCES mdn_identity_contexts(mdn_identity_context_id),
  from_mdn_user_id bigint,
  FOREIGN KEY (from_mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  to_mdn_custodian_id bigint not null,
  FOREIGN KEY (to_mdn_custodian_id) REFERENCES mdn_custodians(mdn_custodian_id)
);

CREATE TABLE IF NOT EXISTS mdn_identity_contexts_in_storages(
  mdn_identity_context_in_storage_id bigint generated always as identity primary key,
  mdn_identity_context_in_storage_uid varchar unique not null,
  mdn_identity_context_id bigint not null,
  FOREIGN KEY (mdn_identity_context_id) REFERENCES mdn_identity_contexts(mdn_identity_context_id),
  mdn_custodian_storage_id bigint not null,
  FOREIGN KEY (mdn_custodian_storage_id) REFERENCES mdn_custodian_storages(mdn_custodian_storage_id)
);

CREATE TABLE IF NOT EXISTS mdn_custodian_storage_caps(
  mdn_custodian_storage_cap_id bigint generated always as identity primary key,
  mdn_custodian_storage_cap_uid varchar unique not null,
  mdn_custodian_storage_willow_cap_token varchar not null,
  mdn_custodian_context_data_access_cap_id bigint not null,
  FOREIGN KEY (mdn_custodian_context_data_access_cap_id) REFERENCES mdn_custodian_context_data_access_caps(mdn_custodian_context_data_access_cap_id),
  mdn_identity_context_in_storage_id bigint not null,
  FOREIGN KEY (mdn_identity_context_in_storage_id) REFERENCES mdn_identity_contexts_in_storages(mdn_identity_context_in_storage_id)
);
