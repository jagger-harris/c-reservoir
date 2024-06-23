/*
  rsv_containers.h
  Contains numerous container types

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

static rsv_dynamic_array_t rsv_dynamic_array_create(unsigned int capacity,
                                                    unsigned int element_size);
static void rsv_dynamic_array_destroy(rsv_dynamic_array_t* array);
static void* rsv_dynamic_array_get(rsv_dynamic_array_t* array,
                                   unsigned int index);
static void rsv_dynamic_array_push(rsv_dynamic_array_t* array,
                                   const void* element);
static void rsv_dynamic_array_pop(rsv_dynamic_array_t* array);

/******** Hash table ********/

#define RSV_HASH_TABLE_LOAD_FACTOR 0.75

typedef struct rsv_hash_table_entry_t {
  void* key;
  void* value;
  struct rsv_hash_table_entry_t* next;
} rsv_hash_table_entry_t;

typedef struct rsv_hash_table_t {
  rsv_hash_table_entry_t** buckets;
  unsigned int amount;
  unsigned int capacity;
  unsigned int key_size;
  unsigned int value_size;
  unsigned int (*custom_hash_func)(const void*, unsigned int);
  int (*custom_compare_func)(const void*, const void*, unsigned int);
} rsv_hash_table_t;

static unsigned int rsv_hash_table_hash(const void* data,
                                        unsigned int data_size);
static int rsv_hash_table_compare(const void* data1, const void* data2,
                                  unsigned int data_size);
static rsv_hash_table_t rsv_hash_table_create(
    unsigned int capacity, unsigned int key_size, unsigned int value_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int));
static void rsv_hash_table_destroy(rsv_hash_table_t* hash_table);
static void rsv_hash_table_resize(rsv_hash_table_t* hash_table,
                                  unsigned int new_capacity);
static void* rsv_hash_table_get(rsv_hash_table_t* hash_table, const void* key);
static void rsv_hash_table_push(rsv_hash_table_t* hash_table, const void* key,
                               const void* value);
static void rsv_hash_table_pop(rsv_hash_table_t* hash_table,
                                  const void* key);

/******** Hash set ********/

#define RSV_HASH_SET_LOAD_FACTOR 0.75

typedef struct rsv_hash_set_entry_t {
  void* data;
  struct rsv_hash_set_entry_t* next;
} rsv_hash_set_entry_t;

typedef struct rsv_hash_set_t {
  rsv_hash_set_entry_t** buckets;
  unsigned int amount;
  unsigned int capacity;
  unsigned int data_size;
  unsigned int (*custom_hash_func)(const void*, unsigned int);
  int (*custom_compare_func)(const void*, const void*, unsigned int);
} rsv_hash_set_t;

static unsigned int rsv_hash_set_hash(const void* data, unsigned int data_size);
static int rsv_hash_set_compare(const void* data_a, const void* data_b,
                                unsigned int data_size);
static rsv_hash_set_t rsv_hash_set_create(
    unsigned int capacity, unsigned int data_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int));
static void rsv_hash_set_destroy(rsv_hash_set_t* hash_set);
static void rsv_hash_set_resize(rsv_hash_set_t* hash_set,
                                unsigned int new_capacity);
static int rsv_hash_set_contains(rsv_hash_set_t* hash_set, const void* data);
static void rsv_hash_set_push(rsv_hash_set_t* hash_set, const void* data);
static void rsv_hash_set_pop(rsv_hash_set_t* hash_set, const void* data);

/**************** Implementations ****************/

/******** Dynamic array ********/

