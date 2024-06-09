#pragma once

#include "opl/opl.h"

/*****************************************************
 * type forward declarations
 *****************************************************/
typedef struct _OplPlatform _OplPlatform;
typedef struct _OplState    _OplState;

/*****************************************************
 * type definitions
 *****************************************************/
typedef int _OplBool;

typedef struct _OplPlatform {
  int platformId;
  OplResult (*init)(const OplInitInfo*);
  void (*terminate)();
  void (*pollEvents)();
} _OplPlatform;

struct _OplState {
  _OplBool initialized;
  _OplPlatform platform;
  struct {
    OplTerminateRequestFun terminateRequest;
  } callbacks;
};

/* global library state shared between compilation units of OPL */
extern _OplState _opl;
