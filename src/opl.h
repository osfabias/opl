/**
 * @file opl.h
 * @brief The header of the public opl functions.
 *
 * @copyright Copyright (c) 2023-2024 Osfabias
 * @license Licensed under the Apache License, Version 2.0.
 */
#pragma once

/**
 * @brief Window style flags.
 *
 * @var opl_window_hint::OPL_WINDOW_HINT_TITLED
 * The window displays it's title.
 *
 * @var opl_window_hint::OPL_WINDOW_HINT_CLOSABLE
 * The window displays/enables it's close button.
 *
 * @var opl_window_hint::OPL_WINDOW_HINT_RESIABLE
 * The window can be resized by user.
 *
 * @var opl_window_hint::OPL_WINDOW_HINT_BORDERLESS
 * The window doesn't display any peripheral elements.
 *
 * @var opl_window_hint::OPL_WINDOW_HINT_FULLSCREEN
 * The window is in the fullscreen mode.
 *
 * @var opl_window_hint::OPL_WINDOW_HINT_MINIATURIZABLE
 * The window can be hided.
 */
typedef enum opl_window_hint {
  OPL_WINDOW_HINT_TITLED_BIT         = 1 << 0,
  OPL_WINDOW_HINT_CLOSABLE_BIT       = 1 << 1,
  OPL_WINDOW_HINT_RESIZABLE_BIT      = 1 << 2,
  OPL_WINDOW_HINT_BORDERLESS_BIT     = 1 << 3,
  OPL_WINDOW_HINT_FULLSCREEN_BIT     = 1 << 4,
  OPL_WINDOW_HINT_MINIATURIZABLE_BIT = 1 << 5,
} opl_window_hint_t;

/**
 * @brief An opl window handle.
 */
typedef struct opl_window* opl_window_t;

/**
 * @brief Alert type.
 */
typedef enum opl_alert_style {
  OPL_ALERT_STYLE_INFO,
  OPL_ALERT_STYLE_WARN,
  OPL_ALERT_STYLE_ERROR,
} opl_alert_style_t;

/**
 * @brief Virtual key codes.
 *
 * This enum holds keycodes, that are corresponding to the
 * key codes used in Windows OS.
 *
 * https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */
typedef enum opl_key {
  OPL_KEY_BACKSPACE = 0x08,
  OPL_KEY_ENTER     = 0x0D,
  OPL_KEY_TAB       = 0x09,
  OPL_KEY_SHIFT     = 0x10,
  OPL_KEY_CONTROL   = 0x11,

  OPL_KEY_PAUSE    = 0x13,
  OPL_KEY_CAPSLOCK = 0x14,

  OPL_KEY_ESCAPE = 0x1B,

  OPL_KEY_CONVERT    = 0x1C,
  OPL_KEY_NONCONVERT = 0x1D,
  OPL_KEY_ACCEPT     = 0x1E,
  OPL_KEY_MODECHANGE = 0x1F,

  OPL_KEY_SPACE = 0x20,

  OPL_KEY_PAGEUP   = 0x21,
  OPL_KEY_PAGEDOWN = 0x22,
  OPL_KEY_END      = 0x23,
  OPL_KEY_HOME     = 0x24,

  OPL_KEY_LEFT  = 0x25,
  OPL_KEY_UP    = 0x26,
  OPL_KEY_RIGHT = 0x27,
  OPL_KEY_DOWN  = 0x28,

  OPL_KEY_SELECT      = 0x29,
  OPL_KEY_PRINT       = 0x2A,
  OPL_KEY_EXECUTE     = 0x2B,
  OPL_KEY_PRINTSCREEN = 0x2C,
  OPL_KEY_INSERT      = 0x2D,
  OPL_KEY_DELETE      = 0x2E,
  OPL_KEY_HELP        = 0x2F,

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

  OPL_KEY_APPS  = 0x5D,
  OPL_KEY_SLEEP = 0x5F,

  OPL_KEY_NUMPAD0   = 0x60,
  OPL_KEY_NUMPAD1   = 0x61,
  OPL_KEY_NUMPAD2   = 0x62,
  OPL_KEY_NUMPAD3   = 0x63,
  OPL_KEY_NUMPAD4   = 0x64,
  OPL_KEY_NUMPAD5   = 0x65,
  OPL_KEY_NUMPAD6   = 0x66,
  OPL_KEY_NUMPAD7   = 0x67,
  OPL_KEY_NUMPAD8   = 0x68,
  OPL_KEY_NUMPAD9   = 0x69,
  OPL_KEY_MULTIPLY  = 0x6A,
  OPL_KEY_ADD       = 0x6B,
  OPL_KEY_SEPARATOR = 0x6C,
  OPL_KEY_SUBTRACT  = 0x6D,
  OPL_KEY_DECIMAL   = 0x6E,
  OPL_KEY_DIVIDE    = 0x6F,

  OPL_KEY_F1  = 0x70,
  OPL_KEY_F2  = 0x71,
  OPL_KEY_F3  = 0x72,
  OPL_KEY_F4  = 0x73,
  OPL_KEY_F5  = 0x74,
  OPL_KEY_F6  = 0x75,
  OPL_KEY_F7  = 0x76,
  OPL_KEY_F8  = 0x77,
  OPL_KEY_F9  = 0x78,
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

  OPL_KEY_NUMLOCK      = 0x90,
  OPL_KEY_SCROLL       = 0x91,
  OPL_KEY_NUMPAD_EQUAL = 0x92,

  OPL_KEY_LSHIFT   = 0xA0,
  OPL_KEY_RSHIFT   = 0xA1,
  OPL_KEY_LCONTROL = 0xA2,
  OPL_KEY_RCONTROL = 0xA3,
  OPL_KEY_LALT     = 0xA4,
  OPL_KEY_RALT     = 0xA5,

  OPL_KEY_SEMICOLON = 0x3B,

  OPL_KEY_APOSTROPHE = 0xDE,
  OPL_KEY_EQUAL      = 0xBB,
  OPL_KEY_COMMA      = 0xBC,
  OPL_KEY_MINUS      = 0xBD,
  OPL_KEY_PERIOD     = 0xBE,
  OPL_KEY_SLASH      = 0xBF,

  OPL_KEY_GRAVE = 0xC0,

  OPL_KEY_LBRACKET  = 0xDB,
  OPL_KEY_BACKSLASH = 0xDC,
  OPL_KEY_RBRACKET  = 0xDD,

  OPL_KEY_MAX_ENUM = 0xFF
} opl_key_t;

