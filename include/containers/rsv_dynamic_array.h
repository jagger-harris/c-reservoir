/*
  rsv_dynamic_array.h
  Reservoir implementation of a dynamic array

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_DYNAMIC_ARRAY_H
#define RSV_DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>

#define RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT 1.61803398874989484820

/**
 * @brief A dynamic array which automatically resizes and can take any type.
 * Make sure to cast your type from the void pointer.
 *
 */
typedef struct rsv_dynamic_array_t {
  /**
   * @brief The array data. Use this to access data from within the array.
   *
   */
  void* data;
  /**
   * @brief The amount of data values in the array.
   *
   */
  unsigned int amount;
  /**
   * @brief The amount of data that can be stored.
   *
   */
  unsigned int capacity;
  /**
   * @brief The size of an element in memory.
   *
   */
  unsigned int element_size;
} rsv_dynamic_array_t;

/**
 * @brief Creates a dynamic array.
 *
 * @param capacity Initial capacity of the array.
 * @param element_size Size of each element in the array.
 * @return A rsv_dynamic_array_t struct representing the created dynamic array.
 */
static inline rsv_dynamic_array_t
rsv_dynamic_array_create(unsigned int capacity, unsigned int element_size) {
  rsv_dynamic_array_t array;

  array.data = malloc(capacity * element_size);
  array.amount = 0;
  array.capacity = capacity;
  array.element_size = element_size;

  return array;
}

/**
 * @brief Destroys a dynamic array, freeing all associated memory.
 *
 * @param array Pointer to the dynamic array to destroy.
 */
static inline void rsv_dynamic_array_destroy(rsv_dynamic_array_t* array) {
  free(array->data);
  array->data = NULL;
  array->amount = 0;
  array->capacity = 0;
  array->element_size = 0;
}

/**
 * @brief Gets the element at the specified index in the dynamic array.
 *
 * @param array Pointer to the dynamic array.
 * @param index Index of the element to retrieve.
 * @return Pointer to the element at the specified index.
 */
static inline void* rsv_dynamic_array_get(rsv_dynamic_array_t* array,
                                          unsigned int index) {
  if (index >= array->amount) {
    return NULL;
  }

  return (void*)((unsigned char*)array->data + index * array->element_size);
}

/**
 * @brief Adds an element to the end of the dynamic array.
 *
 * @param array Pointer to the dynamic array.
 * @param element Pointer to the element to add.
 */
static inline void rsv_dynamic_array_push(rsv_dynamic_array_t* array,
                                          const void* element) {
  unsigned char* destination;

  if (array->amount >= array->capacity) {
    array->capacity =
        (size_t)(array->capacity * RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT + 1);
    array->data = realloc(array->data, array->capacity * array->element_size);
  }

  destination =
      (unsigned char*)array->data + array->amount * array->element_size;
  memcpy((void*)destination, element, array->element_size);
  array->amount++;
}

/**
 * @brief Removes the last element from the dynamic array.
 *
 * @param array Pointer to the dynamic array.
 */
static inline void rsv_dynamic_array_pop(rsv_dynamic_array_t* array) {
  if (array->amount == 0) {
    return;
  }

  array->amount--;

  if (array->amount < array->capacity / 4) {
    array->capacity /= 2;
    array->data = realloc(array->data, array->capacity * array->element_size);
  }
}

#endif /* RSV_DYNAMIC_ARRAY_H */
