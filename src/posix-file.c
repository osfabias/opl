#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "opl/opl.h"

struct OplFile{
  FILE *file;
};

static const char* modeString[] =  {
  "rt",  // OPL_FILE_MODE_READ,
  "wt",  // OPL_FILE_MODE_WRITE,
  "at",  // OPL_FILE_MODE_APPEND,
  "r+t", // OPL_FILE_MODE_READ_AND_WRITE,
  "w+t", // OPL_FILE_MODE_WRITE_AND_READ,
  "rb",  // OPL_FILE_MODE_BINARY_READ,
  "wb",  // OPL_FILE_MODE_BINARY_WRITE,
  "ab",  // OPL_FILE_MODE_BINARY_APPEND,
  "r+b", // OPL_FILE_MODE_BINARY_READ_AND_WRITE,
  "w+b", // OPL_FILE_MODE_BINARY_WRITE_AND_READ,
};

OplFile* oplFileOpen(const char *path, OplFileMode mode) {
  OplFile *file = oplAlloc(sizeof(OplFile));
  file->file = fopen(path, modeString[mode]);

  if (file->file) { return file; }

  oplFree(file);
  return 0;
}

uint8_t oplFileClose(OplFile *file) {
  uint8_t res = fclose(file->file) == 0;
  oplFree(file);
  return res;
}

uint8_t oplFileIsEof(OplFile *file) {
  return feof(file->file);
}

uint8_t oplFileIsExist(const char *path) {
  return access(path, F_OK) == 0;
}

uint64_t oplFileSize(OplFile *file) {
  const uint32_t cursorPos = ftell(file->file);

  fseek(file->file, 0, SEEK_END);
  const uint32_t size = ftell(file->file);
  fseek(file->file, cursorPos, SEEK_SET);

  return size;
}

uint8_t oplFileCursorSetPosition(OplFile *file, uint32_t position) {
  return fseek(file->file, position, SEEK_SET) == 0;
}

uint32_t oplFileCursorGetPosition(OplFile *file) {
  return ftell(file->file);
}

uint8_t oplFileCursorJumpEnd(OplFile *file) {
  return fseek(file->file, 0, SEEK_END);
}

uint8_t oplFileRead(OplFile *file, uint64_t size,
                    char *out) {
  return fread(out, size, 1, file->file) == 0;
}

uint8_t oplFileReadChar(OplFile *file, char *out) {
  int outInt = getc(file->file);
  *out = outInt;
  return outInt == EOF;
}

uint8_t oplFileReadLine(OplFile *file, uint64_t bufferLimit,
                        char *out) {
  return fgets(out, bufferLimit, file->file) != 0;
}

uint8_t oplFileReadFormatted(OplFile *file, const char *format, ...) {
  va_list valist;
  va_start(valist, format);
  uint8_t res = vfscanf(file->file, format, valist) >= 0;
  va_end(valist);

  return res;
}

uint8_t oplFileWrite(OplFile *file, uint64_t size,
                     void *in) {
  return fwrite(in, size, 1, file->file) == 1;

}

uint8_t oplFileWriteChar(OplFile *file, char *in) {
  return fputc(*in, file->file) == 0;
}

uint8_t oplFileWriteLine(OplFile *file, char *in) {
  return fputs(in, file->file) == 0;
}

uint8_t oplFileWriteFormatted(OplFile *file, const char *format, ...) {
  va_list valist;
  va_start(valist, format);
  uint8_t res = vfprintf(file->file, format, valist) >= 0;
  va_end(valist);

  return res;
}
