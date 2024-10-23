#include <stdlib.h>

#include <windows.h>
#include <windowsx.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include "opl.h"

#define WINDOW_CLASS_NAME               "opl window class"
#define WINDOW_PROPERTY_NAME_OPL_WINDOW "opl window handle"

struct opl_window {
  LONG should_close;
  HWND window;
};

static struct {
  int             initialized;
  HMODULE         h_instance;
  WNDCLASSA       window_class;
  opl_input_state input_state;
} s_opl_state;

LRESULT CALLBACK window_process_msg(
  HWND   hwnd,
  UINT   umsg,
  WPARAM wparam,
  LPARAM lparam
) {
  switch (umsg) {
    case WM_ERASEBKGND:
      // Notify the OS that erasing will be handled by the application
      return 1;
    case WM_CLOSE:
      struct opl_window *window = GetProp(
        hwnd, WINDOW_PROPERTY_NAME_OPL_WINDOW);
      window->should_close = 1;
      break;
    case WM_SIZE:
      break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      s_opl_state.input_state.keys[wparam] = 1;
      break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
      s_opl_state.input_state.keys[wparam] = 0;
      break;
    case WM_MOUSEMOVE:
      s_opl_state.input_state.x = GET_X_LPARAM(lparam);
      s_opl_state.input_state.y = GET_Y_LPARAM(lparam);
      break;
    case WM_MOUSEWHEEL:
      s_opl_state.input_state.wheel = GET_WHEEL_DELTA_WPARAM(wparam);
      break;
    case WM_LBUTTONDOWN:
      s_opl_state.input_state.btns[OPL_BTN_LEFT] = 1;
      break;
    case WM_LBUTTONUP:
      s_opl_state.input_state.btns[OPL_BTN_LEFT] = 0;
      break;
    case WM_RBUTTONDOWN:
      s_opl_state.input_state.btns[OPL_BTN_RIGHT] = 1;
      break;
    case WM_RBUTTONUP:
      s_opl_state.input_state.btns[OPL_BTN_RIGHT] = 0;
      break;
    case WM_MBUTTONDOWN:
      s_opl_state.input_state.btns[OPL_BTN_MIDDLE] = 1;
      break;
    case WM_MBUTTONUP:
      s_opl_state.input_state.btns[OPL_BTN_MIDDLE] = 0;
      break;
    default:
      return DefWindowProc(hwnd, umsg, wparam, lparam);
  }

  return 0;
}

int opl_init(void)
{
  if (s_opl_state.initialized) { return 1; }

  // Saving a handle to currenty running application
  s_opl_state.h_instance = GetModuleHandle(0);

  // Register window class
  WNDCLASSA window_class = {
    .style         = CS_DBLCLKS, // Get double clicks
    .lpfnWndProc   = window_process_msg,
    .cbClsExtra    = 0,
    .cbWndExtra    = 0,
    .hInstance     = s_opl_state.h_instance,
    .hIcon         = LoadIconA(s_opl_state.h_instance, IDI_APPLICATION),
    .hCursor       = LoadCursorA(0, IDC_ARROW),
    .hbrBackground = 0,
    .lpszClassName = WINDOW_CLASS_NAME,
    .lpszMenuName  = "",
  };

  if(!RegisterClass(&window_class)) { return 0; }

  s_opl_state.initialized = 1;

  return 1;
}

void opl_quit(void)
{
  if (!s_opl_state.initialized) { return; }

  s_opl_state.initialized = 0;
}

void opl_update(void)
{
  MSG message;
  while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}

