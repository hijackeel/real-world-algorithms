#include <stdio.h>

#define run_test(fn_name)\
  printf("%s\n", #fn_name);\
  fn_name();
