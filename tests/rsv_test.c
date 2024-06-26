#include "test_registry.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  test_entry_t* entry;

  for (entry = test_registry; entry->name != NULL; entry++) {
    printf("Running %s...\n", entry->name);
    entry->test_func();
    printf("%s passed!\n", entry->name);
  }

  printf("All tests passed!\n");

  exit(EXIT_SUCCESS);
}
