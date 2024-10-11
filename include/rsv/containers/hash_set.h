/*
  hash_set.h
  Implementation of a hash set

  Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/
*/

#ifndef RSV_HASH_SET_H
#define RSV_HASH_SET_H

#include <stdlib.h>
#include <string.h>

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
 * @brief Generates a hash for the given data.
 *
 * @param data Pointer to the data to hash.
 * @param element_size Size of the data in memory.
 * @return The generated hash value.
 */
static inline unsigned int rsv_hash_set_hash(const void* data,
                                             unsigned int element_size) {
  const unsigned char* data_key = (const unsigned char*)data;
  unsigned int hash = 0;
  unsigned int i;

  for (i = 0; i < element_size; ++i) {
    hash = (hash * 31) + data_key[i];
  }

  return hash;
}

/**
 * @brief Compares two pieces of data.
 *
 * @param data_a Pointer to the first data.
 * @param data_b Pointer to the second data.
 * @param element_size Size of the data in memory.
 * @return 1 if the data are equal, 0 otherwise.
 */
static inline int rsv_hash_set_compare(const void* data_a, const void* data_b,
                                       unsigned int element_size) {
  return memcmp(data_a, data_b, element_size) == 0;
}

/**
 * @brief Creates a hash set.
 *
 * @param capacity Initial capacity of the hash set.
 * @param element_size Size of each element in the hash set.
 * @param custom_hash_func Pointer to a custom hash function, or NULL to use the
 * default.
 * @param custom_compare_func Pointer to a custom compare function, or NULL to
 * use the default.
 * @return A rsv_hash_set_t struct representing the created hash set.
 */
static inline rsv_hash_set_t rsv_hash_set_create(
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

/**
 * @brief Destroys a hash set, freeing all associated memory.
 *
 * @param hash_set Pointer to the hash set to destroy.
 */
static inline void rsv_hash_set_destroy(rsv_hash_set_t* hash_set) {
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

/**
 * @brief Resizes a hash set to the new specified capacity.
 *
 * @param hash_set Pointer to the hash set to resize.
 * @param new_capacity The new capacity for the hash set.
 */
static inline void rsv_hash_set_resize(rsv_hash_set_t* hash_set,
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

/**
 * @brief Checks if the hash set contains the specified data.
 *
 * @param hash_set Pointer to the hash set.
 * @param data Pointer to the data to check for.
 * @return 1 if the data is in the hash set, 0 otherwise.
 */
static inline int rsv_hash_set_contains(rsv_hash_set_t* hash_set,
                                        const void* data) {
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

/**
 * @brief Adds an element to the hash set.
 *
 * @param hash_set Pointer to the hash set.
 * @param data Pointer to the data to add.
 */
static inline void rsv_hash_set_push(rsv_hash_set_t* hash_set,
                                     const void* data) {
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

/**
 * @brief Removes an element from the hash set.
 *
 * @param hash_set Pointer to the hash set.
 * @param data Pointer to the data to remove.
 */
static inline void rsv_hash_set_pop(rsv_hash_set_t* hash_set,
                                    const void* data) {
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

#endif /* RSV_HASH_SET_H */
