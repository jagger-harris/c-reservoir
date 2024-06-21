#ifndef RSVR_THREADS_H
#define RSVR_THREADS_H

/******** Unix ********/

#include <pthread.h>

typedef pthread_t rsvr_thread_t;
typedef pthread_mutex_t rsvr_mutex_t;

int rsvr_thread_create(rsvr_thread_t* thread, void*  (*start_routine)(void*), void* arg);
int rsvr_thread_join(rsvr_thread_t thread, void** retval);

int rsvr_mutex_create(rsvr_mutex_t* mutex);
int rsvr_mutex_destroy(rsvr_mutex_t* mutex);
int rsvr_mutex_lock(rsvr_mutex_t* mutex);
int rsvr_mutex_unlock(rsvr_mutex_t* mutex);

int rsvr_thread_create(rsvr_thread_t* thread, void*  (*start_routine)(void*), void* arg) {
  return pthread_create(thread, NULL, start_routine, arg);
}

int rsvr_thread_join(rsvr_thread_t thread, void** retval) {
  return pthread_join(thread, retval);
}

int rsvr_mutex_create(rsvr_mutex_t* mutex) {
  return pthread_mutex_init(mutex, NULL);
}

int rsvr_mutex_destroy(rsvr_mutex_t* mutex) {
  return pthread_mutex_destroy(mutex);
}

int rsvr_mutex_lock(rsvr_mutex_t* mutex) {
  return pthread_mutex_lock(mutex);
}

int rsvr_mutex_unlock(rsvr_mutex_t* mutex) {
  return pthread_mutex_unlock(mutex);
}

#endif /* RSVR_THREADS_H */