/**
 * @brief Keyboard state.
 *
 * @var opl_keyboard_state::keys
 * An array of integers that represents key states. 1 represents 
 * that the key is down and 0 represents that the key is up. The 
 * index of each element corresponds to it's key code defined in
 * opl_key_t enum. The value of elements which indices not presented in 
 * the opl_key_t enum is undefined.
 */
typedef struct opl_keyboard_state {
  char keys[OPL_KEY_MAX_ENUM];
} opl_keyboard_state_t;

/**
 * @brief Mouse button codes.
 */
typedef enum opl_mouse_btn {
  OPL_MOUSE_BTN_LEFT,
  OPL_MOUSE_BTN_RIGHT,
  OPL_MOUSE_BTN_MIDDLE,

  OPL_MOUSE_BTN_MAX_ENUM
} opl_mouse_btn_t;

/**
 * @brief Mouse state.
 * @var opl_mouse_state::btns
 * An array of mouse button states. 0 represents that the mouse button
 * is up, 1 represents that the mouse button is down. The index of each
 * element (mouse button) corresponds to it's code (use opl_mouse_btn_t
 * enum for mouse button codes). The value of elements which indices 
 * not presented in the opl_key_t enum is undefined.
 *
 * @var opl_mouse_state::x
 * X position of the cursor on the screen.
 *
 * @var opl_mouse_state::y
 * Y position of the cursor on the screen.
 *
 * @var opl_mouse_state::wheel
 * A mouse wheel scroll.
 */
typedef struct opl_mouse_state {
  char btns[OPL_MOUSE_BTN_MAX_ENUM];
  int  x;
  int  y;
  int  wheel;
} opl_mouse_state_t;

/**
 * @brief Initializes opl.
 * 
 * This function should be called before any other opl functions.
 *
 * @return Return 1 on success, otherwise returns 0.
 */
int opl_init(void);

/**
 * @brief Terminates opl.
 */
void opl_quit(void);

/**
 * @brief Updates opl state.
 *
 * Runs a loop, where pumps all OS generated messages since the
 * last opl_update() call and processes them.
 */
void opl_update(void);

/**
 * @brief Opens window.
 *
 * @param width  The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @param titlte The title of the window.
 *
 * @return Returns opl window instance on success, otherwise returns 0.
 */
opl_window_t opl_window_open(
  int         width,
  int         height,
  const char *title
);

/**
 * @brief Opens window.
 *
 * @param width  The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @param titlte The title of the window.
 * @param x      The x position of the window in pixels.
 * @param y      The y position of the window in pixels.
 * @param hints  Creation hints.
 *
 * @return Returns opl window instance on success, otherwise returns 0.
 */
opl_window_t opl_window_open_ext(
  int                width,
  int                height,
  const char        *title,
  int                x,
  int                y,
  opl_window_hint_t  hints
);

/**
 * @brief Closes window.
 *
 * @param window An opl window handle.
 */
