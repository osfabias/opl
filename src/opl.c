#include "opl/opl.h"
#include "internal.h"

_OplState s_oplState = {
  .initialized = OPL_FALSE,
  .terminateRequsted = OPL_FALSE,
};

uint8_t oplInit(const OplInitInfo *pInitInfo) {
  if (s_oplState.initialized) { return OPL_TRUE; }

  s_oplState.initialized = _oplPlatformInit(pInitInfo, &s_oplState);
  return s_oplState.initialized;
}

void oplTerminate() {
  if (!s_oplState.initialized) { return; }

  _oplPlatformTerminate();

  s_oplState.initialized = OPL_FALSE;
}

uint8_t oplShouldTerminate() {
  return s_oplState.terminateRequsted;
}

const OplKeyboardState* oplKeyboardGetState() {
  return &s_oplState.keyboardState;
}

const OplMouseState* oplMouseGetState() {
  return &s_oplState.mouseState;
}
