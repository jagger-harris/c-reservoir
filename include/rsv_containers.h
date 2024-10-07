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
#include <memory.h>
#include <stdlib.h>

/******** Dynamic array ********/

#define RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT RSV_GOLDEN_RATIO

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
 * @brief Creates a dynamic array
 *
 * @param capacity Initial capacity of the array
 * @param element_size Size of each element in the array
 * @return A rsv_dynamic_array_t struct representing the created dynamic array
 */
static rsv_dynamic_array_t rsv_dynamic_array_create(unsigned int capacity,
                                                    unsigned int element_size);

/**
 * @brief Destroys a dynamic array, freeing all associated memory
 *
 * @param array Pointer to the dynamic array to destroy
 */
static void rsv_dynamic_array_destroy(rsv_dynamic_array_t* array);

/**
 * @brief Gets the element at the specified index in the dynamic array
 *
 * @param array Pointer to the dynamic array
 * @param index Index of the element to retrieve
 * @return Pointer to the element at the specified index
 */
static void* rsv_dynamic_array_get(rsv_dynamic_array_t* array,
                                   unsigned int index);

/**
 * @brief Adds an element to the end of the dynamic array
 *
 * @param array Pointer to the dynamic array
 * @param element Pointer to the element to add
 */
static void rsv_dynamic_array_push(rsv_dynamic_array_t* array,
                                   const void* element);

/**
 * @brief Removes the last element from the dynamic array
 *
 * @param array Pointer to the dynamic array
 */
static void rsv_dynamic_array_pop(rsv_dynamic_array_t* array);

/******** Hash table ********/

#define RSV_HASH_TABLE_LOAD_FACTOR 0.75

/**
 * @brief A hash table entry. Should not be directly used unless necessary.
 *
 */
typedef struct rsv_hash_table_entry_t {
  void* key;
  void* value;
  struct rsv_hash_table_entry_t* next;
} rsv_hash_table_entry_t;

/**
 * @brief A hash table which automatically resizes and can take any type. Make
 * sure to cast your type from the void pointer.
 *
 */
typedef struct rsv_hash_table_t {
  /**
   * @brief The hash table data. Use this to access data from within the hash
   * table.
   *
   */
  rsv_hash_table_entry_t** data;
  /**
   * @brief The amount of hash table entries in the hash table.
   *
   */
  unsigned int amount;
  /**
   * @brief The amount of hash table entries that can be stored.
   *
   */
  unsigned int capacity;
  /**
   * @brief The size of the key in memory.
   *
   */
  unsigned int key_size;
  /**
   * @brief The size of the value in memory.
   *
   */
  unsigned int value_size;
  /**
   * @brief Use if the hash table would need a custom hash function. Set to NULL
   * for default hashing.
   *
   */
  unsigned int (*custom_hash_func)(const void*, unsigned int);
  /**
   * @brief Use if the hash table would need a custom comparing function for
   * comparing values inside the table. Set to NULL for default comparing.
   *
   */
  int (*custom_compare_func)(const void*, const void*, unsigned int);
} rsv_hash_table_t;

/**
 * @brief Generates a hash for the given data
 *
 * @param data Pointer to the data to hash
 * @param element_size Size of the data in memory
 * @return The generated hash value
 */
static unsigned int rsv_hash_table_hash(const void* data,
                                        unsigned int element_size);

/**
 * @brief Compares two pieces of data
 *
 * @param data_a Pointer to the first data
 * @param data_b Pointer to the second data
 * @param element_size Size of the data in memory
 * @return 1 if the data are equal, 0 otherwise
 */
static int rsv_hash_table_compare(const void* data_a, const void* data_b,
                                  unsigned int element_size);

/**
 * @brief Creates a hash table
 *
 * @param capacity Initial capacity of the hash table
 * @param key_size Size of each key in memory
 * @param value_size Size of each value in memory
 * @param custom_hash_func Pointer to a custom hash function, or NULL to use the
 * default
 * @param custom_compare_func Pointer to a custom compare function, or NULL to
 * use the default
 * @return A rsv_hash_table_t struct representing the created hash table
 */
