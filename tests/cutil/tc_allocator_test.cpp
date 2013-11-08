#include <tbsys.h>
#include <gtest/gtest.h>
#include "cutil/memory.h"
#include "cutil/cu_test_framework.h"

using namespace cutil;

class TCAllocatorTest: public ::testing::Test 
{
  public:
  TCAllocatorTest()
  {
  }

  ~TCAllocatorTest()
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


TEST_F(TCAllocatorTest, alloc_free) 
{
  void *ptr = NULL;
  void *ptr2 = NULL;
  ptr = tc_malloc(100, 1);
  ptr2 = tc_malloc(100000, 2);
  ASSERT_EQ(100, cutil::TCAllocator::mod_[1]);
  tc_free(ptr);
  ASSERT_EQ(0, cutil::TCAllocator::mod_[1]);
  TBSYS_LOG(INFO, "gogogog");
  tc_free(ptr2);
}

TEST_F(TCAllocatorTest, alloc_free_parallel) 
{
  BEGIN_THREAD_CODE(mygod, 30)
  {
    void *ptr = NULL;
    for (int i = 0; i < 10000; i++)
    {
      ptr = tc_malloc(100 * i, 1);
      tc_free(ptr);
    }
    TBSYS_LOG(INFO, "end current thread");
  }END_THREAD_CODE(mygod);
  ASSERT_EQ(0, cutil::TCAllocator::mod_[1]);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

