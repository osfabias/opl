/**
 * @file opl.h
 * @brief The header of the OPL API
 */
#pragma once

#include <stdint.h>        // for const size types

#include <vulkan/vulkan.h> // for surface creation

/************************************************
 *                  OPL tokens                  *
 ************************************************/
/**
 * @brief True.
 */
#define OPL_TRUE 1

/**
 * @brief False.
 */
#define OPL_FALSE 0

/************************************************
 *                  OPL types                   *
 ************************************************/
/**
 * @brief Key codes.
 */
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

/**
 * @brief Keyboard state.
 * @var OplKeyboardState::keys
 * An array, that holds key states. 0 represents that the key is
 * up, 1 represents that the key is down. The index of each
 * element (key) corresponds to it's key code (use OplKey enum
 * for key codes).
 */
typedef struct OplKeyboardState {
  uint8_t keys[OPL_KEY_MAX_ENUM];
} OplKeyboardState;

/**
 * @brief Mouse button codes.
 */
typedef enum OplMouseButton {
  OPL_MOUSE_BUTTON_LEFT,
  OPL_MOUSE_BUTTON_RIGHT,
  OPL_MOUSE_BUTTON_MIDDLE,
  OPL_MOUSE_BUTTON_FORWARD,
  OPL_MOUSE_BUTTON_BACK,

  OPL_MOUSE_BUTTON_MAX_ENUM
} OplMouseButton;

/**
 * @brief Mouse state.
 * @var OplMouseState::buttons
 * An array of mouse button states. 0 represents that the mouse button
 * is up, 1 represents that the mouse button is down. The index of each
 * element (mouse button) corresponds to it's code (use OplMouseButton
 * enum for mouse button codes).
 *
 * @var OplMouseState::x
 * X position of the cursor on the screen.
 *
 * @var OplMouseState::y
 * Y position of the cursor on the screen.
 *
 * @var OplMouseState::wheel
 * Wheel scroll.
 */
typedef struct OplMouseState {
  uint8_t buttons[OPL_MOUSE_BUTTON_MAX_ENUM];
  uint16_t x;
  uint16_t y;
  int8_t wheel;
} OplMouseState;

/**
 * @brief Window flags.
 */
typedef enum OplWindowStyleFlag {
  OPL_WINDOW_STYLE_TITLED         = 1 << 0,
  OPL_WINDOW_STYLE_CLOSABLE       = 1 << 1,
  OPL_WINDOW_STYLE_RESIZABLE      = 1 << 2,
  OPL_WINDOW_STYLE_BORDERLESS     = 1 << 3,
  OPL_WINDOW_STYLE_FULLSCREEN     = 1 << 4,
  OPL_WINDOW_STYLE_MINIATURIZABLE = 1 << 5,
} OplWindowStyleFlag;

/**
 * @brief Window creation info.
 *
 * @var OplWindowCreateInfo::flags
 * Window flags, used for enabling features.
 *
 * @var OplWindowCreateInfo::title
 * String to show as a title of the window.
 *
 * @var OplWindowCreateInfo::x
 * X position of the window on the display.
 *
 * @var OplWindowCreateInfo::y
 * Y position of the window on the display.
 *
 * @var OplWindowCreateInfo::width
 * The width of the window in pixels.
 *
 * @var OplWindowCreateInfo::height
 * The height of the window in pixels.
 */
typedef struct OplWindowCreateInfo {
  OplWindowStyleFlag styleFlags;
  const char        *title;
  uint16_t           x;
  uint16_t           y;
  uint16_t           width;
  uint16_t           height;
} OplWindowCreateInfo;

/**
 * @brief Window handle;
 */
typedef struct OplWindow OplWindow;

/**
 * @brief An alert window style.
 */
typedef enum OplAlertStyle {
  OPL_ALERT_STYLE_INFO,
  OPL_ALERT_STYLE_WARN,
  OPL_ALERT_STYLE_ERROR,
} OplAlertStyle;

/**
 * @brief An alert window button.
 * @var OplAlertButton::title
 * A title of the button.
 */
typedef struct OplAlertButton {
  const char *title;
} OplAlertButton;

/**
 * @brief Alert show info.
 *
 * @var OplAlertShowInfo::style
 * Alert window style.
 *
 * @var OplAlertShowInfo::title
 * A title of the alert window.
 *
 * @var OplAlertShowInfo::message
 * A message of the alert window.
 *
 * @var OplAlertShowInfo::buttonCount
 * A button count.
 *
 * @var OplAlertShowInfo::buttons
 * A pointer to an array of OplAlertButton structs.
 */
