#include <stdlib.h>
#include <limits.h>

#include <X11/Xmd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

#define OPL_INCLUDE_VULKAN
#include "opl.h"


#define _NET_WM_STATE_REMOVE        0	/* remove/unset property */
#define _NET_WM_STATE_ADD           1	/* add/set property */

struct opl_window {
  Window  window;
  int     should_close;
};

static struct {
  Display *display;
  int      screen_ind;
  Screen  *screen;
  Window   root_window;

  Atom     wm_state;
  Atom     net_wm_state;
  Atom     wm_state_fullscreen;

  opl_mouse_state_t    mouse_state;
  opl_keyboard_state_t keyboard_state;
} s_opl_state;


static unsigned long _get_window_prop(Window window,
                                        Atom property,
                                        Atom type,
                                        unsigned char** value)
{
    Atom actualType;
    int actualFormat;
    unsigned long itemCount, bytesAfter;

    XGetWindowProperty(s_opl_state.display,
                       window,
                       property,
                       0,
                       LONG_MAX,
                       False,
                       type,
                       &actualType,
                       &actualFormat,
                       &itemCount,
                       &bytesAfter,
                       value);

    return itemCount;
}



static int _get_window_state(struct opl_window* window)
{
    int result = WithdrawnState;
    struct {
        CARD32 state;
        Window icon;
    } *state = NULL;

    if (_get_window_prop(window->window,
                                  s_opl_state.wm_state,
                                  s_opl_state.wm_state,
                                  (unsigned char**) &state))
    {
        result = state->state;
    }

    if (state)
        XFree(state);

    return result;
}


static void _send_event_to_wm(
  struct opl_window* window, Atom type,
  long a, long b, long c, long d, long e
) {
  XEvent event = { ClientMessage };
  event.xclient.window = window->window;
  event.xclient.format = 32; // Data is 32-bit longs
  event.xclient.message_type = type;
  event.xclient.data.l[0] = a;
  event.xclient.data.l[1] = b;
  event.xclient.data.l[2] = c;
  event.xclient.data.l[3] = d;
  event.xclient.data.l[4] = e;

  XSendEvent(
    s_opl_state.display, s_opl_state.root_window,
    False,
    SubstructureNotifyMask | SubstructureRedirectMask,
    &event
  );
}


int opl_init(void) {
  s_opl_state.display = XOpenDisplay(0);
  if (!s_opl_state.display) { return 0; }

  // Get default screen and root window
  s_opl_state.screen_ind  = XDefaultScreen(s_opl_state.display);
  s_opl_state.root_window = RootWindow(
    s_opl_state.display,
    s_opl_state.screen_ind
  );

  s_opl_state.screen = XScreenOfDisplay(
    s_opl_state.display,
    s_opl_state.screen_ind
  );

  s_opl_state.wm_state = XInternAtom(
    s_opl_state.display, "WM_STATE", True
  );

  s_opl_state.new_wm_state = XInternAtom (
    s_opl_state.display, "_NET_WM_STATE", True
  );

  s_opl_state.wm_fullscreen = XInternAtom (
    s_opl_state.display, "_NET_WM_STATE_FULLSCREEN", True
  );

  return 1;
}

void opl_quit(void) {
  XCloseDisplay(s_opl_state.display);
}

void opl_update(void) {
  XEvent event;

  while (XPending(s_opl_state.display)) {
    XNextEvent(s_opl_state.display, &event);
    switch (event.type) {
      case KeyPress:
        s_opl_state.keyboard_state.keys[event.xkey.keycode] = 1;
        break;
      case KeyRelease:
        s_opl_state.keyboard_state.keys[event.xkey.keycode] = 0;
        break;
      case ButtonPress:
        s_opl_state.mouse_state.btns[event.xbutton.button] = 1;
        break;
      case ButtonRelease:
        s_opl_state.mouse_state.btns[event.xbutton.button] = 0;
        break;
      case MotionNotify:
        s_opl_state.mouse_state.x = event.xbutton.x;
        s_opl_state.mouse_state.y = event.xbutton.y;
        break;
      case Expose:
        break;
    }
  }

  
}

struct opl_window *opl_window_open(int width, int height, const char *title) {
  return opl_window_open_ext(
    width,
    height,
    title,
    WidthOfScreen(s_opl_state.screen) / 2,
    HeightOfScreen(s_opl_state.screen) / 2,
    0
  );
}

