#include <stdio.h>

#include "opl/opl.h"

int main() {
  if (!oplInit()) { return 1; }

  const OplAlertButton button1 = {
    .title = "fuck this!",
  };

  const OplAlertButton button2 = {
    .title = "ok :3",
  };

  const OplAlertButton buttons[] = {
    button1,
    button2,
  };

  const OplAlertShowInfo info = {
    .style       = OPL_ALERT_STYLE_INFO,
    .title       = "OPL info alert",
    .message     = "some info",
    .buttonCount = 2,
    .buttons     = buttons,
  };

  uint32_t responce = oplAlertShow(&info);
  printf("%s\n", buttons[responce].title);

  oplTerminate();
}
