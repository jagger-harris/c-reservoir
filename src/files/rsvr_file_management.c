#include "rsvr_file_management.h"
#include <stdio.h>
#include <stdlib.h>

const char* rsvr_file_load_text_file(const char* file_path) {
  FILE* file = fopen(file_path, "r");
  long length = 0;
  char* content = "";

  if (!file) {
    fprintf(stderr, "Failed to open file\n");

    return NULL;
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);

  content = (char*)malloc((length + 1) * sizeof(char));
  fread(content, 1, length, file);
  content[length] = '\0';

  fclose(file);

  return content;
}

void rsvr_file_save_text_file(const char* file_path, const char* content) {
  FILE* file = fopen(file_path, "w");

  if (!file) {
    fprintf(stderr, "Failed to open file\n");

    return;
  }

  fprintf(file, "%s", content);
  fclose(file);
}
