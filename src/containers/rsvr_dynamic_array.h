#ifndef RSVR_DYNAMIC_ARRAY_H
#define RSVR_DYNAMIC_ARRAY_H

#include "../math/rsvr_math.h"

#define RSVR_DYNAMIC_ARRAY_GROWTH_AMOUNT RSVR_GOLDEN_RATIO

typedef struct rsvr_dynamic_array_t {
  void* data;
  unsigned int amount;
  unsigned int capacity;
  unsigned int element_size;
} rsvr_dynamic_array_t;

rsvr_dynamic_array_t rsvr_dynamic_array_create(unsigned int array_size,
                                               unsigned int element_size);
void rsvr_dynamic_array_destroy(rsvr_dynamic_array_t* dynamic_array);
void* rsvr_dynamic_array_get(rsvr_dynamic_array_t* dynamic_array,
                             unsigned int index);
void rsvr_dynamic_array_push(rsvr_dynamic_array_t* dynamic_array,
                             const void* element);
void rsvr_dynamic_array_pop(rsvr_dynamic_array_t* dynamic_array);

#endif /* DYNAMIC_ARRAY_H */
