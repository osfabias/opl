#include <stdio.h>
#include <stdarg.h>

#include "opl/opl.h"

void oplConsoleSetTextStyle(OplTextStyleFlag textStyleFlag) {
  uint8_t charInd = 0;
  char style[20];

  // 5 - numebr of text style flags
  for (uint32_t i = 0; i < 5; ++i) {
    if (textStyleFlag & (1 << i)) {
      style[charInd++] = 48 + i; // see ASCII table
      style[charInd++] = ';';
    }
  }

  style[charInd - 1] = '\0';

  printf("\033[%sm", style);
}

void oplConsoleSetColor(OplFgColor fgColor, OplBgColor bgColor) {
  printf("\033[%d;%dm", fgColor, bgColor);
}

void oplConsoleWrite(const char *message, ...) {
  va_list valist;
  va_start(valist, message);
  vprintf(message, valist);
  va_end(valist);
}

void oplConsoleRead(char *string, uint64_t bufferLimit) {
  fgets(string, bufferLimit, stdin);
}

void oplConsoleReadFormatted(const char *format, ...) {
  va_list valist;
  va_start(valist, format);
  vscanf(format, valist);
  va_end(valist);
}