typedef struct OplAlertShowInfo {
  OplAlertStyle style;
  const char *title;
  const char *message;
  uint32_t buttonCount;
  const OplAlertButton *buttons;
} OplAlertShowInfo;

/**
 * @brief Output text style.
 *
 * Values are took from https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
typedef enum OplTextStyleFlag {
  OPL_TEXT_STYLE_NORMAL       = 1 << 0, // \033[0m
  OPL_TEXT_STYLE_BOLD         = 1 << 1, // \033[1m
  OPL_TEXT_STYLE_LIGHT        = 1 << 2, // \033[2m
  OPL_TEXT_STYLE_ITALIC       = 1 << 3, // \033[3m
  OPL_TEXT_STYLE_UNDERLINE    = 1 << 4, // \033[4m
} OplTextStyleFlag;

/**
 * @brief Output foreground color for console.
 *
 * Values are took from http://en.wikipedia.org/wiki/ANSI_color#Colors.
 */
typedef enum OplFgColor {
  OPL_FG_COLOR_DEFAULT        = 37,
  OPL_FG_COLOR_BLACK          = 30,
  OPL_FG_COLOR_RED            = 31,
  OPL_FG_COLOR_GREEN          = 32,
  OPL_FG_COLOR_YELLOW         = 33,
  OPL_FG_COLOR_BLUE           = 34,
  OPL_FG_COLOR_MAGENTA        = 35,
  OPL_FG_COLOR_CYAN           = 36,
  OPL_FG_COLOR_WHITE          = 37,
  OPL_FG_COLOR_BRIGHT_BLACK   = 90,
  OPL_FG_COLOR_BRIGHT_RED     = 91,
  OPL_FG_COLOR_BRIGHT_GREEN   = 92,
  OPL_FG_COLOR_BRIGHT_YELLOW  = 93,
  OPL_FG_COLOR_BRIGHT_BLUE    = 94,
  OPL_FG_COLOR_BRIGHT_MAGENTA = 95,
  OPL_FG_COLOR_BRIGHT_CYAN    = 96,
  OPL_FG_COLOR_BRIGHT_WHITE   = 97,
} OplFgColor;

/**
 * @brief Output background color for console.
 *
 * Values are took from http://en.wikipedia.org/wiki/ANSI_color#Colors.
 */
typedef enum OplBgColor {
  OPL_BG_COLOR_DEFAULT        = 10,
  OPL_BG_COLOR_BLACK          = 40,
  OPL_BG_COLOR_RED            = 41,
  OPL_BG_COLOR_GREEN          = 42,
  OPL_BG_COLOR_YELLOW         = 43,
  OPL_BG_COLOR_BLUE           = 44,
  OPL_BG_COLOR_MAGENTA        = 45,
  OPL_BG_COLOR_CYAN           = 46,
  OPL_BG_COLOR_WHITE          = 47,
  OPL_BG_COLOR_BRIGHT_BLACK   = 100,
  OPL_BG_COLOR_BRIGHT_RED     = 101,
  OPL_BG_COLOR_BRIGHT_GREEN   = 102,
  OPL_BG_COLOR_BRIGHT_YELLOW  = 103,
  OPL_BG_COLOR_BRIGHT_BLUE    = 104,
  OPL_BG_COLOR_BRIGHT_MAGENTA = 105,
  OPL_BG_COLOR_BRIGHT_CYAN    = 106,
  OPL_BG_COLOR_BRIGHT_WHITE   = 107,
} OplBgColor;

/**
 * @brief File mode.
 */
typedef enum OplFileMode {
  OPL_FILE_MODE_READ,
  OPL_FILE_MODE_WRITE,
  OPL_FILE_MODE_APPEND,
  OPL_FILE_MODE_READ_AND_WRITE,
  OPL_FILE_MODE_WRITE_AND_READ,
  OPL_FILE_MODE_BINARY_READ,
  OPL_FILE_MODE_BINARY_WRITE,
  OPL_FILE_MODE_BINARY_APPEND,
  OPL_FILE_MODE_BINARY_READ_AND_WRITE,
  OPL_FILE_MODE_BINARY_WRITE_AND_READ,
  OPL_FILE_MODE_TEMP,
} OplFileMode;

/**
 * @brief OPL file handle.
 */
typedef struct OplFile OplFile;

/** 
 * @brief OPL directory handle.
 */
typedef struct OplDir OplDir;

/**
 * @brief OPL thread handle.
 */
