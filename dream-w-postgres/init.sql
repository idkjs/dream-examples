-- Used only in development
-- In production, Heroku creates the DB and its users
SET client_encoding = 'UTF8';

-- reset the user along with the DB;

DROP USER IF EXISTS dream;
DROP ROLE IF EXISTS dream;
CREATE USER dream WITH PASSWORD 'password';
CREATE DATABASE dream;
GRANT ALL PRIVILEGES ON DATABASE dream TO dream;
ALTER ROLE dream SUPERUSER;
