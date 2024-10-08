#ifndef TEST_HASH_TABLE_H
#define TEST_HASH_TABLE_H

#include "../include/rsv_containers.h"
#include "../include/rsv_safe.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

int test_hash_table(void) {
  int test_int;
  char test_key[16];
  rsv_hash_table_t hash_table;

  /* Test: Create hash table */
  hash_table =
      rsv_hash_table_create(2, sizeof(test_key), sizeof(int), NULL, NULL);
  TEST(hash_table.amount == 0);
  TEST(hash_table.capacity == 2);

  /* Test: Insert key-value pairs */
  rsv_strcpy(test_key, "key1", sizeof(test_key));
  test_int = 100;
  rsv_hash_table_push(&hash_table, test_key, &test_int);
  TEST(hash_table.amount == 1);

  rsv_strcpy(test_key, "key2", sizeof(test_key));
  test_int = 200;
  rsv_hash_table_push(&hash_table, test_key, &test_int);
  TEST(hash_table.amount == 2);

  /* Test: Retrieve values from hash table */
  rsv_strcpy(test_key, "key1", sizeof(test_key));
  TEST((int*)rsv_hash_table_get(&hash_table, test_key) != NULL);
  TEST(*(int*)rsv_hash_table_get(&hash_table, test_key) == 100);

  rsv_strcpy(test_key, "key2", sizeof(test_key));
  TEST((int*)rsv_hash_table_get(&hash_table, test_key) != NULL);
  TEST(*(int*)rsv_hash_table_get(&hash_table, test_key) == 200);

  /* Test: Insert with key collision (same hash index) */
  rsv_strcpy(test_key, "key3", sizeof(test_key));
  test_int = 300;
  rsv_hash_table_push(&hash_table, test_key, &test_int);
  TEST(hash_table.amount == 3);

  /* Test: Remove key from hash table */
  rsv_strcpy(test_key, "key2", sizeof(test_key));
  rsv_hash_table_pop(&hash_table, test_key);
  TEST(hash_table.amount == 2);
  TEST((int*)rsv_hash_table_get(&hash_table, test_key) == NULL);

  /* Clean up */
  rsv_hash_table_destroy(&hash_table);
  return 0;
}

#endif /* TEST_HASH_TABLE_H */
