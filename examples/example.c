#include <opl.h>

int main() {
  if (!opl_init()) { return 1; }

  opl_alert("Welcome!", "Thanks for using opl!");

  opl_window_t window = opl_window_open(640, 360, "opl window");
  if (!window) { return 1; }

  while (!opl_window_should_close(window)) {
    opl_update();
  }

  opl_window_close(window);

  opl_quit();

  return 0;
}

