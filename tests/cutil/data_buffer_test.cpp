#include <tbsys.h>
#include <gtest/gtest.h>
#include "cutil/data_buffer.h"
#include "cutil/memory.h"

using namespace cutil;

class DataBufferTest : public ::testing::Test 
{
  public:
  DataBufferTest()
  {
  }

  ~DataBufferTest()
  {
  }
  
  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
    TBSYS_LOG(INFO, "set up");
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    TBSYS_LOG(INFO, "tear down");
  }

};


TEST_F(DataBufferTest, basic_method_test) 
{
  TBSYS_LOG(INFO, "run init_reset_test");
  DataBuffer buff;
  const int size = 100;
  const int64_t used = 10;
  char *ptr = static_cast<char *>(tc_malloc(size, MemoryModIds::DEFAULT_MOD));
  ASSERT_EQ(CU_SUCCESS, buff.set_data(ptr, size));

  ASSERT_EQ(0, buff.get_position());
  ASSERT_EQ(size, buff.get_capacity());
  ASSERT_EQ(size, buff.get_remain());
  ASSERT_EQ(size, buff.get_remain());
  buff.get_position() = used;
  ASSERT_EQ(used, buff.get_position());
  ASSERT_EQ(size, buff.get_capacity());
  ASSERT_EQ(size - used, buff.get_remain());
  buff.reset();
  ASSERT_EQ(0, buff.get_position());
  ASSERT_EQ(size, buff.get_capacity());
  ASSERT_EQ(size, buff.get_remain()); 
}


TEST_F(DataBufferTest, init_exception_test) {
  DataBuffer buff;
  const int size_ok = 100;
  char *ptr_ok = static_cast<char *>(tc_malloc(size_ok, MemoryModIds::DEFAULT_MOD));
  const int size_neg_bad = -1;
  const int size_zero_bad = 0;
  char *ptr_null = NULL;
  
  ASSERT_EQ(CU_SUCCESS, buff.set_data(ptr_ok, size_ok));

  ASSERT_NE(CU_SUCCESS, buff.set_data(ptr_null, size_ok));
  ASSERT_NE(CU_SUCCESS, buff.set_data(ptr_null, size_neg_bad));
  ASSERT_NE(CU_SUCCESS, buff.set_data(ptr_null, size_zero_bad));

  ASSERT_NE(CU_SUCCESS, buff.set_data(ptr_ok, size_ok));
  ASSERT_NE(CU_SUCCESS, buff.set_data(ptr_ok, size_neg_bad));
  ASSERT_NE(CU_SUCCESS, buff.set_data(ptr_ok, size_zero_bad));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

