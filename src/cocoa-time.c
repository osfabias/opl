#include <mach/mach_time.h>

#include "opl/opl.h"

uint64_t oplGetTime() {
  mach_timebase_info_data_t clockTimebase;
  mach_timebase_info(&clockTimebase);

  uint64_t machAbsolute = mach_absolute_time();

  uint64_t nanos = (float)(machAbsolute * (uint64_t)clockTimebase.numer) / (float)clockTimebase.denom;
  return nanos * 0.000001f; // to milliseconds
}
