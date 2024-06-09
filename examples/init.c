#include <stdio.h>

#include "opl/opl.h"

static int running = 1;

void onTerminateRequest() {
  puts("terminate requested");
  running = 0;
}

int main() {
  puts("configuring init info");
  /* configure opl initialization */
  OplInitInfo initInfo;
  initInfo.pApplicationName = "OPL application";
  initInfo.width  = 1280;
  initInfo.height = 720;
  initInfo.desiredPlatform = OPL_PLATFORM_ID_ANY;

  puts("initializing opl");
  /* init library */
  OplResult result = oplInit(&initInfo);
  if (result != OPL_SUCCESS)
    return result;

  puts("terminate request callback set");
  /* set terminate request callback */
  oplSetTerminateRequestCallback(&onTerminateRequest);

  puts("entering main cycle");
  /* update opl state untill terminate callback is called */
  while (running) {
    oplPollEvents();
  }

  puts("terminating library");
  /* terminate library */
  oplTerminate();
}

