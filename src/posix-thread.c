#include <unistd.h>

#include "opl/opl.h"

void oplSleep(uint64_t ms) {
  if (ms >= 1000) { sleep(ms / 1000); }
  usleep((ms % 1000) * 1000);
}

