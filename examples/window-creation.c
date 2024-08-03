#include "opl/opl.h"

const OplWindowCreateInfo windowCreateInfo = {
  .styleFlags  = OPL_WINDOW_STYLE_TITLED        |
                 OPL_WINDOW_STYLE_CLOSABLE      |
                 OPL_WINDOW_STYLE_RESIZABLE     |
                 OPL_WINDOW_STYLE_MINIATURIZABLE,
  .title       = "OPL window",
  .x           = 0,
  .y           = 0,
  .width       = 300,
  .height      = 300,
};

int main() {
  if (!oplInit()) { return 1; }

  OplWindow *window = oplWindowCreate(&windowCreateInfo);
  if (!window) { return 1; }

  while (!oplWindowShouldClose(window)) {
    oplPumpMessages();
  }

  oplWindowDestroy(window);

  oplTerminate();

  return 0;
}
