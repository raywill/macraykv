#ifndef _MACRAYKV_CUTIL_DEFINE_H_
#define _MACRAYKV_CUTIL_DEFINE_H_
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif


#ifndef CU_ASSERT
#define CU_ASSERT(x) (assert(x))
#endif
#endif
