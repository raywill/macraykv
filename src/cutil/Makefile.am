AM_CPPFLAGS = -I${TBLIB_ROOT}/include/tbsys \
							-I${TBLIB_ROOT}/include/tbnet

AM_CPPFLAGS += -Wno-deprecated	-fPIC 

LDADD = ${TBLIB_ROOT}/lib/libtbsys.a

AM_LDFLAGS=-lrt -lpthread  -ltcmalloc

noinst_LIBRARIES=libcutil.a
libcutil_a_SOURCES=define.h 																										\
									 error_code.h 																								\
									 data_buffer.h 																								\
									 memory_mod_define.h 																					\
									 memory.h                          	memory.cpp 								\
									 thread_data_buffer.h         			thread_data_buffer.cpp



