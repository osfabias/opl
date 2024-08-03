#include <stdio.h>
#include <stdarg.h>
#include <sys/dirent.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "opl/opl.h"

#define IS_DOT_DIR(dirname) \
  !(strcmp(dirname, ".") && strcmp(dirname, ".."))

struct OplFile { FILE *file; };

struct OplDir { DIR *dir; };

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

uint8_t oplIsFile(const char *path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

OplFile* oplFileOpen(const char *path, OplFileMode mode) {
  OplFile *file = oplAlloc(sizeof(OplFile));

  if (mode != OPL_FILE_MODE_TEMP) {
    file->file = fopen(path, modeString[mode]);
  }
  else { file->file = tmpfile(); }

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

uint8_t oplFileRename(const char *oldPath, const char *newPath) {
  return rename(oldPath, newPath) == 0;
}

uint8_t oplFileDelete(const char *path) {
  return remove(path) == 0;
}

uint8_t oplFileCopy(OplFile *dstFile, const OplFile *srcFile) {
  char buf[1024];
  uint8_t res = OPL_FALSE;
  while (1) {
    uint32_t bytesRead = fread(buf, 1, 1024, srcFile->file);
    if (bytesRead <= 0) { break; }
    if (fwrite(buf, 1, bytesRead, dstFile->file) <= 0) {  break; }
    res = OPL_TRUE;
  }
  
  return res;
}

uint8_t oplFileCopyByPath(const char *dstPath, const char *srcPath) {
  FILE* srcFile = fopen(srcPath, "r");
  if (!srcFile) { return OPL_FALSE; }

  FILE* dstFile = fopen(dstPath, "w");
  if (!dstFile) {
    fclose(srcFile);
    return OPL_TRUE;
  }

  OplFile dstOplFile = { dstFile };
  const OplFile srcOplFile = { srcFile };
  const uint8_t res = oplFileCopy(&dstOplFile, &srcOplFile);

  fclose(srcFile);
  fclose(dstFile);

  return res;
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

uint32_t oplFileRead(OplFile *file, uint32_t size,
                    uint32_t count, char *out) {
  return fread(out, size, count, file->file);
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

uint32_t oplFileWrite(OplFile *file, uint32_t size,
                      uint32_t count, void *in) {
  return fwrite(in, size, count, file->file);
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

uint8_t oplIsDir(const char *path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

OplDir* oplDirOpen(const char *path) {
  OplDir *dir = oplAlloc(sizeof(OplDir));
  dir->dir = opendir(path);
  if (!dir->dir) {
    oplFree(dir);
    return 0;
  }
  return dir;
}

uint8_t oplDirClose(OplDir *dir) {
  uint8_t res = closedir(dir->dir) == 0;
  oplFree(dir);
  return res;
}

uint8_t oplDirCreate(const char *path) {
  return mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0;
}

uint8_t oplDirDelete(const char *path) {
  return rmdir(path) == 0;
}

uint8_t oplDirRead(OplDir *dir, char *out) {
  struct dirent *de;
  de = readdir(dir->dir);
  if (!de) { return OPL_FALSE; }
  out = de->d_name;
  return OPL_TRUE;
}

void oplDirCursorSetPos(OplDir *dir, uint32_t pos) {
  seekdir(dir->dir, pos);
};

uint32_t oplDirCursorGetPos(OplDir *dir) {
  return telldir(dir->dir);
}

uint32_t oplDirList(const char *path, uint32_t bufferLimit,
                    const char* *paths) {
  DIR *dir = opendir(path);
  if (!dir) { return 0; }

  struct dirent *de;
  uint32_t entCount = 0;

  while (entCount < bufferLimit) {
    de = readdir(dir);
    if (!de) { break; }

    // skip '.' and '..' dirs
    if (de->d_type == DT_DIR && IS_DOT_DIR(de->d_name)) {
      continue;
    }

    paths[entCount++] = de->d_name;
  }

  return entCount;
}

uint32_t oplDirListRecurse(const char *path, uint32_t bufferLimit,
                           char paths[][1024]) {
  DIR *dir = opendir(path);
  if (!dir) { return 0; }

  struct dirent *de;
  uint32_t entCount = 0;

  while (entCount < bufferLimit) {
    de = readdir(dir);
    if (!de) { break; }

    if (de->d_type == DT_REG) {
      paths[entCount][0] = '\0';
      if (!IS_DOT_DIR(path)) {
        strcat(paths[entCount], path);
        strcat(paths[entCount], "/");
      }
      strcat(paths[entCount++], de->d_name);

      continue;
    }

    // skip '.' and '..' dirs
    if (IS_DOT_DIR(de->d_name)) { continue; }

    char fullPath[1024] = { 0 }; // the size as the MAXPATHLEN
    if (!IS_DOT_DIR(path)) {
      strcat(fullPath, path);
      strcat(fullPath, "/");
    }
    strcat(fullPath, de->d_name);
   
    entCount += oplDirListRecurse(fullPath, bufferLimit - entCount,
                                  paths + entCount);
  }

  return entCount;
}
