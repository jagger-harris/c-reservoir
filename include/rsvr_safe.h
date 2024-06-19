/*
  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSVR_SAFE_H
#define RSVR_SAFE_H

#include <string.h>

void rsvr_strcpy(char* dest, const char* src, size_t dest_size);

/**************** Implementations ****************/

void rsvr_strcpy(char* dest, const char* src, size_t dest_size) {
  size_t i;
  
  if (dest == NULL || src == NULL || dest_size == 0) {
    return; /* Return if parameters are invalid */
  }

  for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  dest[i] = '\0'; /* Null terminate the destination string */
}

#endif /* RSVR_SAFE_H */
