#include <windows.h>
#include <windowsx.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include "opl/opl.h"

#define WINDOW_CLASS_NAME "OPL window class"
#define WINDOW_PROPERTY_NAME_OPL_WINDOW "OPL window handle"

typedef struct _OplWin32Window {
  LONG shouldClose;
  HWND window;
} _OplWin32Window;

static struct {
  uint8_t initialized;

  HMODULE hInstance;
  WNDCLASSA windowClass;

  OplMouseState mouseState;
  OplKeyboardState keyboardState;
} s_win32State = { .initialized = OPL_FALSE };

LRESULT CALLBACK windowProcessMessage(
  HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_ERASEBKGND:
      // Notify the OS that erasing will be handled by the application
      return 1;
    case WM_CLOSE:
      _OplWin32Window *window = GetProp(hWnd, WINDOW_PROPERTY_NAME_OPL_WINDOW);
      window->shouldClose = OPL_TRUE;
      break;
    case WM_SIZE:
      break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      s_win32State.keyboardState.keys[wParam] = 1;
      break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
      s_win32State.keyboardState.keys[wParam] = 0;
      break;
    case WM_MOUSEMOVE:
      s_win32State.mouseState.x = GET_X_LPARAM(lParam);
      s_win32State.mouseState.y = GET_Y_LPARAM(lParam);
      break;
    case WM_MOUSEWHEEL:
      int32_t wheel = GET_WHEEL_DELTA_WPARAM(wParam);
      s_win32State.mouseState.wheel = wheel > 0 ? 1 : -1;
      break;
    case WM_LBUTTONDOWN:
      s_win32State.mouseState.buttons[OPL_MOUSE_BUTTON_LEFT] = 1;
      break;
    case WM_LBUTTONUP:
      s_win32State.mouseState.buttons[OPL_MOUSE_BUTTON_LEFT] = 0;
      break;
    case WM_RBUTTONDOWN:
      s_win32State.mouseState.buttons[OPL_MOUSE_BUTTON_RIGHT] = 1;
      break;
    case WM_RBUTTONUP:
      s_win32State.mouseState.buttons[OPL_MOUSE_BUTTON_RIGHT] = 0;
      break;
    case WM_MBUTTONDOWN:
      s_win32State.mouseState.buttons[OPL_MOUSE_BUTTON_MIDDLE] = 1;
      break;
    case WM_MBUTTONUP:
      s_win32State.mouseState.buttons[OPL_MOUSE_BUTTON_MIDDLE] = 0;
      break;
    default:
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return 0;
}

uint8_t oplInit() {
  if (s_win32State.initialized) { return OPL_TRUE; }

  // Saving a handle to currenty running application
  s_win32State.hInstance = GetModuleHandle(0);

  // Register window class
  WNDCLASSA windowClass = {
    .style         = CS_DBLCLKS, // Get double clicks (i dunno what that means...)
    .lpfnWndProc   = windowProcessMessage,
    .cbClsExtra    = 0,
    .cbWndExtra    = 0,
    .hInstance     = s_win32State.hInstance,
    .hIcon         = LoadIconA(s_win32State.hInstance, IDI_APPLICATION),
    .hCursor       = LoadCursorA(0, IDC_ARROW),
    .hbrBackground = 0,
    .lpszClassName = WINDOW_CLASS_NAME,
    .lpszMenuName  = "",
  };
  if(!RegisterClass(&windowClass)) { return OPL_FALSE; }

  return OPL_TRUE;
}

void oplTerminate() {
  if (!s_win32State.initialized) { return; }

  s_win32State.initialized = OPL_FALSE;
}

void oplPumpMessages() {
  MSG message;
  while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}

const OplKeyboardState* oplKeyboardGetState() {
  return &s_win32State.keyboardState;
}

const OplMouseState* oplMouseGetState() {
  return &s_win32State.mouseState;
}

