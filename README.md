macraykv
========

MacrayKV is a Key-Value storage system

##INSTALL
you need following third-party library
* [tbsys&tbnet] https://github.com/raywill/tb-common-utils.git
* [gperftools] http://code.google.com/p/gperftools/downloads/list
* [gtest] Google Test is used as unit-test framework
* [libunwind] you may need this in order to build gperftools in some system. Ignore this if gperftools compiles OK.

in order to compile tbsys&tbnet, set $TBLIB_ROOT first.
after all dependency resolved, run following command in $root_dir:
* sh build.sh init;
* sh build.sh
* make -j

##Author:
* raywill
* macduan
