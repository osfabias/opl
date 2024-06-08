#pragma once

#include "internal.h"
#include "opl/opl.h"

struct _OplPlatform {
  int platformId;
  OplResult (*init)(const OplInitInfo*);
  void (*terminate)();
  void (*pollEvents)();
};

OplResult _oplSelectPlatform(OplPlatformID desiredID,
                             const _OplPlatform *pPlatform);