static rsv_dynamic_array_t rsv_dynamic_array_create(unsigned int capacity,
                                                    unsigned int element_size) {
  rsv_dynamic_array_t array;

  array.data = malloc(capacity * element_size);
  array.amount = 0;
  array.capacity = capacity;
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

static unsigned int rsv_hash_table_hash(const void* data,
                                        unsigned int data_size) {
  const unsigned char* data_key = (const unsigned char*)data;
  unsigned int hash = 0;
  unsigned int i;

  for (i = 0; i < data_size; ++i) {
    hash = (hash * 31) + data_key[i];
  }

  return hash;
}

static int rsv_hash_table_compare(const void* data1, const void* data2,
                                  unsigned int data_size) {
  return memcmp(data1, data2, data_size) == 0;
}

static rsv_hash_table_t rsv_hash_table_create(
    unsigned int capacity, unsigned int key_size, unsigned int value_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int)) {
  rsv_hash_table_t hash_table;

  hash_table.buckets = (rsv_hash_table_entry_t**)calloc(
      capacity, sizeof(rsv_hash_table_entry_t*));
  hash_table.amount = 0;
  hash_table.capacity = capacity;
  hash_table.key_size = key_size;
  hash_table.value_size = value_size;

  if (custom_hash_func == NULL) {
    custom_hash_func = rsv_hash_table_hash;
  }

  if (custom_compare_func == NULL) {
    custom_compare_func = rsv_hash_table_compare;
  }

  hash_table.custom_hash_func = custom_hash_func;
  hash_table.custom_compare_func = custom_compare_func;

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
  hash_table->amount = 0;
  hash_table->capacity = 0;
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
      unsigned int new_index =
          hash_table->custom_hash_func(entry->key, hash_table->key_size) %
          new_capacity;
      entry->next = new_buckets[new_index];
      new_buckets[new_index] = entry;
      entry = next;
    }
  }

  free(hash_table->buckets);
  hash_table->buckets = new_buckets;
  hash_table->capacity = new_capacity;
}

static void* rsv_hash_table_get(rsv_hash_table_t* hash_table, const void* key) {
  unsigned int index = hash_table->custom_hash_func(key, hash_table->key_size) %
                       hash_table->capacity;
  rsv_hash_table_entry_t* entry = hash_table->buckets[index];

  while (entry) {
    if (hash_table->custom_compare_func(entry->key, key,
                                        hash_table->key_size)) {
      return entry->value;
    }
    entry = entry->next;
  }
  return NULL;
}

static void rsv_hash_table_push(rsv_hash_table_t* hash_table, const void* key,
                               const void* value) {
  unsigned int index;
  rsv_hash_table_entry_t* entry;
  rsv_hash_table_entry_t* new_entry;

  if ((float)hash_table->amount / hash_table->capacity >
      RSV_HASH_TABLE_LOAD_FACTOR) {
    rsv_hash_table_resize(hash_table, hash_table->capacity * 2);
  }

  index = hash_table->custom_hash_func(key, hash_table->key_size) %
          hash_table->capacity;
  entry = hash_table->buckets[index];

  while (entry) {
    if (hash_table->custom_compare_func(entry->key, key,
                                        hash_table->key_size)) {
      memcpy(entry->value, value, hash_table->value_size);
      return;
    }
    entry = entry->next;
  }

  new_entry = (rsv_hash_table_entry_t*)malloc(sizeof(rsv_hash_table_entry_t));
  new_entry->key = malloc(hash_table->key_size);
  new_entry->value = malloc(hash_table->value_size);
  memcpy(new_entry->key, key, hash_table->key_size);
  memcpy(new_entry->value, value, hash_table->value_size);
  new_entry->next = hash_table->buckets[index];
  hash_table->buckets[index] = new_entry;
  hash_table->amount++;
}

static void rsv_hash_table_pop(rsv_hash_table_t* hash_table,
                                  const void* key) {
  unsigned int index = hash_table->custom_hash_func(key, hash_table->key_size) %
                       hash_table->capacity;
  rsv_hash_table_entry_t* entry = hash_table->buckets[index];
  rsv_hash_table_entry_t* prev = NULL;

  while (entry) {
    if (hash_table->custom_compare_func(entry->key, key,
                                        hash_table->key_size)) {
      if (prev) {
        prev->next = entry->next;
      } else {
        hash_table->buckets[index] = entry->next;
      }

      free(entry->key);
      free(entry->value);
      free(entry);
      hash_table->amount--;

      return;
    }

    prev = entry;
    entry = entry->next;
  }
}

/******** Hash set ********/

static unsigned int rsv_hash_set_hash(const void* data,
                                      unsigned int data_size) {
  const unsigned char* data_key = (const unsigned char*)data;
  unsigned int hash = 0;
  unsigned int i;

  for (i = 0; i < data_size; ++i) {
    hash = (hash * 31) + data_key[i];
  }

  return hash;
}

static int rsv_hash_set_compare(const void* data1, const void* data2,
                                unsigned int data_size) {
  return memcmp(data1, data2, data_size) == 0;
}

