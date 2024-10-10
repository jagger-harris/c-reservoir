/*
  rsv_threads_pthreads.h
  Contains wrappers for pthreads api

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#if defined(__unix__)

#ifndef RSV_THREADS_UNIX_H
#define RSV_THREADS_UNIX_H

#include <pthread.h>

typedef pthread_t rsv_thread_t;
typedef pthread_mutex_t rsv_mutex_t;

/**
 * @brief Creates a new thread.
 *
 * This function wraps `pthread_create` to create a new thread that starts
 * executing the specified start routine.
 *
 * @param thread A pointer to the thread object to be created.
 * @param start_routine A function pointer representing the function that will
 * be executed by the thread.
 * @param arg A pointer to the argument that will be passed to the start
 * routine.
 * @return 0 on success, or an error code on failure (as returned by
 * `pthread_create`).
 */
static inline int rsv_thread_create(rsv_thread_t* thread,
                                    void* (*start_routine)(void*), void* arg) {
  return pthread_create(thread, NULL, start_routine, arg);
}

/**
 * @brief Waits for the specified thread to terminate.
 *
 * This function wraps `pthread_join` to wait for a specific thread to finish
 * executing.
 *
 * @param thread The thread to wait for.
 * @param retval A pointer to a location where the return value of the thread
 * will be stored.
 * @return 0 on success, or an error code on failure (as returned by
 * `pthread_join`).
 */
static inline int rsv_thread_join(rsv_thread_t thread, void** retval) {
  return pthread_join(thread, retval);
}

/**
 * @brief Initializes a mutex.
 *
 * This function wraps `pthread_mutex_init` to create and initialize a mutex
 * object.
 *
 * @param mutex A pointer to the mutex object to be initialized.
 * @return 0 on success, or an error code on failure (as returned by
 * `pthread_mutex_init`).
 */
static inline int rsv_mutex_create(rsv_mutex_t* mutex) {
  return pthread_mutex_init(mutex, NULL);
}

/**
 * @brief Destroys a mutex.
 *
 * This function wraps `pthread_mutex_destroy` to destroy a previously
 * initialized mutex.
 *
 * @param mutex A pointer to the mutex object to be destroyed.
 * @return 0 on success, or an error code on failure (as returned by
 * `pthread_mutex_destroy`).
 */
static inline int rsv_mutex_destroy(rsv_mutex_t* mutex) {
  return pthread_mutex_destroy(mutex);
}

/**
 * @brief Locks a mutex.
 *
 * This function wraps `pthread_mutex_lock` to lock a mutex, preventing other
 * threads from accessing shared data.
 *
 * @param mutex A pointer to the mutex object to be locked.
 * @return 0 on success, or an error code on failure (as returned by
 * `pthread_mutex_lock`).
 */
static inline int rsv_mutex_lock(rsv_mutex_t* mutex) {
  return pthread_mutex_lock(mutex);
}

/**
 * @brief Unlocks a mutex.
 *
 * This function wraps `pthread_mutex_unlock` to unlock a mutex, allowing other
 * threads to acquire the lock and proceed.
 *
 * @param mutex A pointer to the mutex object to be unlocked.
 * @return 0 on success, or an error code on failure (as returned by
 * `pthread_mutex_unlock`).
 */
static inline int rsv_mutex_unlock(rsv_mutex_t* mutex) {
  return pthread_mutex_unlock(mutex);
}

#endif /* RSV_THREADS_UNIX_H */

#endif
