# contrib/pg_dropcache/Makefile

MODULE_big = pg_dropcache
OBJS = pg_dropcache.o $(WIN32RES)

EXTENSION = pg_dropcache
DATA = pg_dropcache--0.1.sql
PGFILEDESC = "pg_dropcache - clears buffer cache"

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/pg_dropcache
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