opl_window opl_open(
  int              width,
  int              height,
  const char      *title,
  int              x,
  int              y,
  opl_window_hint  hints
) {
  struct opl_window *window = malloc(sizeof(struct opl_window));
  window->should_close = 0;

  // Window style
  DWORD window_style = WS_SYSMENU;

  if (!(hints & OPL_WINDOW_HINT_TITLED_BIT))
    window_style |= WS_POPUP | WS_BORDER;

  if (hints & OPL_WINDOW_HINT_RESIZABLE_BIT)
    window_style |= WS_MAXIMIZEBOX | WS_SIZEBOX;

  if (hints & OPL_WINDOW_HINT_MINIATURIZABLE_BIT)
    window_style |= WS_MINIMIZEBOX | WS_CAPTION;

  // Window style extended
  DWORD window_style_ex = 0;

  // Calculating actual window size
  RECT rect = { 0, 0, 0, 0 };
  AdjustWindowRectEx(&rect, window_style, 0, window_style_ex);

  window->window = CreateWindowEx(
    window_style_ex,
    WINDOW_CLASS_NAME,
    title,
    window_style,
    x == OPL_CENTER ? CW_USEDEFAULT : x,
    y == OPL_CENTER ? CW_USEDEFAULT : y,
    // Grow by the size of the window frame border
    width + rect.right - rect.left,
    height + rect.bottom - rect.top,
    0,
    0,
    s_opl_state.h_instance,
    0
  );

  if (!window->window) {
    free(window);
    return NULL;
  }

  if (!(hints & OPL_WINDOW_HINT_CLOSABLE_BIT))
    EnableMenuItem(GetSystemMenu(window->window, FALSE), SC_CLOSE,
                   MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

  // Ad property to hold a pointer to OPL window handle
  SetProp(window->window, WINDOW_PROPERTY_NAME_OPL_WINDOW, window);

  // Showing window
  int cmd_flags =
    (hints & OPL_WINDOW_HINT_FULLSCREEN_BIT) ? SW_SHOWMAXIMIZED : SW_SHOW;
  ShowWindow(window->window, cmd_flags);

  return window;
}

void opl_close(struct opl_window *window)
{
  DestroyWindow(window->window);
  free(window);
}

int opl_should_close(struct opl_window *window)
{
  return window->should_close;
}

void opl_set_title(
  struct opl_window *window,
  const char        *title
) { }

const char* opl_get_title(struct opl_window *window) { }

void opl_set_size(
  struct opl_window *window,
  int                width,
  int                height
) { }

opl_size opl_get_size(struct opl_window *window) { }

void opl_set_pos(
  struct opl_window *window,
  int                x,
  int                y
) { }

opl_pos opl_window_get_pos(struct opl_window *window) { }

void opl_hide(struct opl_window *window) { }

int opl_is_hidden(struct opl_window *window) { }

void opl_show(struct opl_window *window) { }

int opl_is_shown(struct opl_window *window) { }

void opl_toggle_fullscreen(struct opl_window *window) { }

int opl_is_fullscreen(struct opl_window *window) { }

int opl_alert(
  const char *title,
  const char *text
) {
  opl_alert_ext(title, text, OPL_ALERT_STYLE_ERROR, 0, 0);
}

int opl_alert_ext(
  const char      *title,
  const char      *text,
  opl_alert_style  style,
  int              btn_count,
  const char*     *btn_titles
) {
  return MessageBox(NULL, text, title, MB_OK);
}


const opl_input_state* opl_get_input_state(void)
{
  return &s_opl_state.input_state;
}

VkResult opl_vk_surface_create(
  opl_window                  window,
  VkInstance                  instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR                *surface
) {
  VkWin32SurfaceCreateInfoKHR info = {
    .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
    .pNext = 0,
    .flags = 0,
    .hinstance = s_opl_state.h_instance,
    .hwnd = window->window,
  };

  return vkCreateWin32SurfaceKHR(instance, &info, allocator, surface);
}

void opl_vk_device_extensions(
  uint16_t *extensionsCount, const char* *extensionNames) {
  if (extensionNames) {
    extensionNames[0] = "VK_EXT_win32_surface";
    extensionNames[1] = "VK_KHR_surface";
  }

  *extensionsCount = 2;
}

