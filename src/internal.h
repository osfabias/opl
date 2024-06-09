#pragma once
/*****************************************************
 * type forward declarations
 *****************************************************/
#include "opl/opl.h"
typedef struct _OplState    _OplState;
typedef struct _OplPlatform _OplPlatform;

/*****************************************************
 * type definitions
 *****************************************************/
typedef int _OplBool;

struct _OplState {
  _OplBool initialized;
  _OplPlatform *platform;
  struct {
    OplTerminateRequestFun terminateRequest;
  } callbacks;
};

/* global library state shared between compilation units of OPL */
extern _OplState _opl;
