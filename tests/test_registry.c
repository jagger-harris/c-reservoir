#include "test_registry.h"
#include <stdlib.h>

int test_dynamic_array(void);
int test_file_management(void);
int test_hash_set(void);
int test_hash_table(void);
int test_math(void);
int test_rsv_strcpy(void);

#if defined(__unix__)
int test_threads(void);
#endif

test_entry_t test_registry[] = {
    REGISTER_TEST("Dynamic Array Test", test_dynamic_array),
    REGISTER_TEST("File Management Test", test_file_management),
    REGISTER_TEST("Hash Set Test", test_hash_set),
    REGISTER_TEST("Hash Table Test", test_hash_table),
    REGISTER_TEST("Math Test", test_math),
    REGISTER_TEST("Reservoir String Copy Test", test_rsv_strcpy),
#if defined(__unix__)
    REGISTER_TEST("Threads Test", test_threads),
#endif
    {NULL, NULL}};
