#ifndef TEST_H
#define TEST_H

#include "../include/rsv_log.h"

#define TEST(condition)                                                        \
  do {                                                                         \
    if (!(condition)) {                                                        \
      printf("%sTest failed: %s (file: %s, line: %d)%s\n", RSV_ANSI_COLOR_RED, \
             #condition, __FILE__, __LINE__, RSV_ANSI_COLOR_RESET);            \
      return 1;                                                                \
    }                                                                          \
  } while (0)

#endif /* TEST_H */
