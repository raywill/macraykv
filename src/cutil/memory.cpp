#include "memory.h"

void *cutil::tc_malloc(const int64_t nbytes, const int32_t mod_id)
{
  void *ptr = NULL;
  UNUSED(mod_id);
  if (nbytes > 0)
  {
    // based on gproftool[tc_malloc]
    ptr = malloc(nbytes);
  }
  return ptr;
}

void cutil::tc_free(void *ptr)
{
//  UNUSED(mod_id);
  if (ptr)
  {
    free(ptr);
  }
}

void cutil::tc_print_memory_usage(void)
{
  return;
}

