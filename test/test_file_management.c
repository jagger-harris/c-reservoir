#include "../src/files/rsvr_file_management.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_file_management(void) {
  const char* loaded_content = "";
  const char* file_path = "test_file.txt";
  const char* save_content = "This is an example of a file.\n\nLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
  rsvr_file_save_text_file(file_path, save_content);

  loaded_content = rsvr_file_load_text_file(file_path);
  assert(loaded_content != NULL);
  assert(strcmp(loaded_content, save_content) == 0);
  free((void*)loaded_content);

  printf("All file management tests passed!\n");
}

int main(void) {
  test_file_management();
  exit(EXIT_SUCCESS);
}
