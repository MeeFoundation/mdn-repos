
CREATE TABLE provider_mdn_license_application (
    id SERIAL PRIMARY KEY NOT NULL,
    meeid TEXT NOT NULL UNIQUE,
    provider_meeid TEXT NOT NULL,
    contact_email TEXT NOT NULL,
    company_name TEXT NOT NULL,
    company_uri TEXT NOT NULL,
    cloud_node_discovery_url TEXT NOT NULL,
    decentralized_id TEXT NOT NULL,
    status TEXT NOT NULL,
    created_at TIMESTAMP NOT NULL,
    updated_at TIMESTAMP NOT NULL
);

CREATE TABLE pda_hil_application (
    id SERIAL PRIMARY KEY NOT NULL,
    meeid TEXT NOT NULL UNIQUE,
    pda_meeid TEXT NOT NULL,
    status TEXT NOT NULL,
    created_at TIMESTAMP NOT NULL,
    updated_at TIMESTAMP NOT NULL
);

CREATE TABLE advertiser_hil_application (
    id SERIAL PRIMARY KEY NOT NULL,
    meeid TEXT NOT NULL UNIQUE,
    advertiser_meeid TEXT NOT NULL,
    status TEXT NOT NULL,
    created_at TIMESTAMP NOT NULL,
    updated_at TIMESTAMP NOT NULL
);