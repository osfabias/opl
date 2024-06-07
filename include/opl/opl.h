#pragma once
/*****************************************************
 * OPL stdlib includes
 *****************************************************/
#include <stdint.h>

/*****************************************************
 * OPL tokens
 *****************************************************/
#define OPL_TRUE 1

#define OPL_FALSE 0

/*****************************************************
 * OPL enums
 *****************************************************/
typedef enum OplResult {
  OPL_SUCCESS = 0,
  OPL_UNKWOWN_ERROR = -1,
} OplResult;

/*****************************************************
 * OPL types
 *****************************************************/
typedef struct OplInitInfo {
  const char *pApplicationName;
  uint16_t resolutionX;
  uint16_t resolutionY;
} OplInitInfo;

typedef void(*OplTerminateRequestFun)();

typedef void(*OplSurfaceResizeFun)(uint16_t, uint16_t);
typedef void(*OplSurfaceMinimizeFun)();
typedef void(*OplSurfaceMaximizeFun)();

/*****************************************************
 * OPL public API
 *****************************************************/
OplResult oplInit(const OplInitInfo*);
void oplTerminate();

void oplPollEvents();

void oplSetTerminateRequestCallback(OplTerminateRequestFun);

void oplSetSurfaceResizeCallback(OplSurfaceResizeFun);
void oplSetSurfaceMinimizeCallback(OplSurfaceMinimizeFun);
void oplSetSurfaceMaximizeCallback(OplSurfaceMaximizeFun);
