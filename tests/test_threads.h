#if defined(__unix__)

#ifndef TEST_THREADS_H
#define TEST_THREADS_H

#include "../include/threads/rsv_threads_pthreads.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct shared_data_t {
  int counter;
  rsv_mutex_t mutex;
} shared_data_t;

static inline void* increment_counter(void* arg) {
  shared_data_t* data = (shared_data_t*)arg;
  int i;

  for (i = 0; i < 1000; i++) {
    rsv_mutex_lock(&data->mutex);
    data->counter++;
    rsv_mutex_unlock(&data->mutex);
  }

  return NULL;
}

static inline int test_threads(void) {
  rsv_thread_t thread1;
  rsv_thread_t thread2;
  shared_data_t data;

  data.counter = 0;

  rsv_mutex_create(&data.mutex);

  /* Test: Create threads */
  TEST(rsv_thread_create(&thread1, increment_counter, &data) == 0);
  TEST(rsv_thread_create(&thread2, increment_counter, &data) == 0);

  /* Test: join threads */
  TEST(rsv_thread_join(thread1, NULL) == 0);
  TEST(rsv_thread_join(thread2, NULL) == 0);

  /* Test: Counter value */
  TEST(data.counter == 2000);
  rsv_mutex_destroy(&data.mutex);

  return 0;
}

#endif /* TEST_THREADS_H */

#endif
