#include "opl/opl.h"

int main() {
  if (!oplInit()) { return 1; }

  char paths[1024][1024] = { 0 };
  uint32_t pathCount = oplDirListRecurse(".", 1024, paths);

  for (uint32_t i = 0; i < pathCount; ++i) {
    oplConsoleWrite("%s\n", paths[i]);
  }

  oplTerminate();
}
