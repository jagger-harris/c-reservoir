/*
  rsv_hash_table.h
  Reservoir implementation of a hash table

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_HASH_TABLE_H
#define RSV_HASH_TABLE_H

#include <stdlib.h>
#include <string.h>

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
 * @brief Generates a hash for the given data.
 *
 * @param data Pointer to the data to hash.
 * @param element_size Size of the data in memory.
 * @return The generated hash value.
 */
static inline unsigned int rsv_hash_table_hash(const void* data,
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
 * @brief Compares two pieces of hash table data.
 *
 * @param data_a Pointer to the first data.
 * @param data_b Pointer to the second data.
 * @param element_size Size of the data in memory.
 * @return 1 if the data are equal, 0 otherwise.
 */
static inline int rsv_hash_table_compare(const void* data_a, const void* data_b,
                                         unsigned int element_size) {
  return memcmp(data_a, data_b, element_size) == 0;
}

/**
 * @brief Creates a hash table.
 *
 * @param capacity Initial capacity of the hash table.
 * @param key_size Size of each key in memory.
 * @param value_size Size of each value in memory.
 * @param custom_hash_func Pointer to a custom hash function, or NULL to use the
 * default.
 * @param custom_compare_func Pointer to a custom compare function, or NULL to
 * use the default.
 * @return A rsv_hash_table_t struct representing the created hash table.
 */
static inline rsv_hash_table_t rsv_hash_table_create(
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

/**
 * @brief Destroys a hash table, freeing all associated memory.
 *
 * @param hash_table Pointer to the hash table to destroy.
 */
static inline void rsv_hash_table_destroy(rsv_hash_table_t* hash_table) {
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

/**
 * @brief Resizes a hash table to the new specified capacity.
 *
 * @param hash_table Pointer to the hash table to resize.
 * @param new_capacity The new capacity for the hash table.
 */
static inline void rsv_hash_table_resize(rsv_hash_table_t* hash_table,
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

/**
 * @brief Retrieves the value associated with the specified key in the hash
 * table.
 *
 * @param hash_table Pointer to the hash table.
 * @param key Pointer to the key.
 * @return Pointer to the value associated with the key, or NULL if the key is
 * not found.
 */
static inline void* rsv_hash_table_get(rsv_hash_table_t* hash_table,
                                       const void* key) {
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

/**
 * @brief Adds a key-value pair to the hash table.
 *
 * @param hash_table Pointer to the hash table.
 * @param key Pointer to the key.
 * @param value Pointer to the value.
 */
static inline void rsv_hash_table_push(rsv_hash_table_t* hash_table,
                                       const void* key, const void* value) {
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

/**
 * @brief Removes a key-value pair from the hash table.
 *
 * @param hash_table Pointer to the hash table.
 * @param key Pointer to the key of the pair to remove.
 */
static inline void rsv_hash_table_pop(rsv_hash_table_t* hash_table,
                                      const void* key) {
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

#endif /* RSV_HASH_TABLE_H */
