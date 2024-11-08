CREATE TABLE IF NOT EXISTS mdn_users(
  mdn_user_id serial primary key,
  mdn_user_uid text unique not null,
  mdn_user_email text unique not null,
  mdn_user_phone text unique,
  mdn_user_name text unique,
  mdn_user_role varchar(255) not null,
  is_user_active boolean not null,
  is_user_verified boolean not null,
  salt text not null,
  password text not null
);

CREATE TABLE IF NOT EXISTS mdn_user_devices(
  mdn_user_device_id serial primary key,
  mdn_user_id integer not null,
  device_description text not null,
  is_device_linked boolean not null,
  device_did varchar(4096) not null,
  willow_peer_id varchar(255) not null,
  iroh_node_id varchar(255) not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id)
);

CREATE TABLE IF NOT EXISTS mdn_user_device_replication_capabilities(
  mdn_user_device_replication_capability_id serial primary key,
  mdn_user_id integer not null,
  from_device_id integer not null,
  to_device_id integer not null,
  willow_capabilities text not null,
  expires timestamp not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  FOREIGN KEY (from_device_id) REFERENCES mdn_user_devices(mdn_user_device_id),
  FOREIGN KEY (to_device_id) REFERENCES mdn_user_devices(mdn_user_device_id)
);

CREATE TABLE IF NOT EXISTS mdn_user_device_requests_for_linkage(
  mdn_user_device_request_for_linkage_id serial primary key,
  mdn_user_id integer not null,
  from_device_id integer not null,
  from_device_signature text not null,
  FOREIGN KEY (mdn_user_id) REFERENCES mdn_users(mdn_user_id),
  FOREIGN KEY (from_device_id) REFERENCES mdn_user_devices(mdn_user_device_id)
);
