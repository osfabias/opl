#include "opl/opl.h"

int main() {
  oplInit();

  OplFile *file = oplFileOpen("file.txt", OPL_FILE_MODE_WRITE);
  if (!file) { return 1; }
  oplFileWrite(file, 12, "hello world!");
  oplFileClose(file);

  oplTerminate();
}
