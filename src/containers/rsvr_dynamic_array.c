#include "rsvr_dynamic_array.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>

rsvr_dynamic_array_t rsvr_dynamic_array_create(unsigned int array_size,
                                               unsigned int element_size) {
  rsvr_dynamic_array_t dynamic_array;

  dynamic_array.data = malloc(array_size * element_size);
  dynamic_array.amount = 0;
  dynamic_array.capacity = array_size;
  dynamic_array.element_size = element_size;

  return dynamic_array;
}

void rsvr_dynamic_array_destroy(rsvr_dynamic_array_t* dynamic_array) {
  free(dynamic_array->data);
  dynamic_array->data = NULL;
  dynamic_array->amount = 0;
  dynamic_array->capacity = 0;
  dynamic_array->element_size = 0;
}

void* rsvr_dynamic_array_get(rsvr_dynamic_array_t* dynamic_array,
                             unsigned int index) {
  if (index >= dynamic_array->amount) {
    return NULL;
  }

  return (void*)((unsigned char*)dynamic_array->data +
                 index * dynamic_array->element_size);
}

void rsvr_dynamic_array_push(rsvr_dynamic_array_t* dynamic_array,
                             const void* element) {
  unsigned char* destination;

  if (dynamic_array->amount >= dynamic_array->capacity) {
    dynamic_array->capacity = (size_t)ceil(dynamic_array->capacity *
                                           RSVR_DYNAMIC_ARRAY_GROWTH_AMOUNT);
    dynamic_array->data =
        realloc(dynamic_array->data,
                dynamic_array->capacity * dynamic_array->element_size);
  }

  destination = (unsigned char*)dynamic_array->data +
                dynamic_array->amount * dynamic_array->element_size;
  memcpy((void*)destination, element, dynamic_array->element_size);
  dynamic_array->amount++;
}

void rsvr_dynamic_array_pop(rsvr_dynamic_array_t* dynamic_array) {
  free(dynamic_array->data);
  dynamic_array->data = NULL;
  dynamic_array->amount = 0;
  dynamic_array->capacity = 0;
  dynamic_array->element_size = 0;
}