static rsv_hash_set_t rsv_hash_set_create(
    unsigned int capacity, unsigned int data_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int)) {
  rsv_hash_set_t hash_set;

  hash_set.buckets =
      (rsv_hash_set_entry_t**)calloc(capacity, sizeof(rsv_hash_set_entry_t*));
  hash_set.amount = 0;
  hash_set.capacity = capacity;
  hash_set.data_size = data_size;

  if (custom_hash_func == NULL) {
    custom_hash_func = rsv_hash_set_hash;
  }

  if (custom_compare_func == NULL) {
    custom_compare_func = rsv_hash_set_compare;
  }

  hash_set.custom_hash_func = custom_hash_func;
  hash_set.custom_compare_func = custom_compare_func;

  return hash_set;
}

static void rsv_hash_set_destroy(rsv_hash_set_t* hash_set) {
  unsigned int i;

  for (i = 0; i < hash_set->capacity; ++i) {
    rsv_hash_set_entry_t* entry = hash_set->buckets[i];

    while (entry) {
      rsv_hash_set_entry_t* next = entry->next;
      free(entry->data);
      free(entry);
      entry = next;
    }
  }

  free(hash_set->buckets);
  hash_set->buckets = NULL;
  hash_set->amount = 0;
  hash_set->capacity = 0;
}

static void rsv_hash_set_resize(rsv_hash_set_t* hash_set,
                                unsigned int new_capacity) {
  unsigned int i;
  rsv_hash_set_entry_t** new_buckets = (rsv_hash_set_entry_t**)calloc(
      new_capacity, sizeof(rsv_hash_set_entry_t*));

  for (i = 0; i < hash_set->capacity; ++i) {
    rsv_hash_set_entry_t* entry = hash_set->buckets[i];
    while (entry) {
      rsv_hash_set_entry_t* next = entry->next;
      unsigned int new_index =
          hash_set->custom_hash_func(entry->data, hash_set->data_size) %
          new_capacity;
      entry->next = new_buckets[new_index];
      new_buckets[new_index] = entry;
      entry = next;
    }
  }

  free(hash_set->buckets);
  hash_set->buckets = new_buckets;
  hash_set->capacity = new_capacity;
}

static int rsv_hash_set_contains(rsv_hash_set_t* hash_set, const void* data) {
  unsigned int index = hash_set->custom_hash_func(data, hash_set->data_size) %
                       hash_set->capacity;
  rsv_hash_set_entry_t* entry = hash_set->buckets[index];

  while (entry) {
    if (hash_set->custom_compare_func(entry->data, data, hash_set->data_size)) {
      return 1;
    }

    entry = entry->next;
  }
  return 0;
}

static void rsv_hash_set_push(rsv_hash_set_t* hash_set, const void* data) {
  unsigned int index;
  rsv_hash_set_entry_t* entry;
  rsv_hash_set_entry_t* new_entry;

  if ((float)hash_set->amount / hash_set->capacity > RSV_HASH_SET_LOAD_FACTOR) {
    rsv_hash_set_resize(hash_set, hash_set->capacity * 2);
  }

  index = hash_set->custom_hash_func(data, hash_set->data_size) %
          hash_set->capacity;
  entry = hash_set->buckets[index];

  while (entry) {
    if (hash_set->custom_compare_func(entry->data, data, hash_set->data_size)) {
      return;
    }
    entry = entry->next;
  }

  new_entry = (rsv_hash_set_entry_t*)malloc(sizeof(rsv_hash_set_entry_t));
  new_entry->data = malloc(hash_set->data_size);
  memcpy(new_entry->data, data, hash_set->data_size);
  new_entry->next = hash_set->buckets[index];
  hash_set->buckets[index] = new_entry;
  hash_set->amount++;
}

static void rsv_hash_set_pop(rsv_hash_set_t* hash_set, const void* data) {
  unsigned int index = hash_set->custom_hash_func(data, hash_set->data_size) %
                       hash_set->capacity;
  rsv_hash_set_entry_t* entry = hash_set->buckets[index];
  rsv_hash_set_entry_t* prev = NULL;

  while (entry) {
    if (hash_set->custom_compare_func(entry->data, data, hash_set->data_size)) {
      if (prev) {
        prev->next = entry->next;
      } else {
        hash_set->buckets[index] = entry->next;
      }

      free(entry->data);
      free(entry);
      hash_set->amount--;

      return;
    }

    prev = entry;
    entry = entry->next;
  }
}

#endif /* RSV_CONTAINERS_H */