typedef struct OplThread OplThread;

/**
 *
 */
typedef void*(*OplThreadFunc)(void *);

/**
 * @brief OPL mutex handle.
 */
typedef struct OplMutex OplMutex;

/**
 * @brief OPL fence handle.
 */
typedef struct OplFence OplFence;

/************************************************
 *                    OPL API                   *
 ************************************************/

/**
 * @brief Initializes OPL.
 * @return Return OPL_TRUE on successfull initialization,
 *         otherwise returns OPL_FALSE.
 */
uint8_t oplInit();

/**
 * @brief Terminates OPL.
 */
void oplTerminate();

/**
 * @brief Pumps platform messages.
 */
void oplPumpMessages();

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
 * @brief Shows an alert window.
 * @param info A pointer to an OplAlertShowInfo struct.
 * @return Returns an index of a button or 0, if no 
 *         buttons were provided.
 */
uint32_t oplAlertShow(const OplAlertShowInfo *info);

/**
 * @brief Creates a desktop window.
 * @param createInfo A pointer to OplWindowCreateInfo struct.
 * @return Returns an OPL window handle.
 */
OplWindow* oplWindowCreate(const OplWindowCreateInfo *createInfo);

/**
 * @brief Destroy a desktop window.
 */
void oplWindowDestroy(OplWindow *window);

/**
 * @brief Returns wheter should window close or not.
 * @param window An OPL window handle.
 * @return Returns OPL_TRUE if window closing was requested,
 * otherwise returns OPL_FALSE.
 */
uint8_t oplWindowShouldClose(OplWindow *window);

/**
 * @brief Sets window's title.
 * @param window An OPL window handle.
 * @param title A title to set.
 */
void oplWindowSetTitle(OplWindow *window, const char *title);

/**
 * @brief Returns window's title.
 * @param window An OPL window handle.
 * @return Returns a pointer to a window title.
 */
const char* oplWindowGetTitle(OplWindow *window);

/**
 * @brief Sets window's size.
 * @param window An OPL window handle.
 * @param width A width in pixels.
 * @param height A height in pixels.
 */
void oplWindowSetSize(OplWindow *window, uint16_t width, uint16_t height);

/**
 * @brief Returns window size.
 * @param window An OPL window handle.
 * @param width A pointer to a variable, that will hold a window's width.
 * @param width A pointer to a variable, that will hold a window's height.
 */
void oplWindowGetSize(OplWindow *window, uint16_t *width, uint16_t *height);

/**
 * @brief Sets window position.
 * @param window An OPL window handle.
 * @param x Window x position.
 * @param y Window y position.
 */
void oplWindowSetPosition(OplWindow *window, uint16_t x, uint16_t y);

/**
 * @brief Returns window position.
 * @param window An OPL window handle.
 * @param x A pointer to a variable, that will hold a window's x position.
 * @param y A pointer to a variable, that will hold a window's y position.
 */
void oplWindowGetPosition(OplWindow *window, uint16_t *x, uint16_t *y);

/**
 * @brief Minituarizes window.
 * @param window An OPL window handle.
 */
void oplWindowMiniaturize(OplWindow *window);

/**
 * @brief Returns wheter window is miniaturized or not.
 * @param window An OPL window handle.
 * @return Returns OPL_TRUE if window miniaturized or
 *         OPL_FALSE if it's not.
 */
uint8_t oplWindowIsMinituarized(OplWindow *window);

/**
 * @brief Maximized window.
 * @param window An OPL window handle.
 */
void oplWindowMaximize(OplWindow *window);

/**
 * @brief Returns wheter window is maximized or not.
 * @param window An OPL window handle.
 * @return Returns OPL_TRUE if window maximized or
 *         OPL_FALSE if it's not.
 */
uint8_t oplWindowIsMaximized(OplWindow *window);

/**
 * @brief Toggles fullscreen mode for a window.
 * @param window An OPL window handle.
 */
void oplWindowToggleFullscreen(OplWindow *window);

/**
 * @brief Return wheter a window in fullscreen mode or not.
 * @param window An OPL window handle.
 * @return Returns OPL_TRUE if window in fullscreen mode
 *         or OPL_FALSE if it's not.
 */
uint8_t oplWindowIsFullscreen(OplWindow *window);

/**
 * @brief Allocates a memory block of of the given size.
 * @param size A size of the memory block in bytes.
 * @return Returns a pointer to a memory block if allocation
 *         was successfull, otherwise return a NULL.
 */
void* oplAlloc(uint64_t size);

