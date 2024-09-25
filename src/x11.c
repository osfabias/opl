#include <stdio.h>

#include <X11/Xlib.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

#include "opl/opl.h"

typedef struct _OplX11Window {
  Window window;
  uint8_t shouldClose;
} _OplX11Window;

static struct {
  uint8_t initialized;
  Display *display;
  int screenIndex;
  Window rootWindow;

  OplMouseState mouseState;
  OplKeyboardState keyboardState;
} s_x11State = { .initialized = OPL_FALSE };

uint8_t oplInit() {
  if (s_x11State.initialized) { return OPL_TRUE; }

  s_x11State.display = XOpenDisplay(0);
  if (!s_x11State.display) { return OPL_FALSE; }

  // Get default screen and root window
  s_x11State.screenIndex = XDefaultScreen(s_x11State.display);
  s_x11State.rootWindow = RootWindow(s_x11State.display, s_x11State.screenIndex);

  s_x11State.initialized = OPL_TRUE;

  return OPL_TRUE;
}

void oplTerminate() {
  if (!s_x11State.initialized) { return; }

  XCloseDisplay(s_x11State.display);
  s_x11State.initialized = OPL_FALSE;
}

void oplPumpMessages() {
  XEvent event;

  while (!XNextEvent(s_x11State.display, &event)) {
    switch (event.type) {
      case KeyPress:
        s_x11State.keyboardState.keys[event.xkey.keycode] = 1;
        break;
      case KeyRelease:
        s_x11State.keyboardState.keys[event.xkey.keycode] = 0;
        break;
      case ButtonPress:
        s_x11State.mouseState.buttons[event.xbutton.button] = 1;
        break;
      case ButtonRelease:
        s_x11State.mouseState.buttons[event.xbutton.button] = 0;
        break;
      case MotionNotify:
        s_x11State.mouseState.x = event.xbutton.x;
        s_x11State.mouseState.y = event.xbutton.y;
        break;
      case Expose:
        break;
    }
  }
}

const OplKeyboardState* oplKeyboardGetState() {
  return &s_x11State.keyboardState;
}

const OplMouseState* oplMouseGetState() {
  return &s_x11State.mouseState;
}

OplWindow oplWindowCreate(const OplWindowCreateInfo *createInfo) {
  _OplX11Window *window = oplAlloc(sizeof(_OplX11Window));
  window->shouldClose = OPL_FALSE;

  #warning "oplWindowCreate(): OPL window style flags aren't used"

  XSetWindowAttributes windowAttributes = {
    .background_pixmap     = ParentRelative,
    .background_pixel      = 0xff101010, // #101010 ~ kinda black
    .border_pixmap         = CopyFromParent,
    .border_pixel          = 0Xff1c1f25, // #1c1f25 ~ kinda dark gray
    .bit_gravity           = 0,
    .win_gravity           = NorthWestGravity,
    .event_mask            = KeyPressMask     | KeyReleaseMask |
                             ButtonPressMask  | ButtonRelease  |
                             PointerMotionMask,
    .save_under            = 0,
    .backing_pixel         = 0,
    .backing_store         = 0,
    .backing_planes        = 0,
    .override_redirect     = False,
    .do_not_propagate_mask = 0,
    .colormap              = DefaultColormap(s_x11State.display,
                                             s_x11State.screenIndex),
    .cursor                = None,
  };

  window->window = XCreateWindow(
    s_x11State.display,
    s_x11State.rootWindow,
    createInfo->x,
    createInfo->y,
    createInfo->width,
    createInfo->height,
    1, // Border size
    DefaultDepth(s_x11State.display, s_x11State.screenIndex),
    InputOutput,
    DefaultVisual(s_x11State.display, s_x11State.screenIndex),
    CWBackPixel | CWBorderPixel | CWWinGravity | CWEventMask |
    CWColormap,
    &windowAttributes
  );

  if (!window->window) { return 0; }
  XStoreName(s_x11State.display, window->window, createInfo->title);

  // Map window (needs to be done for window to be displayed)
  XMapWindow(s_x11State.display, window->window);

  return window;
}

