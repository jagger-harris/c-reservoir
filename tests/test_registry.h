#ifndef TEST_REGISTRY_H
#define TEST_REGISTRY_H

typedef int (*test_func_t)(void);

typedef struct test_entry_t {
  const char *name;
  test_func_t test_func;
} test_entry_t;

#define REGISTER_TEST(name, test_func) {name, test_func}

extern test_entry_t test_registry[];

#endif /* TEST_REGISTRY_H */
