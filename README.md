# pg_dropcache

`pg_dropcache` is a PostgreSQL extension that invalidates `shared_buffers` cache

## Installation

To install `pg_dropcache` clone this repository and run:

```
make install USE_PGXS=1
```

Then in psql (or any other client) execute:

```
create extension pg_dropcache;
```

## Usage

To clear buffer cache just run query:

```
select pg_dropcache();
```

Have fun!