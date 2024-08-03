#include "opl/opl.h"

int main() {
  if (!oplInit()) { return 1; }

  oplConsoleWrite("Type a message: ");

  char message[1024];
  oplConsoleRead(message, 1024);

  oplConsoleSetTextStyle(OPL_TEXT_STYLE_BOLD    |
                         OPL_TEXT_STYLE_ITALIC  |
                         OPL_TEXT_STYLE_UNDERLINE);
  oplConsoleSetColor(OPL_FG_COLOR_WHITE, OPL_BG_COLOR_RED);
  oplConsoleWrite("%s", message);

  oplTerminate();
}
