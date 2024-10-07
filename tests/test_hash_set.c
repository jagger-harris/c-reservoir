#include "../include/rsv_containers.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_hash_set(void) {
  int test_int;
  int* test_key;
  rsv_hash_set_t hash_set;

  /* Test: Create hash set */
  hash_set = rsv_hash_set_create(2, sizeof(int), NULL, NULL);
  TEST(hash_set.amount == 0);
  TEST(hash_set.capacity == 2);

  /* Test: Insert keys */
  test_int = 100;
  test_key = &test_int;
  rsv_hash_set_push(&hash_set, test_key);
  TEST(hash_set.amount == 1);

  test_int = 200;
  test_key = &test_int;
  rsv_hash_set_push(&hash_set, test_key);
  TEST(hash_set.amount == 2);

  /* Test: Check keys presence */
  test_int = 100;
  test_key = &test_int;
  TEST(rsv_hash_set_contains(&hash_set, test_key) == 1);

  test_int = 200;
  test_key = &test_int;
  TEST(rsv_hash_set_contains(&hash_set, test_key) == 1);

  test_int = 300;
  test_key = &test_int;
  TEST(rsv_hash_set_contains(&hash_set, test_key) == 0);

  /* Test: Insert with key collision (same hash index) */
  test_int = 300;
  test_key = &test_int;
  rsv_hash_set_push(&hash_set, test_key);
  TEST(hash_set.amount == 3);
  TEST(rsv_hash_set_contains(&hash_set, test_key) == 1);

  /* Test: Remove keys from hash set */
  test_int = 200;
  test_key = &test_int;
  rsv_hash_set_pop(&hash_set, test_key);
  TEST(hash_set.amount == 2);
  TEST(rsv_hash_set_contains(&hash_set, test_key) == 0);

  test_int = 100;
  test_key = &test_int;
  rsv_hash_set_pop(&hash_set, test_key);
  TEST(hash_set.amount == 1);
  TEST(rsv_hash_set_contains(&hash_set, test_key) == 0);

  rsv_hash_set_destroy(&hash_set);
  return 0;
}
