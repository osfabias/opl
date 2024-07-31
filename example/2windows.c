#include "opl/opl.h"
#include <stdio.h>

const OplWindowCreateInfo windowCreateInfo = {
  .styleFlags  = OPL_WINDOW_STYLE_TITLED |
                 OPL_WINDOW_STYLE_CLOSABLE,
  .title       = "OPL window",
  .x           = 0,
  .y           = 0,
  .width       = 300,
  .height      = 300,
};

const OplWindowCreateInfo windowCreateInfo2 = {
  .styleFlags  = OPL_WINDOW_STYLE_TITLED |
                 OPL_WINDOW_STYLE_RESIZABLE,
  .title       = "OPL unclosable window",
  .x           = 100,
  .y           = 100,
  .width       = 720,
  .height      = 144,
};

int main() {
  if (!oplInit()) { return 1; }

  OplWindow window  = oplWindowCreate(&windowCreateInfo);
  OplWindow window2 = oplWindowCreate(&windowCreateInfo2);

  oplWindowSetTitle(window2, "Window2");
  const char* title = oplWindowGetTitle(window2);
  puts(title);

  while (!oplWindowShouldClose(window)) {
    oplPumpMessages();
  }

  oplWindowDestroy(window);
  oplWindowDestroy(window2);

  oplTerminate();

  return 0;
}
