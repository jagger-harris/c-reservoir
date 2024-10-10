#ifndef TEST_DYNAMIC_ARRAY_H
#define TEST_DYNAMIC_ARRAY_H

#include "../include/containers/rsv_dynamic_array.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

static inline int test_dynamic_array(void) {
  int test_int;
  rsv_dynamic_array_t array;

  /* Test: Create array */
  array = rsv_dynamic_array_create(2, sizeof(int));
  TEST(array.amount == 0);
  TEST(array.capacity == 2);

  /* Test: Push array */
  test_int = 100;
  rsv_dynamic_array_push(&array, &test_int);
  TEST(array.amount == 1);
  TEST(((int*)array.data)[0] == 100);

  /* Test: Push array */
  test_int = 200;
  rsv_dynamic_array_push(&array, &test_int);
  TEST(array.amount == 2);
  TEST(((int*)array.data)[1] == 200);

  /* Test: Array should resize */
  test_int = 300;
  rsv_dynamic_array_push(&array, &test_int);
  TEST(array.amount == 3);
  TEST(array.capacity ==
       (unsigned int)(2 * RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT + 1));

  /* Test: Get value from array */
  TEST(*(int*)rsv_dynamic_array_get(&array, 2) == 300);

  /* Test: Pop */
  rsv_dynamic_array_pop(&array);
  TEST(array.amount == 2);

  /* Test: Ensure last element was removed */
  TEST(*(int*)rsv_dynamic_array_get(&array, 0) == 100);
  TEST(*(int*)rsv_dynamic_array_get(&array, 1) == 200);
  TEST(rsv_dynamic_array_get(&array, 2) == NULL);

  rsv_dynamic_array_destroy(&array);
  return 0;
}

#endif /* TEST_DYNAMIC_ARRAY_H */
