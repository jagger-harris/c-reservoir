/*
  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSVR_CONTAINERS_H
#define RSVR_CONTAINERS_H

#include "rsvr_math.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>

/******** Dynamic array ********/

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

/******** Hash table ********/

#define RSVR_HASH_TABLE_LOAD_FACTOR 0.75

typedef struct rsvr_hash_table_entry_t {
  char* key;
  void* value;
  struct rsvr_hash_table_entry_t* next;
} rsvr_hash_table_entry_t;

typedef struct rsvr_hash_table_t {
  rsvr_hash_table_entry_t** buckets;
  unsigned int size;
  unsigned int capacity;
  unsigned int value_size;
} rsvr_hash_table_t;

static unsigned int rsvr_hash_table_hash(const char* key);
static rsvr_hash_table_t rsvr_hash_table_create(unsigned int initial_size,
                                                unsigned int value_size);
static void rsvr_hash_table_destroy(rsvr_hash_table_t* hash_table);
static void rsvr_hash_table_resize(rsvr_hash_table_t* hash_table,
                                   unsigned int new_capacity);

static void* rsvr_hash_table_get(rsvr_hash_table_t* hash_table,
                                 const char* key);
static void rsvr_hash_table_push(rsvr_hash_table_t* hash_table, const char* key,
                                 const void* value);
static void rsvr_hash_table_pop(rsvr_hash_table_t* hash_table, const char* key);

/**************** Implementations ****************/

/******** Dynamic array ********/

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

/******** Hash table ********/

static unsigned int rsvr_hash_table_hash(const char* key) {
  unsigned int hash = 0;

  while (*key) {
    hash = (hash * 31) + *key++;
  }

  return hash;
}

static rsvr_hash_table_t rsvr_hash_table_create(unsigned int initial_size,
                                                unsigned int value_size) {
  rsvr_hash_table_t hash_table;

  hash_table.buckets = (rsvr_hash_table_entry_t**)calloc(
      initial_size, sizeof(rsvr_hash_table_entry_t*));
  hash_table.size = 0;
  hash_table.capacity = initial_size;
  hash_table.value_size = value_size;

  return hash_table;
}

static void rsvr_hash_table_destroy(rsvr_hash_table_t* hash_table) {
  unsigned int i;

  for (i = 0; i < hash_table->capacity; ++i) {
    rsvr_hash_table_entry_t* entry = hash_table->buckets[i];

    while (entry) {
      rsvr_hash_table_entry_t* next = entry->next;
      free(entry->key);
      free(entry->value);
      free(entry);
      entry = next;
    }
  }

  free(hash_table->buckets);
  hash_table->buckets = NULL;
  hash_table->size = 0;
  hash_table->capacity = 0;
  hash_table->value_size = 0;
}

static void rsvr_hash_table_resize(rsvr_hash_table_t* hash_table,
                                   unsigned int new_capacity) {
  unsigned int i;
  rsvr_hash_table_entry_t** new_buckets = (rsvr_hash_table_entry_t**)calloc(
      new_capacity, sizeof(rsvr_hash_table_entry_t*));

  for (i = 0; i < hash_table->capacity; ++i) {
    rsvr_hash_table_entry_t* entry = hash_table->buckets[i];
    while (entry) {
      rsvr_hash_table_entry_t* next = entry->next;
      unsigned int new_index = rsvr_hash_table_hash(entry->key) % new_capacity;
      entry->next = new_buckets[new_index];
      new_buckets[new_index] = entry;
      entry = next;
    }
  }

  free(hash_table->buckets);
  hash_table->buckets = new_buckets;
  hash_table->capacity = new_capacity;
}

static void* rsvr_hash_table_get(rsvr_hash_table_t* hash_table,
                                 const char* key) {
  unsigned int index = rsvr_hash_table_hash(key) % hash_table->capacity;
  rsvr_hash_table_entry_t* entry = hash_table->buckets[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry->value;
    }

    entry = entry->next;
  }
  return NULL;
}

static void rsvr_hash_table_push(rsvr_hash_table_t* hash_table, const char* key,
                                 const void* value) {
  unsigned int index;
  rsvr_hash_table_entry_t* entry;
  rsvr_hash_table_entry_t* new_entry;

  if ((float)hash_table->size / hash_table->capacity >
      RSVR_HASH_TABLE_LOAD_FACTOR) {
    rsvr_hash_table_resize(hash_table, hash_table->capacity * 2);
  }

  index = rsvr_hash_table_hash(key) % hash_table->capacity;
  entry = hash_table->buckets[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      memcpy(entry->value, value, hash_table->value_size);
      return;
    }
    entry = entry->next;
  }

  new_entry = (rsvr_hash_table_entry_t*)malloc(sizeof(rsvr_hash_table_entry_t));
  new_entry->key = strdup(key);
  new_entry->value = malloc(hash_table->value_size);
  memcpy(new_entry->value, value, hash_table->value_size);
  new_entry->next = hash_table->buckets[index];
  hash_table->buckets[index] = new_entry;
  hash_table->size++;
}

static void rsvr_hash_table_pop(rsvr_hash_table_t* hash_table,
                                const char* key) {
  unsigned int index = rsvr_hash_table_hash(key) % hash_table->capacity;
  rsvr_hash_table_entry_t* entry = hash_table->buckets[index];
  rsvr_hash_table_entry_t* prev = NULL;

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      if (prev) {
        prev->next = entry->next;
      } else {
        hash_table->buckets[index] = entry->next;
      }

      free(entry->key);
      free(entry->value);
      free(entry);
      hash_table->size--;

      return;
    }

    prev = entry;
    entry = entry->next;
  }
}

#endif /* RSVR_CONTAINERS_H */
