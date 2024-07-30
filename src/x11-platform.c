#include <stdio.h>
#include <string.h>

#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib-xcb.h>
#include <xcb/xproto.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xcb.h>

#include "opl/opl.h"
#include "internal.h"

struct {
  Display *display;
  xcb_connection_t *connection;
  xcb_window_t window;
  xcb_screen_t *screen;
  xcb_atom_t wmProtocols;
  xcb_atom_t wmDelete;

  _OplState *oplState;
} s_platformState;

uint8_t _oplPlatformInit(const OplInitInfo *initInfo, _OplState *oplState) {
  s_platformState.oplState = oplState;

  s_platformState.display = XOpenDisplay(0);

  // Turn off key repeats
  XAutoRepeatOff(s_platformState.display);

  // Retrieve the connection from the display
  s_platformState.connection = XGetXCBConnection(s_platformState.display);
  if (xcb_connection_has_error(s_platformState.connection)) {
    return OPL_FALSE;
  }

  // Get data from the X server
  const struct xcb_setup_t *setup = xcb_get_setup(s_platformState.connection);

  // Loop through screens using iterator
  // Don't ask me please, what's going on here...
  // I don't know and don't really care about all this
  // platfrom setup stuff for fucking window creation!
  xcb_screen_iterator_t screenIt = xcb_setup_roots_iterator(setup);
  int32_t screenP = 0;
  for (uint32_t i = screenP; i > 0; --i) {
    xcb_screen_next(&screenIt);
  }

  // After screen have been looped through, assign it
  s_platformState.screen = screenIt.data;

  // Allocate a XID for the window to be created
  s_platformState.window = xcb_generate_id(s_platformState.connection);

  // Registiring types of events we wanna listen to
  uint32_t eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  uint32_t eventsToListen =
    XCB_EVENT_MASK_BUTTON_PRESS    |
    XCB_EVENT_MASK_BUTTON_RELEASE  |
    XCB_EVENT_MASK_KEY_PRESS       |
    XCB_EVENT_MASK_KEY_RELEASE     |
    XCB_EVENT_MASK_EXPOSURE        | // maximizing, minimizing window
    XCB_EVENT_MASK_POINTER_MOTION  |
    XCB_EVENT_MASK_STRUCTURE_NOTIFY; // close request

  // Values to be sent over XCB
  uint32_t valueList[] = {s_platformState.screen->black_pixel, eventsToListen};

  // Create the window (finally :>)
  xcb_void_cookie_t cookie = xcb_create_window(
    s_platformState.connection,
    XCB_COPY_FROM_PARENT,           // depth
    s_platformState.window,
    s_platformState.screen->root,
    0, 0,                           // x and y window position
    initInfo->surfaceWidth,
    initInfo->surfaceHeight,
    0,                              // border widht
    XCB_WINDOW_CLASS_INPUT_OUTPUT,
    s_platformState.screen->root_visual,
    eventMask,
    valueList
  );

  // Set window title
  xcb_change_property(
    s_platformState.connection,
    XCB_PROP_MODE_REPLACE,
    s_platformState.window,
    XCB_ATOM_WM_NAME,
    XCB_ATOM_STRING,
    8, // param name says format, but basicly it's a stride
    strlen(initInfo->applicationName),
    initInfo->applicationName
  );

  // Tell the server to notify when the window manager
  // is trying to destroy the window
  xcb_intern_atom_cookie_t wmDeleteCookie =
    xcb_intern_atom(
      s_platformState.connection,
      0,
      16, // = strlen("WM_DELETE_WINDOW")
      "WM_DELETE_WINDOW"
    );

  xcb_intern_atom_cookie_t wmProtocolsCookie = 
    xcb_intern_atom(
      s_platformState.connection,
      0,
      12, // = strlen("WM_PROTOCOLS")
      "WM_PROTOCOLS"
    );

  xcb_intern_atom_reply_t *wmDeleteReply = 
    xcb_intern_atom_reply(
      s_platformState.connection,
      wmDeleteCookie,
      0
    );

  xcb_intern_atom_reply_t *wmProtocolsReply =
    xcb_intern_atom_reply(
      s_platformState.connection,
      wmProtocolsCookie,
      0
    );

  s_platformState.wmDelete = wmDeleteReply->atom;
  s_platformState.wmProtocols = wmProtocolsReply->atom;

  xcb_change_property(
    s_platformState.connection,
    XCB_PROP_MODE_REPLACE,
    s_platformState.window,
    wmProtocolsReply->atom,
    4, 32, 1, // I don't even trying to understand,
              // what this numbers means
    &wmDeleteReply->atom
  );

  // Map the window to the screen
  xcb_map_window(s_platformState.connection, s_platformState.window);

  // Flush the screen
  int32_t streamResult = xcb_flush(s_platformState.connection);
  if (streamResult <= 0) {
    return OPL_FALSE;
  }

  return OPL_TRUE;
}

void _oplPlatformTerminate(){
  // Turn on key repeats
  XAutoRepeatOn(s_platformState.display);

  xcb_destroy_window(s_platformState.connection, s_platformState.window);
}

void oplPumpMessages() {
  xcb_generic_event_t *event;
  xcb_client_message_event_t *clientMessage;

  uint8_t quitFlagged = OPL_FALSE;

  while (1) {
    // caution! this shit is dynamicly allocated and we have to free it
    event = xcb_poll_for_event(s_platformState.connection);
    if (!event) { break; }

    switch (event->response_type & ~0x80) { // WTF!?
      case XCB_KEY_PRESS:
      case XCB_KEY_RELEASE:
        break;
      case XCB_BUTTON_PRESS:
      case XCB_BUTTON_RELEASE:
        break;
      case XCB_MOTION_NOTIFY: // mouse movement
        break;
      case XCB_CONFIGURE_NOTIFY: // resizing
        break;
      case XCB_CLIENT_MESSAGE:
        clientMessage = (xcb_client_message_event_t*)event;

        // Window close
        if (clientMessage->data.data32[0] == s_platformState.wmDelete) {
          s_platformState.oplState->terminateRequsted = OPL_TRUE;
        }
        break;
      default: { }
    }

    oplFree(event);
  }
}

void oplConsoleWrite(const char *pMessage, OplColor color) {
  // none, trace, info, warn, error, fatal
  const char* clrStrings[] = { "0", "1;30", "1;32", "1;33", "1;31", "0;41", };
  printf("\033[%sm%s\033[0m", clrStrings[color], pMessage);
}

VkResult oplCreateVkSurface(
  VkInstance instance, const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface) {

  VkXcbSurfaceCreateInfoKHR info = {
    .sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT,
    .pNext = 0,
    .flags = 0,
    .connection = s_platformState.connection,
    .window = s_platformState.window,
  };

  return vkCreateXcbSurfaceKHR(instance, &info,
                               allocator, surface);
}

uint16_t oplVkExtensions(const char* *extensionNames) {
  if (extensionNames) {
    extensionNames[0] = "VK_KHR_xcb_surface";
    extensionNames[1] = "VK_KHR_surface";
  }
  return 2;
}

