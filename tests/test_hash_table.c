#define RSVR_CONTAINERS_IMPLEMENTATION
#include "../include/rsvr_containers.h"
#include "../include/rsvr_safe.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_hash_table(void) {
  /* Declare variables */
  int test_int;
  char test_key[16];
  rsvr_hash_table_t hash_table;

  /* Test: Create hash table */
  hash_table = rsvr_hash_table_create(2, sizeof(int));
  assert(hash_table.size == 0);
  assert(hash_table.capacity == 2);

  /* Test: Insert key-value pairs */
  strcpy_safe(test_key, "key1", sizeof(test_key));
  test_int = 100;
  rsvr_hash_table_push(&hash_table, test_key, &test_int);
  assert(hash_table.size == 1);

  strcpy_safe(test_key, "key2", sizeof(test_key));
  test_int = 200;
  rsvr_hash_table_push(&hash_table, test_key, &test_int);
  assert(hash_table.size == 2);

  /* Test: Retrieve values from hash table */
  strcpy_safe(test_key, "key1", sizeof(test_key));
  assert((int*)rsvr_hash_table_get(&hash_table, test_key) != NULL);
  assert(*(int*)rsvr_hash_table_get(&hash_table, test_key) == 100);

  strcpy_safe(test_key, "key2", sizeof(test_key));
  assert((int*)rsvr_hash_table_get(&hash_table, test_key) != NULL);
  assert(*(int*)rsvr_hash_table_get(&hash_table, test_key) == 200);

  /* Test: Insert with key collision (same hash index) */
  strcpy_safe(test_key, "key3", sizeof(test_key));
  test_int = 300;
  rsvr_hash_table_push(&hash_table, test_key, &test_int);
  assert(hash_table.size == 3);

  /* Test: Remove key from hash table */
  strcpy_safe(test_key, "key2", sizeof(test_key));
  rsvr_hash_table_pop(&hash_table, test_key);
  assert(hash_table.size == 2);
  assert((int*)rsvr_hash_table_get(&hash_table, test_key) == NULL);

  /* Clean up */
  rsvr_hash_table_destroy(&hash_table);
  printf("All hash table tests passed!\n");
}

int main(void) {
  test_hash_table();
  exit(EXIT_SUCCESS);
}
