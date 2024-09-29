#include <opl.h>
#include <stdio.h>
#include <unistd.h>


int main() {
  if (!opl_init()) { return 1; }

  opl_alert("Welcome!", "Thanks for using opl!");

  opl_window_t window = opl_window_open(640, 360, "opl window");
  if (!window) { return 1; }

  
  while (!opl_window_should_close(window)) {
    opl_update();
    printf("%d \n", opl_is_fullscreen(window));
    opl_set_fullscreen(window,1);
    opl_update();
    usleep(1000*1000*3);
    opl_set_fullscreen(window, 0);
    opl_update();
    usleep(1000*1000*3);
  }
  
  opl_window_close(window);

  opl_quit();

  return 0;
}