OplWindow oplWindowCreate(const OplWindowCreateInfo *createInfo) {
  _OplWin32Window *window = oplAlloc(sizeof(_OplWin32Window));
  window->shouldClose = OPL_FALSE;

  #warning "Not all OplWindowStyleFlag flags are used."

  // Window style
  DWORD windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_THICKFRAME;
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_RESIZABLE) {
    windowStyle |= WS_MAXIMIZEBOX;
  }
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_MINIATURIZABLE) {
    windowStyle |= WS_MINIMIZEBOX;
  }

  // Window style extended
  DWORD windowStyleEx = WS_EX_APPWINDOW;

  // Calculating actual window size
  RECT windowRect = { 0, 0, 0, 0 };
  AdjustWindowRectEx(&windowRect, windowStyle, 0, windowStyleEx);

  window->window = CreateWindowEx(
    windowStyleEx,
    WINDOW_CLASS_NAME,
    createInfo->title,
    windowStyle,
    createInfo->x,
    createInfo->y,
    // Grow by the size of the window frame border
    createInfo->width + windowRect.right - windowRect.left,
    createInfo->height + windowRect.bottom - windowRect.top,
    0,
    0,
    s_win32State.hInstance,
    0
  );

  if (!window->window) {
    oplFree(window);
    return 0;
  }
  
  // Ad property to hold a pointer to OPL window handle
  SetProp(window->window, WINDOW_PROPERTY_NAME_OPL_WINDOW, window);

  // Showing window
  int commandFlags = 
    (createInfo->styleFlags * OPL_WINDOW_STYLE_FULLSCREEN) ?
      SW_SHOWMAXIMIZED : SW_SHOW;
  ShowWindow(window->window, commandFlags);

  return window;
}

void oplWindowDestroy(OplWindow window) {
  const _OplWin32Window *win32Window = (_OplWin32Window*)window;
  DestroyWindow(win32Window->window);
  oplFree(window);
}

uint8_t oplWindowShouldClose(OplWindow window) {
  return ((_OplWin32Window*)window)->shouldClose;
}

void oplWindowSetTitle(OplWindow window, const char *title) {
  #warning "oplWindowSetTitle() not implemented."
}

const char* oplWindowGetTitle(OplWindow window) {
  #warning "oplWindowGetTitle() not implemented.";
}

void oplWindowSetSize(OplWindow window, uint16_t width, uint16_t height) {
  #warning "oplWindowSetSize() not implemented.";
}

void oplWindowGetSize(OplWindow window, uint16_t *width, uint16_t *height) {
  #warning "oplWindowGetSize() not implemented.";
}

void oplWindowSetPosition(OplWindow window, uint16_t x, uint16_t y) {
  #warning "oplWindowSetPosition() not implemented.";
}

void oplWindowGetPosition(OplWindow window, uint16_t *x, uint16_t *y) {
  #warning "oplWindowGetPosition() not implemented.";
}

void oplWindowMiniaturize(OplWindow window) {
  #warning "oplWindowMiniaturize() not implemented.";
}

uint8_t oplWindowIsMinituarized(OplWindow window) {
  #warning "oplWindowIsMinituarized() not implemented.";
}

void oplWindowMaximize(OplWindow window) {
  #warning "oplWindowMaximize() not implemented.";
}

uint8_t oplWindowIsMaximized(OplWindow window) {
  #warning "oplWindowIsMaximized() not implemented.";
}

void oplWindowToggleFullscreen(OplWindow window) {
  #warning "oplWindowToggleFullscreen() not implented.";
}

uint8_t oplWindowIsFullscreen(OplWindow window) {
  #warning "oplWindowIsFullscreen() not implemented.";
}

void oplConsoleWrite(const char *message, OplColor color) {
  // Saving a handle to console
  const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  // NORMAL, TRACE, INFO, WARN, ERROR, FATAL
  static const uint8_t colors[] = { 0, 8, 1, 2, 6, 64 };
  SetConsoleTextAttribute(consoleHandle, colors[color]);

  uint64_t length = strlen(message);
  DWORD numberWritten = 0;
  WriteConsole(consoleHandle, message, length, &numberWritten, 0);
  OutputDebugString(message);
}

VkResult oplCreateSurface(
  OplWindow window, VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface) {

  VkWin32SurfaceCreateInfoKHR info = {
    .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
    .pNext = 0,
    .flags = 0,
    .hinstance = s_win32State.hInstance,
    .hwnd = ((_OplWin32Window*)window)->window,
  };

  return vkCreateWin32SurfaceKHR(instance, &info,
                                 allocator, surface);
}

void oplGetDeviceExtensions(
  uint16_t *extensionsCount, const char* *extensionNames) {
  if (extensionNames) {
    extensionNames[0] = "VK_EXT_win32_surface";
    extensionNames[1] = "VK_KHR_surface";
  }

  *extensionsCount = 2;
}

