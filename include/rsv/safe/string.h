/*
  string.h
  Safe implementations of standard string.h

  Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/
*/

#ifndef RSV_STRCPY_H
#define RSV_STRCPY_H

#include <string.h>

/**
 * @brief Copies a string from the source to the destination with size
 * limitation.
 *
 * This function copies the string from the source to the destination ensuring
 * that it does not exceed the given destination size. If the source string is
 * longer than the destination size, it will be truncated to fit.
 *
 * @param destination A pointer to the destination buffer where the string will
 * be copied.
 * @param source A pointer to the source string that will be copied.
 * @param destination_size The size of the destination buffer, which limits the
 * number of characters copied. It ensures no buffer overflow.
 *
 * @note The destination string will be null-terminated if there is space in the
 *       destination buffer, but if the source is too long, the string will be
 *       truncated and properly terminated.
 */
static inline void rsv_strcpy(char* destination, const char* source,
                              size_t destination_size) {
  size_t i;

  if (destination == NULL || source == NULL || destination_size == 0) {
    return;
  }

  for (i = 0; i < destination_size - 1 && source[i] != '\0'; i++) {
    destination[i] = source[i];
  }

  destination[i] = '\0';
}

#endif /* RSV_STRCPY_H */
