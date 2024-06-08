#pragma once
/*****************************************************
 * OPL tokens
 *****************************************************/
#define OPL_TRUE 1

#define OPL_FALSE 0

/*****************************************************
 * type forward declarations
 *****************************************************/
typedef enum   OplResult     OplResult;
typedef enum   OplPlatformID OplPlatformID;
typedef struct OplInitInfo   OplInitInfo;

/*****************************************************
 * type definitions
 *****************************************************/
enum OplResult {
  OPL_SUCCESS,
  OPL_INVALID_VALUE,
  OPL_PLATFORM_UNAVAILABLE,
};

enum OplPlatformID {
  OPL_PLATFORM_ID_ANY,
  OPL_PLATFORM_ID_COCOA,
  OPL_PLATFORM_ID_WIN32,
};

typedef struct OplInitInfo {
  const char *pApplicationName;
  int width;
  int height;
  OplPlatformID desiredPlatform;
} OplInitInfo;

typedef void(*OplTerminateRequestFun)();

typedef void(*OplSurfaceResizeFun)(int, int);
typedef void(*OplSurfaceMinimizeFun)();
typedef void(*OplSurfaceMaximizeFun)();

/*****************************************************
 * OPL public API
 *****************************************************/

/** @brief Initializes OPL library.
 *
 * Initializes mutable OPL state and creates surface.
 *
 */
OplResult oplInit(const OplInitInfo *pInitInfo);

/** @brief Terminates OPL library.
 *
 * Destroys surface and process memory clean up.
 *
 */
void oplTerminate();

/** @brief Polls platform events.
 *
 * Poll platform events and calls set event callbacks.
 *
 */
void oplPollEvents();

/** @brief Returns display application name.
 *
 */
const char* oplGetApplicationName();

/** @brief Changes display application name.
 *
 */
OplResult oplSetApplicationName(const char *pTitle);

/** @brief Returns surface resolution.
 *
 */
void oplGetSurfaceSize(int *width, int *height);

/** @brief Changes surface resolution.
 *
 */
OplResult oplSetSurfaceSize(int width, int height);

/** @brief Sets terminate request callback function.
 *
 */
void oplSetTerminateRequestCallback(OplTerminateRequestFun);

/** @brief Sets surface resize callback function.
 *
 */
void oplSetSurfaceResizeCallback(OplSurfaceResizeFun);

/** @brief Sets surface minimize callback function.
 *
 */
void oplSetSurfaceMinimizeCallback(OplSurfaceMinimizeFun);

/** @brief Sets surface maximize callback function.
 *
 */
void oplSetSurfaceMaximizeCallback(OplSurfaceMaximizeFun);
