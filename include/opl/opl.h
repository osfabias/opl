#pragma once

#include <stdint.h> // for const size types

#include <vulkan/vulkan.h> // for surface creation

/************************************************
 *                  OPL tokens                  *
 ************************************************/
#define OPL_TRUE 1
#define OPL_FALSE 0

/************************************************
 *                  OPL types                   *
 ************************************************/
typedef struct OplInitInfo {
  const char *pApplicationName;
  uint16_t surfaceWidth;
  uint16_t surfaceHeight;
} OplInitInfo;

typedef enum OplKey {
  OPL_KEY_BACKSPACE = 0x08,
  OPL_KEY_ENTER = 0x0D,
  OPL_KEY_TAB = 0x09,
  OPL_KEY_SHIFT = 0x10,
  OPL_KEY_CONTROL = 0x11,

  OPL_KEY_PAUSE = 0x13,
  OPL_KEY_CAPSLOCK = 0x14,

  OPL_KEY_ESCAPE = 0x1B,

  OPL_KEY_CONVERT = 0x1C,
  OPL_KEY_NONCONVERT = 0x1D,
  OPL_KEY_ACCEPT = 0x1E,
  OPL_KEY_MODECHANGE = 0x1F,

  OPL_KEY_SPACE = 0x20,

  OPL_KEY_PAGEUP = 0x21,
  OPL_KEY_PAGEDOWN = 0x22,
  OPL_KEY_END = 0x23,
  OPL_KEY_HOME = 0x24,

  OPL_KEY_LEFT = 0x25,
  OPL_KEY_UP = 0x26,
  OPL_KEY_RIGHT = 0x27,
  OPL_KEY_DOWN = 0x28,

  OPL_KEY_SELECT = 0x29,
  OPL_KEY_PRINT = 0x2A,
  OPL_KEY_EXECUTE = 0x2B,
  OPL_KEY_PRINTSCREEN = 0x2C,
  OPL_KEY_INSERT = 0x2D,
  OPL_KEY_DELETE = 0x2E,
  OPL_KEY_HELP = 0x2F,

  OPL_KEY_0 = 0x30,
  OPL_KEY_1 = 0x31,
  OPL_KEY_2 = 0x32,
  OPL_KEY_3 = 0x33,
  OPL_KEY_4 = 0x34,
  OPL_KEY_5 = 0x35,
  OPL_KEY_6 = 0x36,
  OPL_KEY_7 = 0x37,
  OPL_KEY_8 = 0x38,
  OPL_KEY_9 = 0x39,

  OPL_KEY_A = 0x41,
  OPL_KEY_B = 0x42,
  OPL_KEY_C = 0x43,
  OPL_KEY_D = 0x44,
  OPL_KEY_E = 0x45,
  OPL_KEY_F = 0x46,
  OPL_KEY_G = 0x47,
  OPL_KEY_H = 0x48,
  OPL_KEY_I = 0x49,
  OPL_KEY_J = 0x4A,
  OPL_KEY_K = 0x4B,
  OPL_KEY_L = 0x4C,
  OPL_KEY_M = 0x4D,
  OPL_KEY_N = 0x4E,
  OPL_KEY_O = 0x4F,
  OPL_KEY_P = 0x50,
  OPL_KEY_Q = 0x51,
  OPL_KEY_R = 0x52,
  OPL_KEY_S = 0x53,
  OPL_KEY_T = 0x54,
  OPL_KEY_U = 0x55,
  OPL_KEY_V = 0x56,
  OPL_KEY_W = 0x57,
  OPL_KEY_X = 0x58,
  OPL_KEY_Y = 0x59,
  OPL_KEY_Z = 0x5A,

  OPL_KEY_LSUPER = 0x5B,
  OPL_KEY_RSUPER = 0x5C,

  OPL_KEY_APPS = 0x5D,
  OPL_KEY_SLEEP = 0x5F,

  // by the way, who even uses numpad keys in games?
  OPL_KEY_NUMPAD0 = 0x60,
  OPL_KEY_NUMPAD1 = 0x61,
  OPL_KEY_NUMPAD2 = 0x62,
  OPL_KEY_NUMPAD3 = 0x63,
  OPL_KEY_NUMPAD4 = 0x64,
  OPL_KEY_NUMPAD5 = 0x65,
  OPL_KEY_NUMPAD6 = 0x66,
  OPL_KEY_NUMPAD7 = 0x67,
  OPL_KEY_NUMPAD8 = 0x68,
  OPL_KEY_NUMPAD9 = 0x69,
  OPL_KEY_MULTIPLY = 0x6A,
  OPL_KEY_ADD = 0x6B,
  OPL_KEY_SEPARATOR = 0x6C,
  OPL_KEY_SUBTRACT = 0x6D,
  OPL_KEY_DECIMAL = 0x6E,
  OPL_KEY_DIVIDE = 0x6F,

  OPL_KEY_F1 = 0x70,
  OPL_KEY_F2 = 0x71,
  OPL_KEY_F3 = 0x72,
  OPL_KEY_F4 = 0x73,
  OPL_KEY_F5 = 0x74,
  OPL_KEY_F6 = 0x75,
  OPL_KEY_F7 = 0x76,
  OPL_KEY_F8 = 0x77,
  OPL_KEY_F9 = 0x78,
  OPL_KEY_F10 = 0x79,
  OPL_KEY_F11 = 0x7A,
  OPL_KEY_F12 = 0x7B,
  OPL_KEY_F13 = 0x7C,
  OPL_KEY_F14 = 0x7D,
  OPL_KEY_F15 = 0x7E,
  OPL_KEY_F16 = 0x7F,
  OPL_KEY_F17 = 0x80,
  OPL_KEY_F18 = 0x81,
  OPL_KEY_F19 = 0x82,
  OPL_KEY_F20 = 0x83,
  OPL_KEY_F21 = 0x84,
  OPL_KEY_F22 = 0x85,
  OPL_KEY_F23 = 0x86,
  OPL_KEY_F24 = 0x87,

  OPL_KEY_NUMLOCK = 0x90,
  OPL_KEY_SCROLL = 0x91,
  OPL_KEY_NUMPAD_EQUAL = 0x92,

  OPL_KEY_LSHIFT = 0xA0,
  OPL_KEY_RSHIFT = 0xA1,
  OPL_KEY_LCONTROL = 0xA2,
  OPL_KEY_RCONTROL = 0xA3,
  OPL_KEY_LALT = 0xA4,
  OPL_KEY_RALT = 0xA5,

  OPL_KEY_SEMICOLON = 0x3B,

  OPL_KEY_APOSTROPHE = 0xDE,
  OPL_KEY_EQUAL = 0xBB,
  OPL_KEY_COMMA = 0xBC,
  OPL_KEY_MINUS = 0xBD,
  OPL_KEY_PERIOD = 0xBE,
  OPL_KEY_SLASH = 0xBF,

  OPL_KEY_GRAVE = 0xC0,

  OPL_KEY_LBRACKET = 0xDB,
  OPL_KEY_BACKSLASH = 0xDC,
  OPL_KEY_RBRACKET = 0xDD,

  OPL_KEY_MAX_ENUM = 0xFF
} OplKey;

