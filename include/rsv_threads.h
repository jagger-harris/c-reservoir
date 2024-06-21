#ifndef RSV_THREADS_H
#define RSV_THREADS_H

/******** Unix ********/

#include <pthread.h>

typedef pthread_t rsv_thread_t;
typedef pthread_mutex_t rsv_mutex_t;

int rsv_thread_create(rsv_thread_t* thread, void*  (*start_routine)(void*), void* arg);
int rsv_thread_join(rsv_thread_t thread, void** retval);

int rsv_mutex_create(rsv_mutex_t* mutex);
int rsv_mutex_destroy(rsv_mutex_t* mutex);
int rsv_mutex_lock(rsv_mutex_t* mutex);
int rsv_mutex_unlock(rsv_mutex_t* mutex);

int rsv_thread_create(rsv_thread_t* thread, void*  (*start_routine)(void*), void* arg) {
  return pthread_create(thread, NULL, start_routine, arg);
}

int rsv_thread_join(rsv_thread_t thread, void** retval) {
  return pthread_join(thread, retval);
}

int rsv_mutex_create(rsv_mutex_t* mutex) {
  return pthread_mutex_init(mutex, NULL);
}

int rsv_mutex_destroy(rsv_mutex_t* mutex) {
  return pthread_mutex_destroy(mutex);
}

int rsv_mutex_lock(rsv_mutex_t* mutex) {
  return pthread_mutex_lock(mutex);
}

int rsv_mutex_unlock(rsv_mutex_t* mutex) {
  return pthread_mutex_unlock(mutex);
}

#endif /* RSV_THREADS_H */