static rsv_hash_table_t rsv_hash_table_create(
    unsigned int capacity, unsigned int key_size, unsigned int value_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int));

/**
 * @brief Destroys a hash table, freeing all associated memory
 *
 * @param hash_table Pointer to the hash table to destroy
 */
static void rsv_hash_table_destroy(rsv_hash_table_t* hash_table);

/**
 * @brief Resizes a hash table to the new specified capacity
 *
 * @param hash_table Pointer to the hash table to resize
 * @param new_capacity The new capacity for the hash table
 */
static void rsv_hash_table_resize(rsv_hash_table_t* hash_table,
                                  unsigned int new_capacity);

/**
 * @brief Retrieves the value associated with the specified key in the hash
 * table
 *
 * @param hash_table Pointer to the hash table
 * @param key Pointer to the key
 * @return Pointer to the value associated with the key, or NULL if the key is
 * not found
 */
static void* rsv_hash_table_get(rsv_hash_table_t* hash_table, const void* key);

/**
 * @brief Adds a key-value pair to the hash table
 *
 * @param hash_table Pointer to the hash table
 * @param key Pointer to the key
 * @param value Pointer to the value
 */
static void rsv_hash_table_push(rsv_hash_table_t* hash_table, const void* key,
                                const void* value);

/**
 * @brief Removes a key-value pair from the hash table
 *
 * @param hash_table Pointer to the hash table
 * @param key Pointer to the key of the pair to remove
 */
static void rsv_hash_table_pop(rsv_hash_table_t* hash_table, const void* key);

/******** Hash set ********/

#define RSV_HASH_SET_LOAD_FACTOR 0.75

/**
 * @brief A hash set entry. Should not be directly used unless necessary.
 *
 */
typedef struct rsv_hash_set_entry_t {
  void* data;
  struct rsv_hash_set_entry_t* next;
} rsv_hash_set_entry_t;

/**
 * @brief A hash set which automatically resizes and can take any type. Make
 * sure to cast your type from the void pointer.
 *
 */
typedef struct rsv_hash_set_t {
  /**
   * @brief The hash set data. Use this to access data from within the hash set.
   *
   */
  rsv_hash_set_entry_t** data;
  /**
   * @brief The amount of hash set entries in the hash set.
   *
   */
  unsigned int amount;
  /**
   * @brief The amount of hash set entries that can be stored.
   *
   */
  unsigned int capacity;
  /**
   * @brief The size of an element in memory.
   *
   */
  unsigned int element_size;
  /**
   * @brief Use if the hash set would need a custom hash function. Set to NULL
   * for default hashing.
   *
   */
  unsigned int (*custom_hash_func)(const void*, unsigned int);
  /**
   * @brief Use if the hash table would need a custom comparing function for
   * comparing values inside the table. Set to NULL for default comparing.
   *
   */
  int (*custom_compare_func)(const void*, const void*, unsigned int);
} rsv_hash_set_t;

/**
 * @brief Generates a hash for the given data
 *
 * @param data Pointer to the data to hash
 * @param element_size Size of the data in memory
 * @return The generated hash value
 */
static unsigned int rsv_hash_set_hash(const void* data,
                                      unsigned int element_size);

/**
 * @brief Compares two pieces of data
 *
 * @param data_a Pointer to the first data
 * @param data_b Pointer to the second data
 * @param element_size Size of the data in memory
 * @return 1 if the data are equal, 0 otherwise
 */
static int rsv_hash_set_compare(const void* data_a, const void* data_b,
                                unsigned int element_size);

/**
 * @brief Creates a hash set.
 *
 * @param capacity Initial capacity of the hash set
 * @param element_size Size of each element in the hash set
 * @param custom_hash_func Pointer to a custom hash function, or NULL to use the
 * default
 * @param custom_compare_func Pointer to a custom compare function, or NULL to
 * use the default
 * @return A rsv_hash_set_t struct representing the created hash set
 */
static rsv_hash_set_t rsv_hash_set_create(
    unsigned int capacity, unsigned int element_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int));

