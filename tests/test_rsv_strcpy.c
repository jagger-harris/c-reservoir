#include "../include/rsv_safe.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_rsv_strcpy(void) {
  char dest[10];

  /* Test: Normal copy */
  rsv_strcpy(dest, "hello", sizeof(dest));
  TEST(strcmp(dest, "hello") == 0);

  /* Test: Copy with truncation */
  rsv_strcpy(dest, "verylongstring", sizeof(dest));
  TEST(strcmp(dest, "verylongs") ==
         0); /* dest_size - 1 characters + null terminator */

  /* Test: Empty source string */
  rsv_strcpy(dest, "", sizeof(dest));
  TEST(strcmp(dest, "") == 0);

  /* Test: Source string fits exactly */
  rsv_strcpy(dest, "123456789", sizeof(dest));
  TEST(strcmp(dest, "123456789") ==
         0); /* Exactly 9 characters + null terminator */

  /* Test: dest_size is 1 (only null terminator) */
  rsv_strcpy(dest, "test", 1);
  TEST(strcmp(dest, "") == 0);

  /* Test: Null destination */
  rsv_strcpy(NULL, "test",
              sizeof(dest)); /* Should do nothing, no TEST needed */

  /* Test: Null source */
  rsv_strcpy(dest, NULL,
              sizeof(dest)); /* Should do nothing, no TEST needed */

  /* Test: dest_size is 0 */
  rsv_strcpy(dest, "test", 0); /* Should do nothing, no TEST needed */
  
  return 0;
}
