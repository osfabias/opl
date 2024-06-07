#include "opl/opl.h"

static int s_running = 1;

void onTerminateRequest() {
  s_running = 0;
}

int main() {
  /* configure opl initialization */
  OplInitInfo initInfo;
  initInfo.pApplicationName = "OPL application";
  initInfo.resolutionX = 1280;
  initInfo.resolutionY = 720;

  /* init library */
  if (oplInit(&initInfo) != OPL_SUCCESS)
    return -1;

  /* set terminate request callback */
  oplSetTerminateRequestCallback(&onTerminateRequest);

  /* update opl state untill terminate callback is called */
  while (s_running) {
    oplPollEvents();
  }

  /* terminate library */
  oplTerminate();
}