/**
 * @brief Destroys a hash set, freeing all associated memory
 *
 * @param hash_set Pointer to the hash set to destroy
 */
static void rsv_hash_set_destroy(rsv_hash_set_t* hash_set);

/**
 * @brief Resizes a hash set to the new specified capacity
 *
 * @param hash_set Pointer to the hash set to resize
 * @param new_capacity The new capacity for the hash set
 */
static void rsv_hash_set_resize(rsv_hash_set_t* hash_set,
                                unsigned int new_capacity);

/**
 * @brief Checks if the hash set contains the specified data
 *
 * @param hash_set Pointer to the hash set
 * @param data Pointer to the data to check for
 * @return 1 if the data is in the hash set, 0 otherwise
 */
static int rsv_hash_set_contains(rsv_hash_set_t* hash_set, const void* data);

/**
 * @brief Adds an element to the hash set
 *
 * @param hash_set Pointer to the hash set
 * @param data Pointer to the data to add
 */
static void rsv_hash_set_push(rsv_hash_set_t* hash_set, const void* data);

/**
 * @brief Removes an element from the hash set
 *
 * @param hash_set Pointer to the hash set
 * @param data Pointer to the data to remove
 */
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
        (size_t)(array->capacity * RSV_DYNAMIC_ARRAY_GROWTH_AMOUNT + 1);
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
                                        unsigned int element_size) {
  const unsigned char* data_key = (const unsigned char*)data;
  unsigned int hash = 0;
  unsigned int i;

  for (i = 0; i < element_size; ++i) {
    hash = (hash * 31) + data_key[i];
  }

  return hash;
}

static int rsv_hash_table_compare(const void* data_a, const void* data_b,
                                  unsigned int element_size) {
  return memcmp(data_a, data_b, element_size) == 0;
}

static rsv_hash_table_t rsv_hash_table_create(
    unsigned int capacity, unsigned int key_size, unsigned int value_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int)) {
  rsv_hash_table_t hash_table;

  hash_table.data = (rsv_hash_table_entry_t**)calloc(
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
    rsv_hash_table_entry_t* entry = hash_table->data[i];

    while (entry) {
      rsv_hash_table_entry_t* next = entry->next;
      free(entry->key);
      free(entry->value);
      free(entry);
      entry = next;
    }
  }

  free(hash_table->data);
  hash_table->data = NULL;
  hash_table->amount = 0;
  hash_table->capacity = 0;
}

static void rsv_hash_table_resize(rsv_hash_table_t* hash_table,
                                  unsigned int new_capacity) {
  unsigned int i;
  rsv_hash_table_entry_t** new_data = (rsv_hash_table_entry_t**)calloc(
      new_capacity, sizeof(rsv_hash_table_entry_t*));

  for (i = 0; i < hash_table->capacity; ++i) {
    rsv_hash_table_entry_t* entry = hash_table->data[i];
    while (entry) {
      rsv_hash_table_entry_t* next = entry->next;
      unsigned int new_index =
          hash_table->custom_hash_func(entry->key, hash_table->key_size) %
          new_capacity;
      entry->next = new_data[new_index];
      new_data[new_index] = entry;
      entry = next;
    }
  }

  free(hash_table->data);
  hash_table->data = new_data;
  hash_table->capacity = new_capacity;
}

static void* rsv_hash_table_get(rsv_hash_table_t* hash_table, const void* key) {
  unsigned int index = hash_table->custom_hash_func(key, hash_table->key_size) %
                       hash_table->capacity;
  rsv_hash_table_entry_t* entry = hash_table->data[index];

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
  entry = hash_table->data[index];

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
  new_entry->next = hash_table->data[index];
  hash_table->data[index] = new_entry;
  hash_table->amount++;
}

