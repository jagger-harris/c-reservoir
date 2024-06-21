#include "../include/rsvr_threads.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct shared_data_t {
  int counter;
  rsvr_mutex_t mutex;
} shared_data_t;

void* increment_counter(void* arg) {
  shared_data_t* data = (shared_data_t*)arg;
  int i;

  for (i = 0; i < 1000; i++) {
    rsvr_mutex_lock(&data->mutex);
    data->counter++;
    rsvr_mutex_unlock(&data->mutex);
  }

  return NULL;
}

void test_threading(void) {
  rsvr_thread_t thread1;
  rsvr_thread_t thread2;
  shared_data_t data;

  data.counter = 0;

  rsvr_mutex_create(&data.mutex);

  /* Test: Create threads */
  assert(rsvr_thread_create(&thread1, increment_counter, &data) == 0);
  assert(rsvr_thread_create(&thread2, increment_counter, &data) == 0);

  /* Test: join threads */
  assert(rsvr_thread_join(thread1, NULL) == 0);
  assert(rsvr_thread_join(thread2, NULL) == 0);

  /* Test: Counter value */
  assert(data.counter == 2000);

  rsvr_mutex_destroy(&data.mutex);

  printf("All threading tests passed!\n");
}

int main(void) {
  test_threading();
  exit(EXIT_SUCCESS);
}
