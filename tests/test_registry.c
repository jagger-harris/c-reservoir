#include "test_registry.h"
#include <stdlib.h>

void test_dynamic_array(void);
void test_file_management(void);
void test_hash_set(void);
void test_hash_table(void);
void test_rsv_strcpy(void);
void test_threads(void);

test_entry_t test_registry[] = {
  REGISTER_TEST("Dynamic Array Test", test_dynamic_array),
  REGISTER_TEST("File Management Test", test_file_management),
  REGISTER_TEST("Hash Set Test", test_hash_set),
  REGISTER_TEST("Hash Table Test", test_hash_table),
  REGISTER_TEST("Reservoir String Copy Test", test_rsv_strcpy),
  REGISTER_TEST("Threads Test", test_threads),
  {NULL, NULL}
};
