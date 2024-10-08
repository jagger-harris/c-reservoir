#include "rsv_test.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int failed_tests = rsv_test_all();

  if (failed_tests) {
    printf("%s%d test(s) failed!%s\n", "\x1b[31m", failed_tests, "\x1b[0m");
    exit(EXIT_FAILURE);
  }

  printf("%sAll tests passed!%s\n", "\x1b[32m", "\x1b[0m");
  exit(EXIT_SUCCESS);
}