void opl_window_close(opl_window_t window);

/**
 * @brief Returns whether should window close or not.
 *
 * @param window An opl window handle.
 *
 * @return Returns 1 if OS requested window closing, otherwise returns 0.
 */
int opl_window_should_close(opl_window_t window);

/**
 * @brief Sets window's title.
 *
 * @param window An opl window handle.
 * @param title  New window title.
 */
void opl_window_set_title(opl_window_t window, const char *title);

/**
 * @brief Returns window's title.
 *
 * @param window An opl window handle.
 *
 * @return Returns a pointer to the window's title. Returned pointer
 *         shouldn't be freed by user.
 */
const char* opl_window_get_title(opl_window_t window);

/**
 * @brief Sets window's size.
 *
 * @param window An opl window handle.
 * @param width  A width in pixels.
 * @param height A height in pixels.
 */
void opl_window_set_size(opl_window_t window, int width, int height);

/**
 * @brief Returns window size.
 *
 * @param window An opl window handle.
 * @param width  A pointer to a variable, that will hold the window 
 *               width.
 * @param width  A pointer to a variable, that will hold the window 
 *               height.
 */
void opl_window_get_size(opl_window_t window, int *width, int *height);

/**
 * @brief Sets window position.
 *
 * @param window An opl window handle.
 * @param x      The new x position of the window.
 * @param y      The new y position of the window.
 */
void opl_window_set_pos(opl_window_t window, int x, int y);

/**
 * @brief Returns a window position.
 *
 * @param window An opl window handle.
 * @param x      A pointer to a variable, that will hold the window x 
 *               position on the display.
 * @param y      A pointer to a variable, that will hold the window y 
 *               position on the display.
 */
void opl_window_get_pos(opl_window_t window, int *x, int *y);

/**
 * @brief Hides window.
 *
 * @param window An opl window handle.
 */
void opl_hide(opl_window_t window);

/**
 * @brief Returns whether the window is miniaturized or not.
 *
 * @param window An opl window handle.
 *
 * @return Returns 1 if window miniaturized or 0 if it's not.
 */
int opl_is_hidden(opl_window_t window);

/**
 * @brief Shows window.
 *
 * @param window An opl window handle.
 */
void opl_show(opl_window_t window);

/**
 * @brief Returns whether a window is maximized or not.
 *
 * @param window An opl window handle.
 *
 * @return Returns 1 if window maximized or 0 if it's not.
 */
int opl_is_shown(opl_window_t window);

/**
 * @brief Toggles fullscreen mode for a window.
 *
 * @param window An opl window handle.
 */
void opl_set_fullscreen(opl_window_t window, int state);

/**
 * @brief Returns whether a window in fullscreen mode or not.
 *
 * @param window An opl window handle.
 *
 * @return Returns 1 if window in fullscreen mode or 0 if it's not.
 */
int opl_is_fullscreen(opl_window_t window);

/**
 * @brief Shows an alert window.
 *
 * This function will wait for the user to click any button or
 * close an alert window.
 *
 * @param title      Title of the alert window.
 * @param title      Title of the alert window.
 * @param style      The style of the alert window.
 * @param btn_count  The number of buttons.
 * @param btn_titles An array of buttons titles.
 *
 * @return Returns an index of a clicked button. If no buttons
 *         were passed will always return 0.
 */
int opl_alert_ext(
  const char       *title,
  const char       *text,
  opl_alert_style_t style,
  int               btn_count,
  const char*      *btn_titles
);

/**
 * @brief Shows an alert window.
 *
 * Function will wait for the user to close an alert window.
 *
 * @param title Title of the alert window.
 * @param text  Text of the the alert window.
 */
#define opl_alert(title, text) \
  opl_alert_ext(title, text, OPL_ALERT_STYLE_ERROR, 0, 0);

/**
 * @brief Returns a pointer to the keyboard state.
 *
 * @param state A pointer variable that will hold a pointer to
 *              the keyboard state. If the passed pointer is a
 *              null pointer the behaviour is undefined.
 *
 * @return Returns a pointer to the platform keyboard state.
 */
const opl_keyboard_state_t* opl_keyboard_get_state(void);

/**
 * @brief Returns a pointer to a mouse state.
 *
 * @returns A pointer to the platform mouse state.
 */
const opl_mouse_state_t* opl_mouse_get_state(void);

#ifdef OPL_INCLUDE_VULKAN
#include <vulkan/vulkan.h>

/**
 * @brief Creates Vulkan surface.
 */
VkResult opl_vk_surface_create(
  opl_window_t window, VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface
);

/**
 * @brief Returns number of required extensions for Vulkan
 * and their names.
 *
 * User shouldn't free returned array.
 */
void opl_vk_device_extensions(int *count, const char* *names);
#endif

