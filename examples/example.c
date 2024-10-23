#include <opl.h>

int main() {
  if (!opl_init()) { return 1; }

  opl_alert("Welcome!", "Thanks for using opl!");

  opl_window window = opl_open(
    640, 360, "opl window", OPL_CENTER, OPL_CENTER,
    OPL_WINDOW_HINT_TITLED_BIT | OPL_WINDOW_HINT_CLOSABLE_BIT);
  if (!window) { return 1; }

  while (!opl_should_close(window))
    opl_update();

  opl_close(window);

  opl_quit();

  return 0;
}

