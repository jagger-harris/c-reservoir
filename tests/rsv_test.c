#include "../include/rsv_log.h"
#include "test_registry.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  test_entry_t* entry;
  int failed_tests = 0;

  for (entry = test_registry; entry->name != NULL; entry++) {
    if (entry->test_func()) {
      printf("%s%s failed!%s\n", RSV_ANSI_COLOR_RED, entry->name,
             RSV_ANSI_COLOR_RESET);
      failed_tests++;
    } else {
      printf("%s%s passed!%s\n", RSV_ANSI_COLOR_GREEN, entry->name,
             RSV_ANSI_COLOR_RESET);
    }
  }

  if (failed_tests) {
    printf("%s%d tests failed!%s\n", RSV_ANSI_COLOR_RED, failed_tests,
           RSV_ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  printf("%sAll tests passed!%s\n", RSV_ANSI_COLOR_GREEN, RSV_ANSI_COLOR_RESET);
  exit(EXIT_SUCCESS);
}
