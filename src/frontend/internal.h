#pragma once
/*****************************************************
 * type forward declarations
 *****************************************************/
typedef struct _OplState    _OplState;
typedef struct _OplPlatform _OplPlatform;

/*****************************************************
 * type definitions
 *****************************************************/
typedef int _OplBool;

struct _OplState {
  _OplBool initialized;
  _OplPlatform *platform;
};

/* global library state shared between compilation units of OPL */
extern _OplState _opl;
