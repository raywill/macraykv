#include "cu_test_framework.h"

int main()
{
  BEGIN_THREAD_CODE(MyRunner, 10)
  {
    static int i = 0;
  i++;
  }
  END_THREAD_CODE(MyRunner);
}
