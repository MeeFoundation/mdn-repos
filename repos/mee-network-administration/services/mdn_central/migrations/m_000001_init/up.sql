CREATE TABLE IF NOT EXISTS mdn_users(
  mdn_user_id bigint GENERATED ALWAYS AS IDENTITY primary key,
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

CREATE TABLE IF NOT EXISTS mdn_user_devices(
  mdn_user_device_id bigint GENERATED ALWAYS AS IDENTITY primary key,
  mdn_user_device_uid varchar unique not null,
  mdn_user_id bigint not null,
  device_description varchar not null,
  is_device_linked boolean not null,
  device_did varchar not null,
  willow_peer_id varchar not null,
  iroh_node_id varchar not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id)
);

CREATE TABLE IF NOT EXISTS mdn_user_device_replication_capabilities(
  mdn_user_device_replication_capability_id bigint GENERATED ALWAYS AS IDENTITY primary key,
  mdn_user_id bigint not null,
  from_device_id bigint not null,
  to_device_id bigint not null,
  willow_capabilities varchar not null,
  expires timestamptz not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  FOREIGN KEY (from_device_id) REFERENCES mdn_user_devices(mdn_user_device_id),
  FOREIGN KEY (to_device_id) REFERENCES mdn_user_devices(mdn_user_device_id)
);

CREATE TABLE IF NOT EXISTS mdn_user_device_requests_for_linkage(
  mdn_user_device_request_for_linkage_id bigint GENERATED ALWAYS AS IDENTITY primary key,
  mdn_user_device_request_for_linkage_uid varchar unique not null,
  mdn_user_id bigint not null,
  from_device_id bigint not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  FOREIGN KEY (from_device_id) REFERENCES mdn_user_devices(mdn_user_device_id)
);
