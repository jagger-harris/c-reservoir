/*
  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_CONTAINERS_H
#define RSV_CONTAINERS_H

#include "rsv_math.h"
#include <math.h>
#include <memory.h>
#include <stdlib.h>

/******** Dynamic array ********/

#define RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT RSV_GOLDEN_RATIO

typedef struct rsv_dynamic_array_t {
  void* data;
  unsigned int amount;
  unsigned int capacity;
  unsigned int element_size;
} rsv_dynamic_array_t;

static rsv_dynamic_array_t
rsv_dynamic_array_create(unsigned int array_size, unsigned int element_size);
static void rsv_dynamic_array_destroy(rsv_dynamic_array_t* array);
static void* rsv_dynamic_array_get(rsv_dynamic_array_t* array,
                                    unsigned int index);
static void rsv_dynamic_array_push(rsv_dynamic_array_t* array,
                                    const void* element);
static void rsv_dynamic_array_pop(rsv_dynamic_array_t* array);

/******** Hash table ********/

#define RSV_HASH_TABLE_LOAD_FACTOR 0.75

typedef struct rsv_hash_table_entry_t {
  char* key;
  void* value;
  struct rsv_hash_table_entry_t* next;
} rsv_hash_table_entry_t;

typedef struct rsv_hash_table_t {
  rsv_hash_table_entry_t** buckets;
  unsigned int size;
  unsigned int capacity;
  unsigned int value_size;
} rsv_hash_table_t;

static unsigned int rsv_hash_table_hash(const char* key);
static rsv_hash_table_t rsv_hash_table_create(unsigned int initial_size,
                                                unsigned int value_size);
static void rsv_hash_table_destroy(rsv_hash_table_t* hash_table);
static void rsv_hash_table_resize(rsv_hash_table_t* hash_table,
                                   unsigned int new_capacity);
static void* rsv_hash_table_get(rsv_hash_table_t* hash_table,
                                 const char* key);
static void rsv_hash_table_push(rsv_hash_table_t* hash_table, const char* key,
                                 const void* value);
static void rsv_hash_table_pop(rsv_hash_table_t* hash_table, const char* key);

/**************** Implementations ****************/

/******** Dynamic array ********/

static rsv_dynamic_array_t
rsv_dynamic_array_create(unsigned int array_size, unsigned int element_size) {
  rsv_dynamic_array_t array;

  array.data = malloc(array_size * element_size);
  array.amount = 0;
  array.capacity = array_size;
  array.element_size = element_size;

  return array;
}

static void rsv_dynamic_array_destroy(rsv_dynamic_array_t* array) {
  free(array->data);
  array->data = NULL;
  array->amount = 0;
  array->capacity = 0;
  array->element_size = 0;
}

static void* rsv_dynamic_array_get(rsv_dynamic_array_t* array,
                                    unsigned int index) {
  if (index >= array->amount) {
    return NULL;
  }

  return (void*)((unsigned char*)array->data + index * array->element_size);
}

static void rsv_dynamic_array_push(rsv_dynamic_array_t* array,
                                    const void* element) {
  unsigned char* destination;

  if (array->amount >= array->capacity) {
    array->capacity =
        (size_t)ceil(array->capacity * RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT);
    array->data = realloc(array->data, array->capacity * array->element_size);
  }

  destination =
      (unsigned char*)array->data + array->amount * array->element_size;
  memcpy((void*)destination, element, array->element_size);
  array->amount++;
}

static void rsv_dynamic_array_pop(rsv_dynamic_array_t* array) {
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

static unsigned int rsv_hash_table_hash(const char* key) {
  unsigned int hash = 0;

  while (*key) {
    hash = (hash * 31) + *key++;
  }

  return hash;
}

static rsv_hash_table_t rsv_hash_table_create(unsigned int initial_size,
                                                unsigned int value_size) {
  rsv_hash_table_t hash_table;

  hash_table.buckets = (rsv_hash_table_entry_t**)calloc(
      initial_size, sizeof(rsv_hash_table_entry_t*));
  hash_table.size = 0;
  hash_table.capacity = initial_size;
  hash_table.value_size = value_size;

  return hash_table;
}

static void rsv_hash_table_destroy(rsv_hash_table_t* hash_table) {
  unsigned int i;

  for (i = 0; i < hash_table->capacity; ++i) {
    rsv_hash_table_entry_t* entry = hash_table->buckets[i];

    while (entry) {
      rsv_hash_table_entry_t* next = entry->next;
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

static void rsv_hash_table_resize(rsv_hash_table_t* hash_table,
                                   unsigned int new_capacity) {
  unsigned int i;
  rsv_hash_table_entry_t** new_buckets = (rsv_hash_table_entry_t**)calloc(
      new_capacity, sizeof(rsv_hash_table_entry_t*));

  for (i = 0; i < hash_table->capacity; ++i) {
    rsv_hash_table_entry_t* entry = hash_table->buckets[i];
    while (entry) {
      rsv_hash_table_entry_t* next = entry->next;
      unsigned int new_index = rsv_hash_table_hash(entry->key) % new_capacity;
      entry->next = new_buckets[new_index];
      new_buckets[new_index] = entry;
      entry = next;
    }
  }

  free(hash_table->buckets);
  hash_table->buckets = new_buckets;
  hash_table->capacity = new_capacity;
}

static void* rsv_hash_table_get(rsv_hash_table_t* hash_table,
                                 const char* key) {
  unsigned int index = rsv_hash_table_hash(key) % hash_table->capacity;
  rsv_hash_table_entry_t* entry = hash_table->buckets[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry->value;
    }

    entry = entry->next;
  }
  return NULL;
}

static void rsv_hash_table_push(rsv_hash_table_t* hash_table, const char* key,
                                 const void* value) {
  unsigned int index;
  rsv_hash_table_entry_t* entry;
  rsv_hash_table_entry_t* new_entry;

  if ((float)hash_table->size / hash_table->capacity >
      RSV_HASH_TABLE_LOAD_FACTOR) {
    rsv_hash_table_resize(hash_table, hash_table->capacity * 2);
  }

  index = rsv_hash_table_hash(key) % hash_table->capacity;
  entry = hash_table->buckets[index];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      memcpy(entry->value, value, hash_table->value_size);
      return;
    }
    entry = entry->next;
  }

  new_entry = (rsv_hash_table_entry_t*)malloc(sizeof(rsv_hash_table_entry_t));
  new_entry->key = strdup(key);
  new_entry->value = malloc(hash_table->value_size);
  memcpy(new_entry->value, value, hash_table->value_size);
  new_entry->next = hash_table->buckets[index];
  hash_table->buckets[index] = new_entry;
  hash_table->size++;
}

static void rsv_hash_table_pop(rsv_hash_table_t* hash_table,
                                const char* key) {
  unsigned int index = rsv_hash_table_hash(key) % hash_table->capacity;
  rsv_hash_table_entry_t* entry = hash_table->buckets[index];
  rsv_hash_table_entry_t* prev = NULL;

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

#endif /* RSV_CONTAINERS_H */
