#include "postgres.h"
#include "storage/bufmgr.h"
#include "utils/syscache.h"
#include "access/htup_details.h"
#include "miscadmin.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(pg_dropcache);
PG_FUNCTION_INFO_V1(pg_drop_rel_cache);

Datum
pg_dropcache(PG_FUNCTION_ARGS)
{
	DropDatabaseBuffers(MyDatabaseId);
	PG_RETURN_VOID();
}

Datum
pg_drop_rel_cache(PG_FUNCTION_ARGS)
{
	Oid			relid = PG_GETARG_OID(0);
	HeapTuple	tp;
	int			forknum;
	RelFileNodeBackend	rnode;

	tp = SearchSysCache1(RELOID, ObjectIdGetDatum(relid));
	if (HeapTupleIsValid(tp))
	{
		Form_pg_class reltup = (Form_pg_class) GETSTRUCT(tp);
	
		rnode.node.relNode = reltup->relfilenode;
		rnode.node.spcNode = (reltup->reltablespace == InvalidOid) ?
			MyDatabaseTableSpace :
			reltup->reltablespace;
		rnode.node.dbNode = MyDatabaseId;
		rnode.backend = InvalidBackendId;

		ReleaseSysCache(tp);
	}
	else
	{
		elog(ERROR, "Unable to get cache for relation %u", relid);
		PG_RETURN_VOID();
	}

	for (forknum = 0; forknum < MAX_FORKNUM; ++forknum)
	{
		DropRelFileNodeBuffers(rnode, forknum, 0);
	}
	PG_RETURN_VOID();
}
