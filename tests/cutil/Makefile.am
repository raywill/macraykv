AM_LIBTOOLFLAGS=--preserve-dup-deps

AM_CPPFLAGS = -I${top_builddir}/tests/ \
							-I${top_builddir}/tests/cutil/ \
							-I${top_builddir}/src/ \
							-I${top_builddir}/src/cutil/ \
							-I${TBLIB_ROOT}/include/tbsys \
							-I${TBLIB_ROOT}/include/tbnet 

AM_CPPFLAGS += -Wno-deprecated

LDADD = ${top_builddir}/src/cutil/libcutil.a \
				${TBLIB_ROOT}/lib/libtbnet.a \
				${TBLIB_ROOT}/lib/libtbsys.a

AM_LDFLAGS=-lrt -lpthread  -ltcmalloc -lgtest

bin_PROGRAMS=data_buffer_test \
						 tc_allocator_test \
						 cu_test_framework_test

framework_source = cu_test_framework.h

data_buffer_test_SOURCES=data_buffer_test.cpp
tc_allocator_test_SOURCES=tc_allocator_test.cpp
cu_test_framework_test_SOURCES=cu_test_framework_test.cpp

