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

/**
 * @brief Loads the content of a text file
 *
 * This function reads the entire content of a text file specified by the file
 * path
 *
 * @param file_path The path to the text file to be loaded
 * @return A pointer to the content of the text file as a string, or NULL if an
 * error occurs The caller is responsible for freeing the returned string
 */
static const char* rsv_file_load_text_file(const char* file_path);

/**
 * @brief Saves content to a text file.
 *
 * This function writes the specified content to a text file specified by the
 * file path If the file already exists, its content will be replaced
 *
 * @param file_path The path to the text file where the content will be saved
 * @param content The content to be written to the text file
 */
static void rsv_file_save_text_file(const char* file_path, const char* content);

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
