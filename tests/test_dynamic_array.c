#include "../include/rsv_containers.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_dynamic_array(void) {
  int test_int;
  rsv_dynamic_array_t array;

  /* Test: Create array */
  array = rsv_dynamic_array_create(2, sizeof(int));
  assert(array.amount == 0);
  assert(array.capacity == 2);

  /* Test: Push array */
  test_int = 100;
  rsv_dynamic_array_push(&array, &test_int);
  assert(array.amount == 1);
  assert(((int*)array.data)[0] == 100);

  /* Test: Push array */
  test_int = 200;
  rsv_dynamic_array_push(&array, &test_int);
  assert(array.amount == 2);
  assert(((int*)array.data)[1] == 200);

  /* Test: Array should resize */
  test_int = 300;
  rsv_dynamic_array_push(&array, &test_int);
  assert(array.amount == 3);
  assert(array.capacity ==
         (unsigned int)(ceil(2 * RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT)));

  /* Test: Get value from array */
  assert(*(int*)rsv_dynamic_array_get(&array, 2) == 300);

  /* Test: Pop */
  rsv_dynamic_array_pop(&array);
  assert(array.amount == 2);

  /* Test: Ensure last element was removed */
  assert(*(int*)rsv_dynamic_array_get(&array, 0) == 100);
  assert(*(int*)rsv_dynamic_array_get(&array, 1) == 200);
  assert(rsv_dynamic_array_get(&array, 2) == NULL);

  rsv_dynamic_array_destroy(&array);
  printf("All dynamic array tests passed!\n");
}

int main(void) {
  test_dynamic_array();
  exit(EXIT_SUCCESS);
}
