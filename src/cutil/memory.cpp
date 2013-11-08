#include <tbsys.h>
#include "memory.h"

namespace cutil
{
  TCAllocator &get_global_allocator()
  {
    static TCAllocator allocator;
    return allocator;
  }
}

int64_t cutil::TCAllocator::mod_[cutil::MemoryModIds::MAX_MEMORY_MOD_ID];

cutil::TCAllocator::TCAllocator()
{
  memset(mod_, 0, sizeof(mod_));
}

cutil::TCAllocator::~TCAllocator()
{
  int i = 0;
  for (i = 0; i < MemoryModIds::MAX_MEMORY_MOD_ID; i++)
  {
    if (0 != mod_[i])
    {
      TBSYS_LOG(WARN, "possible leak in mod %d, size=%ld", i, mod_[i]);
    }
  }
}

void *cutil::TCAllocator::tc_malloc(const int64_t nbytes, const int32_t mod_id)
{
  void *ptr = NULL;
  if (nbytes > 0)
  {
    // based on gproftool[tc_malloc]
    if (NULL != (ptr = malloc(nbytes + sizeof(TCAllocatorHeader))))
    {
      TCAllocatorHeader *header = NULL;
      CU_ASSERT(MemoryModIds::MIN_MEMORY_MOD_ID < mod_id && MemoryModIds::MAX_MEMORY_MOD_ID > mod_id);
      
      __sync_add_and_fetch(&mod_[mod_id], nbytes);

      header = reinterpret_cast<TCAllocatorHeader *>(ptr);
      header->mod_id_ = mod_id;
      header->size_ = nbytes;
      ptr = static_cast<void *>(static_cast<char *>(ptr) + sizeof(TCAllocatorHeader));
    }
  }
  return ptr;
}

void cutil::TCAllocator::tc_free(void *ptr)
{  
  TCAllocatorHeader *header = NULL;
  if (NULL != ptr)
  {
    header = reinterpret_cast<TCAllocatorHeader *>(static_cast<char *>(ptr) - sizeof(TCAllocatorHeader));

    CU_ASSERT(header->size_ > 0);
    CU_ASSERT(MemoryModIds::MIN_MEMORY_MOD_ID < header->mod_id_ && MemoryModIds::MAX_MEMORY_MOD_ID > header->mod_id_);
    
    __sync_sub_and_fetch(&mod_[header->mod_id_], header->size_);

    free(reinterpret_cast<void *>(header));
  }
}

void cutil::TCAllocator::tc_print_memory_usage(void)
{
  return;
}

void *cutil::tc_malloc(const int64_t nbytes, const int32_t mod_id)
{
  return cutil::get_global_allocator().tc_malloc(nbytes, mod_id);
}

void cutil::tc_free(void *ptr)
{
  cutil::get_global_allocator().tc_free(ptr);
}

void cutil::tc_print_memory_usage(void)
{
  cutil::get_global_allocator().tc_print_memory_usage();
}