/**
 * @brief Reallocates a memory block to the given size.
 * @param block A pointer to a memory block.
 * @param size A new size of a memory block in bytes.
 * @return Returns a pointer to a memory block if allocation
 *         was successfull, otherwise return a NULL.
 */
void* oplRealloc(void *block, uint64_t size);

/**
 * @brief Frees a memory block.
 * @param A pointer to a memory block.
 */
void oplFree(void *block);

/**
 * @bried Copies a memory block.
 * @param dst A pointer to a destination memory block.
 * @param dst A pointer to a source memory block.
 * @param size A size of a memory block to copy in bytes.
 */
void oplMemCpy(void *dst, const void *src, uint64_t size);

/**
 * @brief Sets a block of memory to a given value.
 * @param block A pinter to a memory block.
 * @param value A value to set.
 * @param size A size of a memory block to set value to.
 */
void oplMemSet(void *block, int32_t value, uint64_t size);

/**
 * @brief Moves a block of memory.
 * @param dst A pointer to a destination memory block.
 * @param dst A pointer to a source memory block.
 * @param size A size of a memory block to move in bytes.
 */
void oplMemMove(void *dst, const void *src, uint64_t size);

/**
 * @brief Compares two block of memory.
 * @param block1 A pointer to a first memory block.
 * @param block1 A pointer to a sefence memory block.
 * @param size A size of a memory block to compare in bytes.
 */
int32_t oplMemCmp(const void *block1, const void *block2,
                  uint64_t size);

/**
 * @brief Sets console output style.
 * @param textStyle A text style.
 */
void oplConsoleSetTextStyle(OplTextStyleFlag textStyleFlags);

/**
 * @brief Sets console output color.
 * @param fgColor A foreground color of the message.
 * @param bgColor A background color of the message.
 */
void oplConsoleSetColor(OplFgColor fgColor, OplBgColor bgColor);

/**
 * @brief Writes colorized text to console.
 * @param message A pointer to a message to write to console.
 */
void oplConsoleWrite(const char *message, ...);

/**
 * @brief Reads formatted input from console.
 * @param string A pointer to a string to write extracted
 *               characters from the stream to. 
 * @param bufferLimit A limit of characters to extract.
 */
void oplConsoleRead(char *string, uint64_t bufferLimit);

/**
 * @brief Reads formatted input from console.
 * @param format A string that that control how characters
 *               extracted from the stream are treated.
 * @param ... VA arguments.
 */
void oplConsoleReadFormatted(const char *format, ...);

/**
 * @brief Checks if the path points to a file.
 */
uint8_t oplIsFile(const char *path);

/**
 * @brief Opens a file.
 */
OplFile* oplFileOpen(const char *path, OplFileMode mode);

/**
 * @brief Closes a file.
 */
uint8_t oplFileClose(OplFile *file);

/**
 * @brief Checks if file cursor at the end.
 */
uint8_t oplFileIsEof(OplFile *file);

/**
 * @brief Renames the file.
 */
uint8_t oplFileRename(const char *oldPath, const char *newPath);

/**
 * @brief Deletes the file.
 */
uint8_t oplFileDelete(const char *path);

/**
 * @brief Copies a file.
 */
uint8_t oplFileCopy(OplFile *dstFile, const OplFile *srcFile);

/**
 * @brief Copies a file.
 */
uint8_t oplFileCopyByPath(const char *dstPath,
                          const char *srcPath);

/**
 * @brief Checks if file exists.
 */
uint8_t oplFileIsExist(const char *path);

/**
 * @brief Returs a size of a file in bytes.
 */
uint64_t oplFileSize(OplFile *file);

/**
 * @brief Sets a file cursos position.
 */
uint8_t oplFileCursorSetPosition(OplFile *file, uint32_t position);

/**
 * @brief Returns a file cursos position.
 */
uint32_t oplFileCursorGetPosition(OplFile *file);

/**
 * @brief Sets a file cursor position to the
 *        end of the file.
 */
uint8_t oplFileCursorJumpEnd(OplFile *file);

/**
 * @brief Reads a whole file.
 */
uint32_t oplFileRead(OplFile *file, uint32_t size,
                    uint32_t count, char *out);

/**
 * @brief Reads a character from a file.
 */
uint8_t oplFileReadChar(OplFile *file, char *out);

/**
 * @brief Reads a line from a file.
 */
uint8_t oplFileReadLine(OplFile *file, uint64_t bufferLimit,
                        char *out);

/**
 * @brief
 */
