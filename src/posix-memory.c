#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "opl/opl.h"

void* oplAlloc(uint64_t size) {
  return malloc(size);
}

void* oplRealloc(void *block, uint64_t size) {
  return realloc(block, size);
}

void oplFree(void *block) {
  free(block);
}

void oplMemCpy(void *dst, const void *src, uint64_t size) {
  memcpy(dst, src, size);
}

void oplMemSet(void *block, int32_t value, uint64_t size) {
  memset(block, value, size);
}

void oplMemMove(void *dst, const void *src, uint64_t size) {
  memmove(dst, src, size);
}

int32_t oplMemCmp(const void *block1, const void *block2, uint64_t size) {
  return memcmp(block1, block2, size);
}

