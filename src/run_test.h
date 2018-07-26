#include <stdio.h>

#define run_test(fn_name)\
  printf("%s\n", #fn_name);\
  fn_name();

#define run_test_with_args(fn_name)\
  printf("%s\n", #fn_name);\
  fn_name;