uint8_t oplFileReadFormatted(OplFile *file,
                             const char *format, ...);

/**
 * @brief
 */
uint32_t oplFileWrite(OplFile *file, uint32_t size,
                     uint32_t count, void *in);

/**
 * @brief Writes a character into a file.
 */
uint8_t oplFileWriteChar(OplFile *file, char *in);

/**
 * @brief Writes a string into a file.
 */
uint8_t oplFileWriteString(OplFile *file, char *in);

/**
 * @brief
 */
uint8_t oplFileWriteFormatted(OplFile *file,
                              const char *format, ...);

/**
 * @brief Check if path points to a 
 *        dir.
 */
uint8_t oplIsDir(const char *path);

/**
 * @brief
 */
OplDir* oplDirOpen(const char *path);

/**
 * @brief Closes a directory.
 */
uint8_t oplDirClose(OplDir *dir);

/**
 * @brief Create a directory.
 */
uint8_t oplDirCreate(const char *path);

/**
 * @brief Deletes a directory.
 */
uint8_t oplDirDelete(const char *path);

/**
 * @brief Renames a directory.
 */
#define oplDirRename(oldPath, newPath) \
  oplFileRename(oldPath, newPath)

/**
 * @brief
 */
uint8_t oplDirRead(OplDir *dir, char *out);

/**
 * @brief
 */
void oplDirCursorSetPos(OplDir *dir, uint32_t pos);

/**
 * @brief
 */
uint32_t oplDirCursorGetPos(OplDir *dir);

/**
 * @brief Returns an array of all files and directories in
 *        directory.
 */
uint32_t oplDirList(const char *path, uint32_t bufferLimit,
                    const char* *paths);

/**
 * @brief Returns an array of all files in specified directory
 *        and in subdirectories.
 */
uint32_t oplDirListRecurse(const char *path, uint32_t bufferLimit,
                           char paths[][1024]);

/**
 * @brief Creates an OPL thread.
 */
OplThread* oplThreadCreate(OplThreadFunc func, void *data);

/**
 * @brief Destroys an OPL thread.
 */
void oplThreadDestroy (OplThread *thread);

/**
 * @brief
 */
uint8_t oplThreadJoin(OplThread *thread, void *out);

/**
 * @brief 
 */
#define oplThreadWait(thread) oplThreadJoin(thread, 0)

/**
 * @brief
 */
uint8_t oplThreadDetach(OplThread *thread);

/**
 * @brief Exits an OPL thread.
 */
void oplThreadExit(void *data);

/**
 * @brief Returns an OPL thread handle of the
 *        thread where this function was executed.
 */
OplThread* oplThreadSelf();

/**
 * @brief Sleeps on a current thread.
 * @param millisefences A number of milliseconds to sleep.
 */
uint8_t oplThreadSleep(uint64_t millisefences);

/**
 * @brief Creates an OPL mutex.
 */
OplMutex* oplMutexCreate();

/**
 * @brief Destroys an OPL mutex.
 */
void oplMutextDestroy(OplMutex *mutex);

/**
 * @brief Locks an OPL mutex.
 */
void oplMutexLock(OplMutex *mutex);

/**
 * @brief Tries to lock an OPL mutex.
 */
uint8_t oplMutexTryLock(OplMutex *mutex);

/**
 * @brief Unlocks an OPL mutex.
 */
void oplMutexUnlock(OplMutex *mutex);

/**
 * @brief Create an OPL fence.
 */
OplFence* oplFenceCreate();

/**
 * @brief Destroys an OPL fence.
 */
void oplFenceDestroy(OplFence *fence);

/**
 * @brief Signals an OPL fence.
 */
void oplFenceSignal(OplFence *fence);

/**
 * @brief Broadcasts an OPL fence.
 */
void oplFenceBroadcast(OplFence *fence);

/**
 * @brief Wait for an OPL fence to get open.
 */
void oplFenceWait(OplFence *fence, OplMutex *mutex);

/**
 * @brief Returns amount of millisefences past
 *        since the unix epoch.
 */
uint64_t oplGetAbsoluteTime();

/************************************************
 *                   Vulkan                     *
 ************************************************/
/**
 * @brief Creates Vulkan surface.
 */
VkResult oplCreateSurface(
  OplWindow *window, VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface);

/**
 * @brief Returns number of required extensions for Vulkan
 * and their names.
 *
 * User shouldn't free returned array.
 */
void oplGetDeviceExtensions(
  uint32_t *extensionsCount, const char* *extensionNames);
