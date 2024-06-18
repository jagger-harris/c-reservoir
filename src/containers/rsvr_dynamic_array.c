#include "rsvr_dynamic_array.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>

rsvr_dynamic_array_t rsvr_dynamic_array_create(unsigned int array_size,
                                               unsigned int element_size) {
  rsvr_dynamic_array_t array;

  array.data = malloc(array_size * element_size);
  array.amount = 0;
  array.capacity = array_size;
  array.element_size = element_size;

  return array;
}

void rsvr_dynamic_array_destroy(rsvr_dynamic_array_t* array) {
  free(array->data);
  array->data = NULL;
  array->amount = 0;
  array->capacity = 0;
  array->element_size = 0;
}

void* rsvr_dynamic_array_get(rsvr_dynamic_array_t* array, unsigned int index) {
  if (index >= array->amount) {
    return NULL;
  }

  return (void*)((unsigned char*)array->data + index * array->element_size);
}

void rsvr_dynamic_array_push(rsvr_dynamic_array_t* array, const void* element) {
  unsigned char* destination;

  if (array->amount >= array->capacity) {
    array->capacity =
        (size_t)ceil(array->capacity * RSVR_DYNAMIC_ARRAY_GROWTH_AMOUNT);
    array->data = realloc(array->data, array->capacity * array->element_size);
  }

  destination =
      (unsigned char*)array->data + array->amount * array->element_size;
  memcpy((void*)destination, element, array->element_size);
  array->amount++;
}

void rsvr_dynamic_array_pop(rsvr_dynamic_array_t* array) {
  if (array->amount == 0) {
    return;
  }

  array->amount--;

  /* Shrink array if number of elements is less than a quarter */
  if (array->amount < array->capacity / 4) {
    array->capacity /= 2;
    array->data = realloc(array->data, array->capacity * array->element_size);
  }
}
