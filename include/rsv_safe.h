/*
  rsv_safe.h
  Contains safe variants of C std functions

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_SAFE_H
#define RSV_SAFE_H

#include <string.h>

/**
 * @brief Safely copies a string to a destination buffer
 *
 * This function copies the string from the source buffer to the destination
 * buffer, ensuring that no buffer overflow occurs by limiting the number of
 * characters copied to the size of the destination buffer minus one, and always
 * null-terminating the result
 *
 * @param dest The destination buffer where the string will be copied
 * @param src The source string to be copied
 * @param dest_size The size of the destination buffer
 */
void rsv_strcpy(char* dest, const char* src, size_t dest_size);

/**************** Implementations ****************/

void rsv_strcpy(char* dest, const char* src, size_t dest_size) {
  size_t i;

  if (dest == NULL || src == NULL || dest_size == 0) {
    return; /* Return if parameters are invalid */
  }

  for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  dest[i] = '\0'; /* Null terminate the destination string */
}

#endif /* RSV_SAFE_H */
