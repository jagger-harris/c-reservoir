/*
  rsv_threads.h
  Contains wrappers for threads api

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_THREADS_H
#define RSV_THREADS_H

/******** Unix ********/

#include <pthread.h>

typedef pthread_t rsv_thread_t;
typedef pthread_mutex_t rsv_mutex_t;

/**
 * @brief Creates a new thread
 *
 * This function creates a new thread that executes the `start_routine` function
 * with the provided `arg` argument
 *
 * @param thread Pointer to a rsv_thread_t structure where the thread
 * information will be stored
 * @param start_routine Pointer to the function that will be executed by the new
 * thread
 * @param arg Argument to be passed to the `start_routine` function
 * @return 0 on success, or an error code on failure
 */
int rsv_thread_create(rsv_thread_t* thread, void* (*start_routine)(void*),
                      void* arg);

/**
 * @brief Waits for a thread to terminate
 *
 * This function waits for the thread specified by `thread` to terminate and
 * stores the thread's exit status in `retval`
 *
 * @param thread The thread to wait for
 * @param retval Pointer to a variable that will receive the thread's exit
 * status.
 * @return 0 on success, or an error code on failur
 */
int rsv_thread_join(rsv_thread_t thread, void** retval);

/**
 * @brief Creates a mutex
 *
 * This function initializes a mutex object, allowing threads to synchronize
 * access to shared resources
 *
 * @param mutex Pointer to a rsv_mutex_t structure where the mutex information
 * will be stored
 * @return 0 on success, or an error code on failure
 */
int rsv_mutex_create(rsv_mutex_t* mutex);

/**
 * @brief Destroys a mutex
 *
 * This function destroys a mutex object, freeing any resources associated with
 * it
 *
 * @param mutex Pointer to the mutex to destroy
 * @return 0 on success, or an error code on failure
 */
int rsv_mutex_destroy(rsv_mutex_t* mutex);

/**
 * @brief Locks a mutex
 *
 * This function locks the specified mutex, blocking if the mutex is already
 * locked by another thread
 *
 * @param mutex Pointer to the mutex to lock
 * @return 0 on success, or an error code on failure
 */
int rsv_mutex_lock(rsv_mutex_t* mutex);

/**
 * @brief Unlocks a mutex
 *
 * This function unlocks the specified mutex, allowing other threads to acquire
 * it
 *
 * @param mutex Pointer to the mutex to unlock
 * @return 0 on success, or an error code on failure
 */
int rsv_mutex_unlock(rsv_mutex_t* mutex);

/**************** Implementations ****************/

int rsv_thread_create(rsv_thread_t* thread, void* (*start_routine)(void*),
                      void* arg) {
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
