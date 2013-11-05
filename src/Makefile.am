AM_CPPFLAGS = -I${TBLIB_ROOT}/include/tbsys \
							-I${TBLIB_ROOT}/include/tbnet \
							-fPIC \
							-Wno-deprecated

LDADD = ${TBLIB_ROOT}/lib/libtbnet.a \
				${TBLIB_ROOT}/lib/libtbsys.a

AM_LDFLAGS=-lrt -lpthread  -ltcmalloc

bin_PROGRAMS=macraykv

macraykv_SOURCES=mr_base_server.cpp mr_base_server.h main.cpp

SUBDIRS=cutil
