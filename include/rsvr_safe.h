/*
  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSVR_SAFE_H
#define RSVR_SAFE_H

#include <string.h>

void strcpy_safe(char* dest, const char* src, size_t dest_size);

/**************** Implementations ****************/

void strcpy_safe(char* dest, const char* src, size_t dest_size) {
  if (dest == NULL || src == NULL || dest_size == 0) {
    return; /* Return if parameters are invalid */
  }

  size_t src_len = strlen(src);

  /* Ensure destination buffer has space for null terminator */
  if (src_len >= dest_size) {
    return;
  }

  /* Leave space for null terminator */
  strncpy(dest, src, dest_size - 1);
  dest[dest_size - 1] = '\0';
}

#endif /* RSVR_SAFE_H */