struct opl_window *opl_window_open_ext(
  int width,
  int height,
  const char *title,
  int x,
  int y,
  opl_window_hint_t hints
) {
  struct opl_window *window = malloc(sizeof(struct opl_window));
  window->should_close = 0;

  (void)(hints);
  // #warning "OPL window style flags aren't used"

  XSetWindowAttributes attrs = {
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
    .colormap              = DefaultColormap(s_opl_state.display,
                                             s_opl_state.screen_ind),
    .cursor                = None,
  };

  window->window = XCreateWindow(
    s_opl_state.display,
    s_opl_state.root_window,
    0,
    0,
    width,
    height,
    1, // Border size
    DefaultDepth(s_opl_state.display, s_opl_state.screen_ind),
    InputOutput,
    DefaultVisual(s_opl_state.display, s_opl_state.screen_ind),
    CWBackPixel | CWBorderPixel | CWWinGravity |
    CWEventMask | CWColormap,
    &attrs
  );

  if (!window->window) { return 0; }
  XStoreName(s_opl_state.display, window->window, title);

  // Map window (needs to be done for window to be displayed)
  XMapWindow(s_opl_state.display, window->window);

  XMoveWindow(
    s_opl_state.display,
    window->window,
    x - width / 2,
    y - height / 2
  );

  return window;
}

void opl_window_close(struct opl_window *window) {
  XUnmapWindow(s_opl_state.display, window->window);
  XDestroyWindow(s_opl_state.display, window->window);
  free(window);
}

int opl_window_should_close(struct opl_window *window) {
  return window->should_close;
}

void opl_window_set_title(struct opl_window *window, const char *title) {
  XStoreName(s_opl_state.display, window->window, title);
}

const char* opl_window_get_title(struct opl_window *window) {
  char *title;
  XFetchName(s_opl_state.display, window->window, &title);
  return title;
}

void opl_window_set_size(struct opl_window *window, int width, int height) {
  XResizeWindow(s_opl_state.display, window->window, width, height);
}

void opl_window_get_size(struct opl_window *window, int *width, int *height) {
  XWindowAttributes attrs;
  XGetWindowAttributes(s_opl_state.display, window->window, &attrs);
  *width  = attrs.width;
  *height = attrs.height;
}

void opl_window_set_pos(struct opl_window *window, int x, int y) {
  XMoveWindow(s_opl_state.display, window->window, x, y);
}

void opl_window_get_pos(struct opl_window *window, int *x, int *y) {
  XWindowAttributes attrs;
  XGetWindowAttributes(s_opl_state.display, window->window, &attrs);
  *x = attrs.x;
  *y = attrs.y;
}

void opl_hide(struct opl_window *window) {
  XIconifyWindow(
    s_opl_state.display,
    window->window,
    s_opl_state.screen_ind
  );
}

int opl_is_hidden(struct opl_window *window) {
  return _get_window_state(window ) == IconicState;
}

void opl_show(struct opl_window *window) {
  XWithdrawWindow(
    s_opl_state.display,
    window->window,
    s_opl_state.screen_ind
  );
}

int opl_is_shown(struct opl_window *window) {
  int state =  _get_window_state(window );
  return state == NormalState || state == WithdrawnState;
}

void opl_toggle_fullscreen(struct opl_window *window) {
  //(void)(state);
  _send_event_to_wm(
    window,
    s_opl_state.net_wm_state,
    _NET_WM_STATE_TOGGLE,
    s_opl_state.wm_fullscreen,
    0, 1, 0
  );
}

int opl_is_fullscreen(struct opl_window *window) {
  (void)(window);
  return 0;
}

int opl_alert_ext(
  const char *title,
  const char *text,
  opl_alert_style_t style,
  int btn_count,
  const char **btn_titles
) {
  (void)(title);
  (void)(text);
  (void)(style);
  (void)(btn_count);
  (void)(btn_titles);
  return 1;
}

const opl_keyboard_state_t* opl_keyboard_get_state(void) {
  return &s_opl_state.keyboard_state;
}

const opl_mouse_state_t* opl_mouse_get_state(void) {
  return &s_opl_state.mouse_state;
}

VkResult opl_vk_surface_create(
  struct opl_window *window,
  VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface
) {
  const VkXlibSurfaceCreateInfoKHR info = {
    .sType  = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
    .pNext  = 0,
    .flags  = 0,
    .window = window->window,
    .dpy    = s_opl_state.display,
  };

  return vkCreateXlibSurfaceKHR(instance, &info, allocator, surface);
}

void opl_vk_device_extensions(
  int *extensionsCount, const char* *extensionNames) {
  if (extensionNames) {
    extensionNames[0] = "VK_KHR_xlib_surface";
    extensionNames[1] = "VK_KHR_surface";
  }

  *extensionsCount = 2;
}



