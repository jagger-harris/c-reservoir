#ifndef RSVR_CONTAINERS_H
#define RSVR_CONTAINERS_H

#include "rsvr_math.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>

/**** Dynamic array ****/

#define RSVR_DYNAMIC_ARRAY_GROWTH_AMOUNT RSVR_GOLDEN_RATIO

typedef struct rsvr_dynamic_array_t {
  void* data;
  unsigned int amount;
  unsigned int capacity;
  unsigned int element_size;
} rsvr_dynamic_array_t;

static rsvr_dynamic_array_t
rsvr_dynamic_array_create(unsigned int array_size, unsigned int element_size);
static void rsvr_dynamic_array_destroy(rsvr_dynamic_array_t* array);
static void* rsvr_dynamic_array_get(rsvr_dynamic_array_t* array,
                                    unsigned int index);
static void rsvr_dynamic_array_push(rsvr_dynamic_array_t* array,
                                    const void* element);
static void rsvr_dynamic_array_pop(rsvr_dynamic_array_t* array);

/**************** Implementations ****************/

/**** Dynamic array ****/
static rsvr_dynamic_array_t
rsvr_dynamic_array_create(unsigned int array_size, unsigned int element_size) {
  rsvr_dynamic_array_t array;

  array.data = malloc(array_size * element_size);
  array.amount = 0;
  array.capacity = array_size;
  array.element_size = element_size;

  return array;
}

static void rsvr_dynamic_array_destroy(rsvr_dynamic_array_t* array) {
  free(array->data);
  array->data = NULL;
  array->amount = 0;
  array->capacity = 0;
  array->element_size = 0;
}

static void* rsvr_dynamic_array_get(rsvr_dynamic_array_t* array,
                                    unsigned int index) {
  if (index >= array->amount) {
    return NULL;
  }

  return (void*)((unsigned char*)array->data + index * array->element_size);
}

static void rsvr_dynamic_array_push(rsvr_dynamic_array_t* array,
                                    const void* element) {
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

static void rsvr_dynamic_array_pop(rsvr_dynamic_array_t* array) {
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

#endif /* RSVR_CONTAINERS_H */
