#include <tbsys.h>
#include "define.h"
#include "thread_data_buffer.h"

using namespace cutil;

namespace
{
    const pthread_key_t INVALID_THREAD_KEY = UINT32_MAX;
}

ThreadDataBuffer::ThreadDataBuffer(const int64_t size) :
  size_(size),
  key_(INVALID_THREAD_KEY)
{
  CU_ASSERT(size_ > 0);
  create_thread_key();
}

ThreadDataBuffer::~ThreadDataBuffer()
{
  delete_thread_key();
}

int ThreadDataBuffer::create_thread_key()
{
  int ret = pthread_key_create(&key_, destroy_thread_key);
  if (0 != ret)
  {
    TBSYS_LOG(ERROR, "cannot create thread key. ret=%d", ret);
  }
  return (0 == ret) ? CU_SUCCESS : CU_ERROR;
}

int ThreadDataBuffer::delete_thread_key()
{
  int ret = CU_SUCCESS;
  if (INVALID_THREAD_KEY != key_)
  {
    if (0 != (ret = pthread_key_delete(&key_)))
    {
      TBSYS_LOG(ERROR, "cannot delete thread key. key_=%u ret=%d", key_, ret);
    }
  }
  return (0 == ret) ? CU_SUCCESS : CU_ERROR;
}

void ThreadDataBuffer::destroy_thread_key(void *ptr)
{
  if (NULL != ptr)
  {
    tc_free(ptr);
    ptr = NULL;
  }
}


DataBuffer * ThreadDataBuffer::get_buffer()
{
  int ret = CU_SUCCESS;
  DataBuffer *buffer = NULL;
  void *ptr = NULL;
  if (INVALID_THREAD_KEY != key_ && size_ > 0)
  {
    ptr = pthread_getspecific(key_);
    if (NULL == ptr)
    {
      ptr = tc_malloc(size_ + sizeof(DataBuffer), MemoryModIds::THREAD_DATA_BUFFER); 
      if (NULL == ptr)
      {
        TBSYS_LOG(ERROR, "out of memory. size_=%ld", size_);
      }
      else
      {
        ret = pthread_setspecific(key_, ptr);
        if (0 != ret)
        {
          TBSYS_LOG(ERROR, "pthread_setspecific fail. ret=%d", ret);
          tc_free(ptr);
          ptr = NULL;
        }
        else
        {
          buffer = reinterpret_cast<DataBuffer *>(ptr);
          buffer = new (ptr) DataBuffer(static_cast<char *>(ptr) + sizeof(DataBuffer), size_);
          TBSYS_LOG(DEBUG, "set thread specific buffer ok");
        }
      }
    }
    else
    {
      buffer = reinterpret_cast<DataBuffer *>(ptr);
    }
  }
  else
  {
    TBSYS_LOG(ERROR, "threadbuffer may not be initilized. key_=%u size_=%ld", key_, size_);
  }
  return buffer;
}

