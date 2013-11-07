#ifndef _CUTIL_THREAD_DATA_BUFFER_H_
#define _CUTIL_THREAD_DATA_BUFFER_H_

#include <pthread.h>
#include "memory.h"
#include "data_buffer.h"

namespace cutil
{
  /**
   * Allcate data buffer for each thread once
   */
  class ThreadDataBuffer
  {
    public:
      const static int64_t MAX_THREAD_BUFFER_SIZE = 2 * 1024 * 1024;
    public:
      explicit ThreadDataBuffer(int64_t size);
      ~ThreadDataBuffer();
      // once allocated, never need to free
      DataBuffer *get_buffer();
    private:
      int create_thread_key();
      int delete_thread_key();
      // static for callback
      static void destroy_thread_key(void *ptr);
    private:
      int64_t size_;
      pthread_key_t key_;
  };
}

#endif
