#include "opl/opl.h"

const OplInitInfo info = {
  .applicationName = "OPL example app",
  .surfaceWidth     = 640,
  .surfaceHeight    = 360,
};

int main() {
  oplInit(&info);

  while (!oplShouldTerminate()) {
    oplPumpMessages();
  }

  oplTerminate();

  return 0;
}