typedef struct OplKeyboardState {
  uint8_t pKeyStates[OPL_KEY_MAX_ENUM];
} OplKeyboardState;

typedef enum OplMouseButton {
  OPL_MOUSE_BUTTON_LEFT,
  OPL_MOUSE_BUTTON_RIGHT,
  OPL_MOUSE_BUTTON_MIDDLE,
  OPL_MOUSE_BUTTON_FORWARD,
  OPL_MOUSE_BUTTON_BACK,

  OPL_MOUSE_BUTTON_MAX_ENUM
} OplMouseButton;

typedef struct OplMouseState {
  uint8_t pButtonStates[OPL_MOUSE_BUTTON_MAX_ENUM];
  uint16_t x;
  uint16_t y;
  int8_t wheel;
} OplMouseState;

typedef enum OplColor {
  OPL_COLOR_NONE,
  OPL_COLOR_TRACE,
  OPL_COLOR_INFO,
  OPL_COLOR_WARN,
  OPL_COLOR_ERROR,
  OPL_COLOR_FATAL,
} OplColor;

/************************************************
 *                    OPL API                   *
 ************************************************/
/**
 * @brief Initializes opl.
 */
uint8_t oplInit(const OplInitInfo *pInitInfo);

/**
 * @brief Terminates opl.
 */
void oplTerminate();

/**
 * @brief Returns OPL_TRUE if opl terminate was requested,
 * otherwise returns OPL_FALSE.
 */
uint8_t oplShouldTerminate();

/**
 * @brief Returns a pointer to a keyboard state.
 *
 * If this function is called on console platforms it
 * returns NULL.
 */
const OplKeyboardState* oplKeyboardGetState();

/**
 * @brief Returns a pointer to a mouse state.
 *
 * If this function is called on console platform it returns
 * NULL.
 */
const OplMouseState* oplMouseGetState();


/**
 * @brief Pumps platform messages.
 */
void oplPumpMessages();

/**
 * @brief Allocates a block of memory of the given size.
 */
void* oplAlloc(uint64_t size);

/**
 * @brief Reallocates a block of memory to the given size.
 */
void* oplRealloc(void *pBlock, uint64_t size);

/**
 * @brief Frees a block of memory.
 */
void  oplFree(void *pBlock);

/**
 * @bried Copies a block of memory.
 */
void oplMemCpy(void *pDstBlock, const void *pSrcBlock,
               uint64_t size);

/**
 * @brief Sets a block of memory to a given value.
 */
void oplMemSet(void *pBlock, int32_t value, uint64_t size);

/**
 * @brief Moves a block of memory.
 */
void oplMemMove(void *pDstBlock, const void *pSrcBlock,
                uint64_t size);

/**
 * @brief Compares two block of memory.
 */
int32_t oplMemCmp(const void *pBlock1, const void *pBlock2,
                  uint64_t size);

/**
 * @brief Writes colorized text to console.
 */
void oplConsoleWrite(const char *pMessage, OplColor color);

/**
 * @brief Returns amount of milliseconds past since the unix epoch.
 */
uint64_t oplGetTime();

/**
 * @brief Sleeps on current thread for the given amount of
 * milliseconds.
 *
 * Should only be used for giving time back to the OS for
 * unused update power in order not to use 100% of cpu.
 */
void oplSleep(uint64_t ms);

/************************************************
 *                   Vulkan                     *
 ************************************************/
/**
 * @brief Creates Vulkan surface.
 */
VkResult oplCreateVkSurface(
  VkInstance instance, const VkAllocationCallbacks *pAllocator,
  VkSurfaceKHR *pSurface);

/**
 * @brief Returns number of required extensions for Vulkan
 * and their names.
 *
 * User shouldn't free returned array.
 */
uint16_t oplVkExtensions(const char* *ppExtensionNames);
