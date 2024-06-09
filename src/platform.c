#include <stdio.h>

#include "opl/opl.h"
#include "platform.h"
#include "platform_cocoa.h"

static const struct {
  OplPlatformID id;
  void (*connect)(_OplPlatform*);
} _supportedPlatforms[] = {
  /* add _oplConnectXXX funcs here */
};

OplResult _oplSelectPlatform(OplPlatformID desiredID, _OplPlatform *pPlatform) {
  if (desiredID != OPL_PLATFORM_ID_ANY &&
      desiredID != OPL_PLATFORM_ID_COCOA &&
      desiredID != OPL_PLATFORM_ID_WIN32) {
    return OPL_INVALID_VALUE;
  }

  int platformsCount = sizeof(_supportedPlatforms) /
                       sizeof(_supportedPlatforms[0]);
  if (platformsCount == 0)
    return OPL_PLATFORM_UNAVAILABLE;

  if (desiredID == OPL_PLATFORM_ID_ANY) {
    _supportedPlatforms[0].connect(pPlatform);
    return OPL_SUCCESS;
  }

  for(int i = 0; i < platformsCount; ++i) {
    if (_supportedPlatforms[i].id == desiredID) {
      _supportedPlatforms[i].connect(pPlatform);
      return OPL_SUCCESS;
    }
  }

  return OPL_PLATFORM_UNAVAILABLE;
}
