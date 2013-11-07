#ifndef _CUTIL_MEMRORY_MOD_DEFINE_H_
#define _CUTIL_MEMRORY_MOD_DEFINE_H_
namespace cutil
{
  
  class MemoryModIds
  {
    public:
      enum
      {
        MIN_MEMORY_MOD_ID = 0,
        DEFAULT_MOD,
        THREAD_DATA_BUFFER,
        // more mod ids defined here

        MAX_MEMORY_MOD_ID
      };
  };

}
#endif
