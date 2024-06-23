/*
  rsv_file_management.h
  Contains file management functions

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_FILE_MANAGEMENT_H
#define RSV_FILE_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>

/******** Text files ********/
static const char* rsv_file_load_text_file(const char* file_path);
static void rsv_file_save_text_file(const char* file_path,
                                     const char* content);

/**************** Implementations ****************/

/******** Text files ********/
static const char* rsv_file_load_text_file(const char* file_path) {
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

static void rsv_file_save_text_file(const char* file_path,
                                     const char* content) {
  FILE* file = fopen(file_path, "w");

  if (!file) {
    fprintf(stderr, "Failed to open file\n");

    return;
  }

  fprintf(file, "%s", content);
  fclose(file);
}

#endif /* RSV_FILE_MANAGEMENT_H */
