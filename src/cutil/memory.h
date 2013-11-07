#ifndef _CUTIL_MEMORY_H_
#define _CUTIL_MEMORY_H_
#include "define.h"
#include "memory_mod_define.h"

namespace cutil
{
  void *tc_malloc(const int64_t nbytes, const int32_t mod_id);
  void tc_free(void *ptr);
  void tc_print_memory_usage(void);
}

#endif

