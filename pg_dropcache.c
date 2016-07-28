#include "postgres.h"
#include "storage/bufmgr.h"
#include "miscadmin.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(pg_dropcache);

Datum
pg_dropcache(PG_FUNCTION_ARGS)
{
	DropDatabaseBuffers(MyDatabaseId);
	PG_RETURN_VOID();
}