static void rsv_hash_table_pop(rsv_hash_table_t* hash_table, const void* key) {
  unsigned int index = hash_table->custom_hash_func(key, hash_table->key_size) %
                       hash_table->capacity;
  rsv_hash_table_entry_t* entry = hash_table->data[index];
  rsv_hash_table_entry_t* prev = NULL;

  while (entry) {
    if (hash_table->custom_compare_func(entry->key, key,
                                        hash_table->key_size)) {
      if (prev) {
        prev->next = entry->next;
      } else {
        hash_table->data[index] = entry->next;
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
                                      unsigned int element_size) {
  const unsigned char* data_key = (const unsigned char*)data;
  unsigned int hash = 0;
  unsigned int i;

  for (i = 0; i < element_size; ++i) {
    hash = (hash * 31) + data_key[i];
  }

  return hash;
}

static int rsv_hash_set_compare(const void* data_a, const void* data_b,
                                unsigned int element_size) {
  return memcmp(data_a, data_b, element_size) == 0;
}

static rsv_hash_set_t rsv_hash_set_create(
    unsigned int capacity, unsigned int element_size,
    unsigned int (*custom_hash_func)(const void*, unsigned int),
    int (*custom_compare_func)(const void*, const void*, unsigned int)) {
  rsv_hash_set_t hash_set;

  hash_set.data =
      (rsv_hash_set_entry_t**)calloc(capacity, sizeof(rsv_hash_set_entry_t*));
  hash_set.amount = 0;
  hash_set.capacity = capacity;
  hash_set.element_size = element_size;

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
    rsv_hash_set_entry_t* entry = hash_set->data[i];

    while (entry) {
      rsv_hash_set_entry_t* next = entry->next;
      free(entry->data);
      free(entry);
      entry = next;
    }
  }

  free(hash_set->data);
  hash_set->data = NULL;
  hash_set->amount = 0;
  hash_set->capacity = 0;
}

static void rsv_hash_set_resize(rsv_hash_set_t* hash_set,
                                unsigned int new_capacity) {
  unsigned int i;
  rsv_hash_set_entry_t** new_data = (rsv_hash_set_entry_t**)calloc(
      new_capacity, sizeof(rsv_hash_set_entry_t*));

  for (i = 0; i < hash_set->capacity; ++i) {
    rsv_hash_set_entry_t* entry = hash_set->data[i];
    while (entry) {
      rsv_hash_set_entry_t* next = entry->next;
      unsigned int new_index =
          hash_set->custom_hash_func(entry->data, hash_set->element_size) %
          new_capacity;
      entry->next = new_data[new_index];
      new_data[new_index] = entry;
      entry = next;
    }
  }

  free(hash_set->data);
  hash_set->data = new_data;
  hash_set->capacity = new_capacity;
}

static int rsv_hash_set_contains(rsv_hash_set_t* hash_set, const void* data) {
  unsigned int index =
      hash_set->custom_hash_func(data, hash_set->element_size) %
      hash_set->capacity;
  rsv_hash_set_entry_t* entry = hash_set->data[index];

  while (entry) {
    if (hash_set->custom_compare_func(entry->data, data,
                                      hash_set->element_size)) {
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

  index = hash_set->custom_hash_func(data, hash_set->element_size) %
          hash_set->capacity;
  entry = hash_set->data[index];

  while (entry) {
    if (hash_set->custom_compare_func(entry->data, data,
                                      hash_set->element_size)) {
      return;
    }
    entry = entry->next;
  }

  new_entry = (rsv_hash_set_entry_t*)malloc(sizeof(rsv_hash_set_entry_t));
  new_entry->data = malloc(hash_set->element_size);
  memcpy(new_entry->data, data, hash_set->element_size);
  new_entry->next = hash_set->data[index];
  hash_set->data[index] = new_entry;
  hash_set->amount++;
}

static void rsv_hash_set_pop(rsv_hash_set_t* hash_set, const void* data) {
  unsigned int index =
      hash_set->custom_hash_func(data, hash_set->element_size) %
      hash_set->capacity;
  rsv_hash_set_entry_t* entry = hash_set->data[index];
  rsv_hash_set_entry_t* prev = NULL;

  while (entry) {
    if (hash_set->custom_compare_func(entry->data, data,
                                      hash_set->element_size)) {
      if (prev) {
        prev->next = entry->next;
      } else {
        hash_set->data[index] = entry->next;
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
