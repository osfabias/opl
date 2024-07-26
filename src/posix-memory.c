#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "opl/opl.h"

void* oplAlloc(uint64_t size) {
  return malloc(size);
}

void* oplRealloc(void *pBlock, uint64_t size) {
  return realloc(pBlock, size);
}

void oplFree(void *pBlock) {
  free(pBlock);
}

void oplMemCpy(void *pDstBlock, const void *pSrcBlock, uint64_t size) {
  memcpy(pDstBlock, pSrcBlock, size);
}

void oplMemSet(void *pBlock, int32_t value, uint64_t size) {
  memset(pBlock, value, size);
}

void oplMemMove(void *pDstBlock, const void *pSrcBlock, uint64_t size) {
  memmove(pDstBlock, pSrcBlock, size);
}

int32_t oplMemCmp(const void *pBlock1, const void *pBlock2, uint64_t size) {
  return memcmp(pBlock1, pBlock2, size);
}

