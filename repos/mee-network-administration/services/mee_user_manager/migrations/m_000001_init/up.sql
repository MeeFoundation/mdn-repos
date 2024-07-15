CREATE TABLE IF NOT EXISTS mee_network_users(
  user_id SERIAL PRIMARY KEY,
  user_meeid TEXT UNIQUE NOT NULL,
  user_email TEXT UNIQUE NOT NULL,
  user_phone TEXT UNIQUE,
  user_role TEXT NOT NULL,
  is_active BOOLEAN NOT NULL,
  salt TEXT NOT NULL,
  password TEXT NOT NULL
);
