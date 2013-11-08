#ifndef _TESTING_CU_TEST_FRAMEWORK_H_
#define _TESTING_CU_TEST_FRAMEWORK_H_

#include <tbsys.h>

#define BEGIN_THREAD_CODE(class_name, thread_count) \
  class _##class_name : public tbsys::CDefaultRunnable \
  { \
    public: \
    _##class_name() { _threadCount = thread_count; } \
  void run(tbsys::CThread *thread, void *arg)

#define END_THREAD_CODE(class_name) \
  };\
  _##class_name my_##class_name; \
  my_##class_name.start();  my_##class_name.wait();

#endif
