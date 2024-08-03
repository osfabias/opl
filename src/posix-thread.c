#include <unistd.h>
#include <pthread.h>

#include "opl/opl.h"

struct OplThread { pthread_t thread; };
struct OplMutex  { pthread_mutex_t mutex; };
struct OplFence  { pthread_cond_t cond; };

OplThread* oplThreadCreate(OplThreadFunc func, void *data) {
  OplThread *thread = oplAlloc(sizeof(OplThread));
  if (pthread_create(&thread->thread, 0, func, data) != 0) {
    oplFree(thread);
    return 0;
  }
  return thread;
}

void oplThreadDestroy (OplThread *thread) {
  pthread_kill(thread->thread, 0);
  oplFree(thread);
}

uint8_t oplThreadJoin(OplThread *thread, void *out) {
  return pthread_join(thread->thread, out) == 0;
}

uint8_t oplThreadDetach(OplThread *thread) {
  return pthread_detach(thread->thread) == 0;
}

void oplThreadExit(void *data) {
  pthread_exit(data);
}

OplThread* oplThreadSelf() {
  OplThread *thread = oplAlloc(sizeof(OplThread));
  thread->thread = pthread_self();
  return thread;
}

uint8_t oplThreadSleep(uint64_t milliseconds) {
  // microseconds to milliseconds
  return usleep(milliseconds * 1000) == 0; 
}

OplMutex* oplMutexCreate() {
  OplMutex *mutex = oplAlloc(sizeof(OplMutex));
  if (pthread_mutex_init(&mutex->mutex, 0) == 0) {
    return mutex;
  }
  oplFree(mutex);
  return 0;
}

void oplMutextDestroy(OplMutex *mutex) {
  pthread_mutex_destroy(&mutex->mutex);
  oplFree(mutex);
}

void oplMutexLock(OplMutex *mutex) {
  pthread_mutex_lock(&mutex->mutex);
}

uint8_t oplMutexTryLock(OplMutex *mutex) {
  return pthread_mutex_trylock(&mutex->mutex) == 0;
}

void oplMutexUnlock(OplMutex *mutex) {
  pthread_mutex_unlock(&mutex->mutex);
}

OplFence* oplFenceCreate() {
  OplFence *fence = oplAlloc(sizeof(OplFence));
  if (pthread_cond_init(&fence->cond, 0) == 0) {
    return fence;
  }
  oplFree(fence);
  return 0;
}

/**
 * @brief Destroys an OPL fence.
 */
void oplFenceDestroy(OplFence *fence) {
  pthread_cond_destroy(&fence->cond);
  oplFree(fence);
}

void oplFenceSignal(OplFence *fence) {
  pthread_cond_signal(&fence->cond);
}

void oplFenceBroadcast(OplFence *fence) {
  pthread_cond_broadcast(&fence->cond);
}

void oplFenceWait(OplFence *fence, OplMutex *mutex) {
  pthread_cond_wait(&fence->cond, &mutex->mutex);
}

