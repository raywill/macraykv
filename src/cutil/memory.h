#ifndef _CUTIL_MEMORY_H_
#define _CUTIL_MEMORY_H_
#include "define.h"
#include "memory_mod_define.h"

class TCAllocatorTest_alloc_free_Test;
class TCAllocatorTest_alloc_free_parallel_Test;

namespace cutil
{
  struct TCAllocatorHeader
  {
    int32_t mod_id_;
    int64_t size_;
  };

  // Wapper class
  class TCAllocator
  {
    public:
      friend class ::TCAllocatorTest_alloc_free_Test;
      friend class ::TCAllocatorTest_alloc_free_parallel_Test;
    public:
      TCAllocator();
      ~TCAllocator();
      void *tc_malloc(const int64_t nbytes, const int32_t mod_id);
      void tc_free(void *ptr);
      void tc_print_memory_usage(void);
    private:
      static int64_t mod_[MemoryModIds::MAX_MEMORY_MOD_ID];
  };

  void *tc_malloc(const int64_t nbytes, const int32_t mod_id);
  void tc_free(void *ptr);
  void tc_print_memory_usage(void);
}

#endif

