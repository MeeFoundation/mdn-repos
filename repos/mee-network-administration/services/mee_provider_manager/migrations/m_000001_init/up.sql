CREATE TABLE IF NOT EXISTS mee_network_providers(
  provider_id SERIAL PRIMARY KEY NOT NULL,
  provider_meeid TEXT UNIQUE NOT NULL,
  provider_email TEXT UNIQUE NOT NULL,
  provider_name TEXT NOT NULL,
  provider_role TEXT NOT NULL,
  is_active BOOLEAN NOT NULL,
  salt TEXT NOT NULL,
  password TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS provider_cloud_nodes(
  cloud_node_id SERIAL PRIMARY KEY NOT NULL,
  cloud_node_uid TEXT NOT NULL,
  cloud_node_discovery_url TEXT NOT NULL,
  cloud_node_did TEXT NOT NULL,
  provider_id INTEGER NOT NULL,
  FOREIGN KEY(provider_id) REFERENCES mee_network_providers(provider_id)
);
