AM_CPPFLAGS = -I${TBLIB_ROOT}/include/tbsys \
							-I${TBLIB_ROOT}/include/tbnet \
							-fPIC 

LDADD = ${TBLIB_ROOT}/lib/libtbsys.a

AM_LDFLAGS=-lrt -lpthread  -ltcmalloc

noinst_LIBRARIES=libcutil.a
libcutil_a_SOURCES=data_buffer.h \
									 memory.h         memory.cpp


