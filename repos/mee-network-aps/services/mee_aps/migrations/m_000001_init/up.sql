CREATE TABLE IF NOT EXISTS sda_profiles(
  record_id SERIAL PRIMARY KEY,
  record_uid TEXT UNIQUE NOT NULL,
  user_uid TEXT UNIQUE NOT NULL,
  sda_profile JSON NOT NULL
);
