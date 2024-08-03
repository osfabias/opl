#include "opl/opl.h"

void* routine(void *arg) {
  *((int*)arg) += 11;
  oplConsoleWrite("thread finished, expected output: %d\n", *(int*)arg);

  return 0;
}

int main() {
  int data = 1;

  OplThread *thread = oplThreadCreate(&routine, &data);
  if (!thread) { return 1; }
  if (!oplThreadWait(thread)) { return 1; }

  oplConsoleWrite("output: %d\n", data);

  return 0;
}
