#include "opl/opl.h"

static int running = 1;

void onTerminateRequest() {
  running = 0;
}

int main() {
  /* configure opl initialization */
  OplInitInfo initInfo;
  initInfo.pApplicationName = "OPL application";
  initInfo.width  = 1280;
  initInfo.height = 720;
  initInfo.desiredPlatform = OPL_PLATFORM_ID_ANY;

  /* init library */
  if (oplInit(&initInfo) != OPL_SUCCESS)
    return -1;

  /* set terminate request callback */
  oplSetTerminateRequestCallback(&onTerminateRequest);

  /* update opl state untill terminate callback is called */
  while (running) {
    oplPollEvents();
  }

  /* terminate library */
  oplTerminate();
}

