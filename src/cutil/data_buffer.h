#ifndef _CUTIL_DATA_BUFFER_H_
#define _CUTIL_DATA_BUFFER_H_
namespace cutil
{
  class DataBuffer
  {
    public:
      DataBuffer() :
        buff_(NULL), capacity_(0), postion_(0)
    {
    }

      DataBuffer(char *data, int64_t capacity) : 
        buff_(data), capacity_(capacity), postion_(0)
    {
    }

      ~DataBuffer()
      {
      }

      inline int64_t set_data(char *data, const int64_t capacity);
      inline void DataBuffer::reset();
      inline int64_t get_postion () const;
      inline int64_t &get_postion();
      inline int64_t get_remain() const;
      inline int64_t get_capacity() const;
      inline const char * get_data() const;
      inline char * get_data();
    private:
      char *buff_;
      int64_t postion_;
      int64_t capacity_;
  };

  inline int64_t DataBuffer::set_data(char *data, const int64_t capacity)
  {
    buff_ = data;
    capacity_ = capacity;
    postion_ = 0;    
  }

  inline void DataBuffer::reset()
  {
    buff_ = NULL;
    capacity_ = 0;
    postion_ = 0;
  }

  inline int64_t DataBuffer::get_postion () const
  {
    return postion_;
  }

  inline int64_t & DataBuffer::get_postion()
  {
    return postion_;
  }

  inline int64_t DataBuffer::get_remain() const
  {
    return capacity_ - postion_;
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
