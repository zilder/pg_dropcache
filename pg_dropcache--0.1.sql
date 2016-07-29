\echo Use "CREATE EXTENSION pg_dropcache" to load this file. \quit

CREATE OR REPLACE FUNCTION pg_dropcache()
RETURNS VOID
AS 'pg_dropcache', 'pg_dropcache'
LANGUAGE C;

CREATE OR REPLACE FUNCTION pg_drop_rel_cache(relation regclass, fork text default null)
RETURNS VOID
AS 'pg_dropcache', 'pg_drop_rel_cache'
LANGUAGE C;
