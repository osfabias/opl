#pragma once

#include "internal.h"
#include "opl/opl.h"

typedef struct _OplPlatform {
  int platformId;
  OplResult (*init)(const OplInitInfo*);
  void (*terminate)();
  void (*pollEvents)();
} _OplPlatform;

OplResult _oplSelectPlatform(OplPlatformID desiredID, _OplPlatform *pPlatform);
