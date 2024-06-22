#include "../include/rsv_containers.h"
#include "../include/rsv_safe.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_hash_table(void) {
  int test_int;
  char test_key[16];
  rsv_hash_table_t hash_table;

  /* Test: Create hash table */
  hash_table = rsv_hash_table_create(2, sizeof(int));
  assert(hash_table.size == 0);
  assert(hash_table.capacity == 2);

  /* Test: Insert key-value pairs */
  rsv_strcpy(test_key, "key1", sizeof(test_key));
  test_int = 100;
  rsv_hash_table_push(&hash_table, test_key, &test_int);
  assert(hash_table.size == 1);

  rsv_strcpy(test_key, "key2", sizeof(test_key));
  test_int = 200;
  rsv_hash_table_push(&hash_table, test_key, &test_int);
  assert(hash_table.size == 2);

  /* Test: Retrieve values from hash table */
  rsv_strcpy(test_key, "key1", sizeof(test_key));
  assert((int*)rsv_hash_table_get(&hash_table, test_key) != NULL);
  assert(*(int*)rsv_hash_table_get(&hash_table, test_key) == 100);

  rsv_strcpy(test_key, "key2", sizeof(test_key));
  assert((int*)rsv_hash_table_get(&hash_table, test_key) != NULL);
  assert(*(int*)rsv_hash_table_get(&hash_table, test_key) == 200);

  /* Test: Insert with key collision (same hash index) */
  rsv_strcpy(test_key, "key3", sizeof(test_key));
  test_int = 300;
  rsv_hash_table_push(&hash_table, test_key, &test_int);
  assert(hash_table.size == 3);

  /* Test: Remove key from hash table */
  rsv_strcpy(test_key, "key2", sizeof(test_key));
  rsv_hash_table_pop(&hash_table, test_key);
  assert(hash_table.size == 2);
  assert((int*)rsv_hash_table_get(&hash_table, test_key) == NULL);

  /* Clean up */
  rsv_hash_table_destroy(&hash_table);
  printf("All hash table tests passed!\n");
}

int main(void) {
  test_hash_table();
  exit(EXIT_SUCCESS);
}
