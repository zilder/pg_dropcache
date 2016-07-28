\echo Use "CREATE EXTENSION pg_dropcache" to load this file. \quit

CREATE FUNCTION pg_dropcache()
RETURNS VOID
AS 'pg_dropcache'
LANGUAGE C;