void oplWindowDestroy(OplWindow window) {
  const _OplX11Window *x11Window = ((_OplX11Window*)window);

  XUnmapWindow(s_x11State.display, x11Window->window);
  XDestroyWindow(s_x11State.display, x11Window->window);

  oplFree(window);
}

uint8_t oplWindowShouldClose(OplWindow window) {
  return ((_OplX11Window*)window)->shouldClose;
}

void oplWindowSetTitle(OplWindow window, const char *title) {
  XStoreName(s_x11State.display, ((_OplX11Window*)window)->window, title);
}

const char* oplWindowGetTitle(OplWindow window) {
  char *title;
  XFetchName(s_x11State.display, ((_OplX11Window*)window)->window, &title);
  return title;
}

void oplWindowSetSize(OplWindow window, uint16_t width, uint16_t height) {
  XResizeWindow(s_x11State.display, ((_OplX11Window*)window)->window,
                width, height);
}

void oplWindowGetSize(OplWindow window, uint16_t *width, uint16_t *height) {
  const _OplX11Window *x11Window = ((_OplX11Window*)window);

  XWindowAttributes windowAttributes;
  XGetWindowAttributes(s_x11State.display, x11Window->window, &windowAttributes);
  *width = windowAttributes.width;
  *height = windowAttributes.height;
}

void oplWindowSetPosition(OplWindow window, uint16_t x, uint16_t y) {
  XMoveWindow(s_x11State.display, ((_OplX11Window*)window)->window, x, y);
}

void oplWindowGetPosition(OplWindow window, uint16_t *x, uint16_t *y) {
  const _OplX11Window *x11Window = ((_OplX11Window*)window);

  XWindowAttributes windowAttributes;
  XGetWindowAttributes(s_x11State.display, x11Window->window, &windowAttributes);
  *x = windowAttributes.x;
  *y = windowAttributes.y;
}

void oplWindowMiniaturize(OplWindow window) {
  XIconifyWindow(s_x11State.display, ((_OplX11Window*)window)->window, s_x11State.screenIndex);
}

uint8_t oplWindowIsMinituarized(OplWindow window) {
  #warning "oplWindowIsMinituarized(): not implemented"
  return OPL_FALSE;
}

void oplWindowMaximize(OplWindow window) {
  #warning "oplWindowMaximize(): not implemented"
}

uint8_t oplWindowIsMaximized(OplWindow window) {
  #warning "oplWindowIsMaximized(): not implemented"
  return OPL_FALSE;
}

void oplWindowToggleFullscreen(OplWindow window) {
  #warning "oplWindowToggleFullscreen(): not implemented"
}

uint8_t oplWindowIsFullscreen(OplWindow window) {
  #warning "oplWindowIsFullscreen(): not implemented"
}

void oplConsoleWrite(const char *message, OplColor color) {
  // none, trace, info, warn, error, fatal
  static const char* clrStrings[] = { "0", "1;30", "1;32", "1;33", "1;31", "0;41", };
  printf("\033[%sm%s\033[0m", clrStrings[color], message);
}

VkResult oplCreateSurface(
  OplWindow window, VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface) {

  const VkXlibSurfaceCreateInfoKHR info = {
    .sType  = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
    .pNext  = 0,
    .flags  = 0,
    .window = ((_OplX11Window*)window)->window,
    .dpy    = s_x11State.display,
  };

  return vkCreateXlibSurfaceKHR(
    instance, &info, allocator, surface);
}

void oplGetDeviceExtensions(
  uint16_t *extensionsCount, const char* *extensionNames) {
  if (extensionNames) {
    extensionNames[0] = "VK_KHR_xlib_surface";
    extensionNames[1] = "VK_KHR_surface";
  }

  *extensionsCount = 2;
}
