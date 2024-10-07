#include "../include/rsv_math.h"
#include "test.h"
#include <stdio.h>

/* Tests for rsv_floor */
int test_math(void) {
  /* Test: Floor cases */
  TEST(rsv_floor(4.5) == 4);
  TEST(rsv_floor(4.0) == 4);
  TEST(rsv_floor(-4.5) == -5);
  TEST(rsv_floor(-4.0) == -4);
  TEST(rsv_floor(0.0) == 0);
  TEST(rsv_floor(-0.5) == -1);

  /* Test: Ceil cases */
  TEST(rsv_ceil(4.5) == 5);
  TEST(rsv_ceil(4.0) == 4);
  TEST(rsv_ceil(-4.5) == -4);
  TEST(rsv_ceil(-4.0) == -4);
  TEST(rsv_ceil(0.0) == 0);
  TEST(rsv_ceil(-0.5) == 0);

  return 0;
}
