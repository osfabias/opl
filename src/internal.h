#pragma once

#include <stdint.h> // for types

#include "opl/opl.h"

typedef struct _OplState {
  uint8_t initialized;
  uint8_t terminateRequsted;

  OplKeyboardState keyboardState;
  OplMouseState mouseState;
} _OplState;

uint8_t _oplPlatformInit(const OplInitInfo *pInitInfo, _OplState *pOplState);

void _oplPlatformTerminate();
