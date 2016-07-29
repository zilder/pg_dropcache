#include "postgres.h"
#include "storage/bufmgr.h"
#include "utils/syscache.h"
#include "utils/builtins.h"
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
	int			forkNum;
	HeapTuple	tp;
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

	forkNum = PG_ARGISNULL(1) ? 0 : forkname_to_number(text_to_cstring(PG_GETARG_TEXT_P(1)));
	for (; forkNum <= MAX_FORKNUM; ++forkNum)
		DropRelFileNodeBuffers(rnode, forkNum, 0);

	PG_RETURN_VOID();
}
