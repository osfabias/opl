#include <string.h>

#include "opl/opl.h"
#include "internal.h"
#include "platform.h"

/* this variable contains library mutable state (see internal.h) */
_OplState _opl = {
  .initialized = OPL_FALSE,
};

OplResult oplInit(const OplInitInfo *pInitInfo) {
  if (_opl.initialized)
    return OPL_SUCCESS;

  memset(&_opl, 0, sizeof(_opl));

  OplResult result = _oplSelectPlatform(pInitInfo->desiredPlatform,
                                        &_opl.platform);
  if (result != OPL_SUCCESS)
    return result;

  _opl.platform.init(pInitInfo);

  return OPL_SUCCESS;
}

void oplTerminate() {
  if (!_opl.initialized)
    return;

  _opl.platform.terminate();
  _opl.initialized = OPL_FALSE;

  memset(&_opl, 0, sizeof(_opl));
}

void oplPollEvents() {
  _opl.platform.pollEvents();
}

void oplSetTerminateRequestCallback(OplTerminateRequestFun fun) {
  _opl.callbacks.terminateRequest = fun;
}
