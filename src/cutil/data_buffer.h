#ifndef _CUTIL_DATA_BUFFER_H_
#define _CUTIL_DATA_BUFFER_H_
#include "error_code.h"

namespace cutil
{
  class DataBuffer
  {
    public:
      DataBuffer() :
        buff_(NULL), capacity_(0), position_(0)
    {
    }

      DataBuffer(char *data, int64_t capacity) : 
        buff_(data), capacity_(capacity), position_(0)
    {
    }

      ~DataBuffer()
      {
      }

      inline int64_t set_data(char *data, const int64_t capacity);
      inline void reset();
      inline int64_t get_position () const;
      inline int64_t &get_position();
      inline int64_t get_remain() const;
      inline int64_t get_capacity() const;
      inline const char * get_data() const;
      inline char * get_data();
    private:
      char *buff_;
      int64_t position_;
      int64_t capacity_;
  };

  inline int64_t DataBuffer::set_data(char *data, const int64_t capacity)
  {
    int ret = CU_SUCCESS;
    if (NULL != buff_)
    {
      ret = CU_ALREADY_INIT;
    }
    else if (NULL != data && capacity > 0)
    {
      buff_ = data;
      capacity_ = capacity;
      position_ = 0;    
    }
    else
    {
      TBSYS_LOG(WARN, "invalid argument. data=%p capacity=%ld", data, capacity);
      ret = CU_INVALID_ARGUMENT;
    }
    return ret;
  }

  inline void DataBuffer::reset()
  {
    position_ = 0;
  }

  inline int64_t DataBuffer::get_position () const
  {
    return position_;
  }

  inline int64_t & DataBuffer::get_position()
  {
    return position_;
  }

  inline int64_t DataBuffer::get_remain() const
  {
    return capacity_ - position_;
  }

  inline int64_t DataBuffer::get_capacity() const
  {
    return capacity_;
  }

  inline const char * DataBuffer::get_data() const
  {
    return buff_;
  }

  inline char * DataBuffer::get_data()
  {
    return buff_;
  }
}

#endif
