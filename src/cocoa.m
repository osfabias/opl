#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_metal.h>

#define OE_INCLUDE_VULKAN
#include "opl.h"

@class ContentView;
@class WindowDelegate;
@class ApplicationDelegate;

struct opl_window {
  NSWindow        *window;
  ContentView     *view;
  WindowDelegate  *delegate;
  CAMetalLayer    *metal_layer;
  int              should_close;
};

struct {
  ApplicationDelegate *app_delegate;
  opl_mouse_state_t    mouse_state;
  opl_keyboard_state_t keyboard_staet;
} s_opl_state;

static opl_key_t _translate_key(uint32_t keycode) {
  // https://boredzo.org/blog/wp-content/uploads/2007/05/IMTx-virtual-keycodes.pdf
  // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
  switch (keycode) {
    case 0x52:
      return OPL_KEY_NUMPAD0;
    case 0x53:
      return OPL_KEY_NUMPAD1;
    case 0x54:
      return OPL_KEY_NUMPAD2;
    case 0x55:
      return OPL_KEY_NUMPAD3;
    case 0x56:
      return OPL_KEY_NUMPAD4;
    case 0x57:
      return OPL_KEY_NUMPAD5;
    case 0x58:
      return OPL_KEY_NUMPAD6;
    case 0x59:
      return OPL_KEY_NUMPAD7;
    case 0x5B:
      return OPL_KEY_NUMPAD8;
    case 0x5C:
      return OPL_KEY_NUMPAD9;

    case 0x12:
      return OPL_KEY_1;
    case 0x13:
      return OPL_KEY_2;
    case 0x14:
      return OPL_KEY_3;
    case 0x15:
      return OPL_KEY_4;
    case 0x17:
      return OPL_KEY_5;
    case 0x16:
      return OPL_KEY_6;
    case 0x1A:
      return OPL_KEY_7;
    case 0x1C:
      return OPL_KEY_8;
    case 0x19:
      return OPL_KEY_9;
    case 0x1D:
      return OPL_KEY_0;

    case 0x00:
      return OPL_KEY_A;
    case 0x0B:
      return OPL_KEY_B;
    case 0x08:
      return OPL_KEY_C;
    case 0x02:
      return OPL_KEY_D;
    case 0x0E:
      return OPL_KEY_E;
    case 0x03:
      return OPL_KEY_F;
    case 0x05:
      return OPL_KEY_G;
    case 0x04:
      return OPL_KEY_H;
    case 0x22:
      return OPL_KEY_I;
    case 0x26:
      return OPL_KEY_J;
    case 0x28:
      return OPL_KEY_K;
    case 0x25:
      return OPL_KEY_L;
    case 0x2E:
      return OPL_KEY_M;
    case 0x2D:
      return OPL_KEY_N;
    case 0x1F:
      return OPL_KEY_O;
    case 0x23:
      return OPL_KEY_P;
    case 0x0C:
      return OPL_KEY_Q;
    case 0x0F:
      return OPL_KEY_R;
    case 0x01:
      return OPL_KEY_S;
    case 0x11:
      return OPL_KEY_T;
    case 0x20:
      return OPL_KEY_U;
    case 0x09:
      return OPL_KEY_V;
    case 0x0D:
      return OPL_KEY_W;
    case 0x07:
      return OPL_KEY_X;
    case 0x10:
      return OPL_KEY_Y;
    case 0x06:
      return OPL_KEY_Z;

    case 0x27:
      return OPL_KEY_APOSTROPHE;
    case 0x2A:
      return OPL_KEY_BACKSLASH;
    case 0x2B:
      return OPL_KEY_COMMA;
    case 0x18:
      return OPL_KEY_EQUAL; // Equal/Plus
    case 0x32:
      return OPL_KEY_GRAVE;
    case 0x21:
      return OPL_KEY_LBRACKET;
    case 0x1B:
      return OPL_KEY_MINUS;
    case 0x2F:
      return OPL_KEY_PERIOD;
    case 0x1E:
      return OPL_KEY_RBRACKET;
    case 0x29:
      return OPL_KEY_SEMICOLON;
    case 0x2C:
      return OPL_KEY_SLASH;
    case 0x0A:
      return OPL_KEY_MAX_ENUM; // ?

    case 0x33:
      return OPL_KEY_BACKSPACE;
    case 0x39:
      return OPL_KEY_CAPSLOCK;
    case 0x75:
      return OPL_KEY_DELETE;
    case 0x7D:
      return OPL_KEY_DOWN;
    case 0x77:
      return OPL_KEY_END;
    case 0x24:
      return OPL_KEY_ENTER;
    case 0x35:
      return OPL_KEY_ESCAPE;
    case 0x7A:
      return OPL_KEY_F1;
    case 0x78:
      return OPL_KEY_F2;
    case 0x63:
      return OPL_KEY_F3;
    case 0x76:
      return OPL_KEY_F4;
    case 0x60:
      return OPL_KEY_F5;
    case 0x61:
      return OPL_KEY_F6;
    case 0x62:
      return OPL_KEY_F7;
    case 0x64:
      return OPL_KEY_F8;
    case 0x65:
      return OPL_KEY_F9;
    case 0x6D:
      return OPL_KEY_F10;
    case 0x67:
      return OPL_KEY_F11;
    case 0x6F:
      return OPL_KEY_F12;
    case 0x69:
      return OPL_KEY_PRINT;
    case 0x6B:
      return OPL_KEY_F14;
    case 0x71:
      return OPL_KEY_F15;
    case 0x6A:
      return OPL_KEY_F16;
    case 0x40:
      return OPL_KEY_F17;
    case 0x4F:
      return OPL_KEY_F18;
    case 0x50:
      return OPL_KEY_F19;
    case 0x5A:
      return OPL_KEY_F20;
    case 0x73:
      return OPL_KEY_HOME;
    case 0x72:
      return OPL_KEY_INSERT;
    case 0x7B:
      return OPL_KEY_LEFT;
    case 0x3A:
      return OPL_KEY_LALT;
    case 0x3B:
      return OPL_KEY_LCONTROL;
    case 0x38:
      return OPL_KEY_LSHIFT;
    case 0x37:
      return OPL_KEY_LSUPER;
    case 0x6E:
      return OPL_KEY_MAX_ENUM; // Menu
    case 0x47:
      return OPL_KEY_NUMLOCK;
    case 0x79:
      return OPL_KEY_PAGEDOWN;
    case 0x74:
      return OPL_KEY_PAGEUP;
    case 0x7C:
      return OPL_KEY_RIGHT;
    case 0x3C:
      return OPL_KEY_RSHIFT;
    case 0x36:
      return OPL_KEY_RSUPER;
    case 0x31:
      return OPL_KEY_SPACE;
    case 0x30:
      return OPL_KEY_TAB;
    case 0x7E:
      return OPL_KEY_UP;

    case 0x45:
      return OPL_KEY_ADD;
    case 0x41:
      return OPL_KEY_DECIMAL;
    case 0x4B:
      return OPL_KEY_DIVIDE;
    case 0x4C:
      return OPL_KEY_ENTER;
    case 0x51:
      return OPL_KEY_NUMPAD_EQUAL;
    case 0x43:
      return OPL_KEY_MULTIPLY;
    case 0x4E:
      return OPL_KEY_SUBTRACT;

    default:
      return OPL_KEY_MAX_ENUM;
  }
}

@interface WindowDelegate : NSObject <NSWindowDelegate> {
  struct opl_window *window;
}

- (instancetype)initWithOplWindow:(struct opl_window*)oplWindow;

@end // WindowDelegate

@implementation WindowDelegate

- (instancetype)initWithOplWindow:(struct opl_window*)oplWindow {
  self = [super init];
  if (self != nil) { window = oplWindow; }

  return self;
}

- (BOOL)windowShouldClose:(id)sender {
  window->should_close = 1;
  return YES;
}

@end // WindowDelegate

@interface ContentView : NSView <NSTextInputClient> {
  struct opl_window         *window;
  NSWindow                  *nsWindow;
  NSTrackingArea            *pRrackingArea;
  NSMutableAttributedString *pMarkedText;
}

- (instancetype)initWith:(struct opl_window*)oplWindow;

@end // ContentView

@implementation ContentView

- (instancetype)initWith:(struct opl_window*)oplWindow {
  self = [super init];
  if (self != nil) {
    window   = oplWindow;
    nsWindow = oplWindow->window;
  }

  return self;
}

- (BOOL)canBecomeKeyView {
  return YES;
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (BOOL)wantsUpdateLayer {
  return YES;
}

- (BOOL)acceptsFirstMouse:(NSEvent *)event {
  return YES;
}

- (void)mouseDown:(NSEvent *)event {
  s_opl_state.mouse_state.btns[OPL_MOUSE_BTN_LEFT] = 1;
}

- (void)mouseDragged:(NSEvent *)event {
  // Equivalent to moving the mouse for now
  [self mouseMoved:event];
}

- (void)mouseUp:(NSEvent *)event {
  s_opl_state.mouse_state.btns[OPL_MOUSE_BTN_LEFT] = 0;
}

- (void)mouseMoved:(NSEvent *)event {
  const NSPoint pos = [event locationInWindow];

  // Need to invert Y on macOS, since origin is bottom-left.
  // Also need to scale the mouse position by the device pixel
  // ratio so screen lookups are correct.
  NSSize window_size = window->metal_layer.drawableSize;
  s_opl_state.mouse_state.x =
    pos.x * window->metal_layer.contentsScale;

  s_opl_state.mouse_state.y =
    window_size.height - (pos.y * window->metal_layer.contentsScale);
}

- (void)rightMouseDown:(NSEvent *)event {
  s_opl_state.mouse_state.btns[OPL_MOUSE_BTN_RIGHT] = 1;
}

- (void)rightMouseDragged:(NSEvent *)event {
  // Equivalent to moving the mouse for now
  [self mouseMoved:event];
}

- (void)rightMouseUp:(NSEvent *)event {
  s_opl_state.mouse_state.btns[OPL_MOUSE_BTN_RIGHT] = 0;
}

- (void)otherMouseDown:(NSEvent *)event {
  // Interpreted as middle click
  s_opl_state.mouse_state.btns[OPL_MOUSE_BTN_MIDDLE] = 1;
}

- (void)otherMouseDragged:(NSEvent *)event {
  // Equivalent to moving the mouse for now
  [self mouseMoved:event];
}

- (void)otherMouseUp:(NSEvent *)event {
  // Interpreted as middle click
  s_opl_state.mouse_state.btns[OPL_MOUSE_BTN_MIDDLE] = 0;
}

- (void)keyDown:(NSEvent *)event {
  opl_key_t key = _translate_key((uint32_t)[event keyCode]);
  s_opl_state.keyboard_staet.keys[key] = 1;

  // [self interpretKeyEvents:@[event]];
}

- (void)keyUp:(NSEvent *)event {
  opl_key_t key = _translate_key((uint32_t)[event keyCode]);
  s_opl_state.keyboard_staet.keys[key] = 1;
}

- (void)scrollWheel:(NSEvent *)event {
  s_opl_state.mouse_state.wheel = ((int8_t)[event scrollingDeltaY]);
}

// If these methods not implemented - compiler generates warnings and
// program crashes on platform initialization
- (void)insertText:(id)string replacementRange:(NSRange)replacementRange {
}

- (void)setMarkedText:(id)string
        selectedRange:(NSRange)selectedRange
     replacementRange:(NSRange)replacementRange {
}

- (void)unmarkText {
}

// Defines a constant for empty ranges in NSTextInputClient
static const NSRange kEmptyRange = {NSNotFound, 0};

- (NSRange)selectedRange {
  return kEmptyRange;
}

- (NSRange)markedRange {
  return kEmptyRange;
}

- (BOOL)hasMarkedText {
  return false;
}

- (nullable NSMutableAttributedString *)
    attributedSubstringForProposedRange:(NSRange)range
                            actualRange:(nullable NSRangePointer)actualRange {
  return nil;
}

- (NSArray<NSAttributedStringKey> *)validAttributesForMarkedText {
  return [NSArray array];
}

- (NSRect)firstRectForCharacterRange:(NSRange)range
                         actualRange:(nullable NSRangePointer)actualRange {
  return NSMakeRect(0, 0, 0, 0);
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point {
  return 0;
}
@end // ContentView

@interface ApplicationDelegate : NSObject <NSApplicationDelegate> {
}

@end // ApplicationDelegate

@implementation ApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  // Posting an empty event at start
  @autoreleasepool {
    NSEvent *event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                        location:NSMakePoint(0, 0)
                                   modifierFlags:0
                                       timestamp:0
                                    windowNumber:0
                                         context:nil
                                         subtype:0
                                           data1:0
                                           data2:0];
    [NSApp postEvent:event atStart:YES];
  } // autoreleasepool

  [NSApp stop:nil];
}

@end // ApplicationDelegate

int opl_init(void) {
  // I don't know what this line stands for (o_O)
  [NSApplication sharedApplication];

  // App delegate creation
  s_opl_state.app_delegate = [[ApplicationDelegate alloc] init];
  if (!s_opl_state.app_delegate) {
    return false;
  }
  [NSApp setDelegate:s_opl_state.app_delegate];

  // Starting application
  if (![[NSRunningApplication currentApplication] isFinishedLaunching]) {
    [NSApp run];
  }

  // Making the app a proper UI app since we're unbundled
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  // Making it possible to create windows in front of others
  [NSApp activateIgnoringOtherApps:YES];

  // Make all windows created appear on top of others
  [[NSRunningApplication currentApplication] activateWithOptions:0];

  return true;
}

void opl_quit(void) {
  [NSApp setDelegate:nil];
  [s_opl_state.app_delegate release];
}

void opl_update(void) {
  @autoreleasepool {
    NSEvent *event;

    while (1) {
      event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                 untilDate:[NSDate distantPast]
                                    inMode:NSDefaultRunLoopMode
                                   dequeue:YES];
      if (!event) {
        break;
      }

      [NSApp sendEvent:event];
    }
  } // autoreleasepool
}

opl_window_t opl_window_open(int width, int height, const char *title) {
  return opl_window_open_ext(
    width,
    height,
    title,
    (NSScreen.mainScreen.frame.size.width - width) / 2,
    (NSScreen.mainScreen.frame.size.height - height) / 2,
    OPL_WINDOW_HINT_TITLED_BIT         |
    OPL_WINDOW_HINT_CLOSABLE_BIT       |
    OPL_WINDOW_HINT_MINIATURIZABLE_BIT
  );
}

opl_window_t opl_window_open_ext(
  int                width,
  int                height,
  const char        *title,
  int                x,
  int                y,
  opl_window_hint_t  hints
) {
  struct opl_window *window = malloc(sizeof(struct opl_window));
  window->should_close = 0;

  // Window delegate creation
  window->delegate = [[WindowDelegate alloc] initWithOplWindow:window];
  if (!window->delegate) {
    free(window);
    return 0;
  }

  // Window creation
  NSWindowStyleMask styleMask = 0;
  if (hints & OPL_WINDOW_HINT_TITLED_BIT) {
    styleMask |= NSWindowStyleMaskTitled;
  }
  if (hints & OPL_WINDOW_HINT_CLOSABLE_BIT) {
    styleMask |= NSWindowStyleMaskClosable;
  }
  if (hints & OPL_WINDOW_HINT_RESIZABLE_BIT) {
    styleMask |= NSWindowStyleMaskResizable;
  }
  if (hints & OPL_WINDOW_HINT_BORDERLESS_BIT) {
    styleMask |= NSWindowStyleMaskBorderless;
  }
  if (hints & OPL_WINDOW_HINT_MINIATURIZABLE_BIT) {
    styleMask |= NSWindowStyleMaskMiniaturizable;
  }

  window->window = [[NSWindow alloc]
      initWithContentRect:NSMakeRect(
                            x,
                            NSScreen.mainScreen.frame.size.height - height - y,
                            width,
                            height
                          )
                styleMask:styleMask
                  backing:NSBackingStoreBuffered
                    defer:NO];

  if (!window->window) {
    free(window);
    return 0;
  }

  if (hints & OPL_WINDOW_HINT_FULLSCREEN_BIT) {
    [window->window toggleFullScreen:nil];
  }

  // View creation
  window->view = [[ContentView alloc] initWith:window];
  [window->view setWantsLayer:YES];

  // Layer creation
  window->metal_layer = [CAMetalLayer layer];

  // Setting window properties
  [window->window setRestorable:NO];
  [window->window setContentView:window->view];
  [window->window setDelegate:window->delegate];
  [window->window setLevel:NSNormalWindowLevel];

  [window->window setTitle:[NSString stringWithCString:title
                                              encoding:NSASCIIStringEncoding]];
  [window->window setAcceptsMouseMovedEvents:YES];
  [window->window makeFirstResponder:window->view];

  // Putting window in front on launch
  [window->window makeKeyAndOrderFront:nil];

  // Handle content scaling for various fidelity displays (i.e. Retina)
  window->metal_layer.bounds = window->view.bounds;

  // It's important to set the drawableSize to the actual backing
  // pixels. When rendering full-screen, we can skip the macOS compositor
  // if the size matches the display size.
  window->metal_layer.drawableSize =
      [window->view convertSizeToBacking:window->view.bounds.size];

  // In its implementation of vkGetPhysicalDeviceSurfaceCapabilitiesKHR,
  // MoltenVK takes into consideration both the size (in points) of the
  // bounds, and the contentsScale of the CAMetalLayer from which the
  // Vulkan surface was created.
  // NOTE: See also https://github.com/KhronosGroup/MoltenVK/issues/428
  window->metal_layer.contentsScale = window->view.window.backingScaleFactor;

  // Set view's Metal layer
  [window->view setLayer:window->metal_layer];

  // This is set to NO by default, but is also important to ensure we
  // can bypass the compositor in full-screen mode
  // NOTE: See "Direct to Display"
  // http://metalkit.org/2017/06/30/introducing-metal-2.html.
  window->metal_layer.opaque = YES;

  return window;
}

void opl_window_close(struct opl_window *window) {
  [window->window orderOut:nil];

  [window->window setDelegate:nil];
  [window->delegate release];

  [window->view release];
  [window->window close];

  free(window);
}

int opl_window_should_close(struct opl_window *window) {
  return window->should_close;
}

const opl_keyboard_state_t* opl_keyboard_get_state(void) {
  return &s_opl_state.keyboard_staet;
}

const opl_mouse_state_t* opl_mouse_get_state(void) {
  return &s_opl_state.mouse_state;
}

int opl_alert_ext(
  const char        *title,
  const char        *text,
  opl_alert_style_t  style,
  int                btn_count,
  const char*       *btn_texts
) {
  NSAlert *alert = [[NSAlert alloc] init];

  switch (style) {
    case OPL_ALERT_STYLE_INFO:
      alert.alertStyle = NSAlertStyleInformational;
      break;
    case OPL_ALERT_STYLE_WARN:
      alert.alertStyle = NSAlertStyleWarning;
      break;
    case OPL_ALERT_STYLE_ERROR:
      alert.alertStyle = NSAlertStyleCritical;
      break;
  }

  alert.accessoryView = nil;
  alert.showsHelp = FALSE;
  alert.delegate = nil;
  alert.messageText = [NSString stringWithCString:title
                                         encoding:NSASCIIStringEncoding];
  alert.informativeText = [NSString stringWithCString:text
                                             encoding:NSASCIIStringEncoding];

  for (int i = 0; i < btn_count; ++i) {
    [alert
        addButtonWithTitle:[NSString stringWithCString:btn_texts[i]
                                              encoding:NSASCIIStringEncoding]];
  }

  int response = (long)[alert runModal] - 1000;
  [alert dealloc];

  // When user provides custom buttons the response
  // returns a button index + 1000
  return btn_count ? response : 1;
}

void opl_window_set_title(struct opl_window *window, const char *title) {
  [window->window setTitle:@(title)];
}

const char* opl_window_get_title(struct opl_window *window) {
  return [window->window.title cStringUsingEncoding:NSASCIIStringEncoding];
}

void opl_window_set_size(struct opl_window *window, int width, int height) {
  const NSWindow *nsWindow = window->window;
  const uint16_t topBarHeight =
      nsWindow.frame.size.height -
      [nsWindow contentRectForFrameRect:nsWindow.frame].size.height;

  [nsWindow setFrame:NSMakeRect(
                       nsWindow.frame.origin.x,
                       nsWindow.frame.origin.y,
                       width,
                       height + topBarHeight
                     )
             display:YES
             animate:YES];
}

void opl_window_get_size(
  struct opl_window *window, int *width, int *height
) {
  const NSWindow *nsWindow = window->window;
  const NSSize size = [nsWindow contentRectForFrameRect:nsWindow.frame].size;

  *width  = (uint16_t)size.width;
  *height = (uint16_t)size.height;
}

void opl_window_set_pos(struct opl_window *window, int x, int y) {
  const NSWindow *nsWindow = window->window;

  [nsWindow setFrame:NSMakeRect(
                       x,
                       NSScreen.mainScreen.frame.size.height - nsWindow.frame.size.height - y,
                       nsWindow.frame.size.width,
                       nsWindow.frame.size.height
                     )
             display:YES
             animate:YES];
}

void opl_window_get_pos(struct opl_window *window, int *x, int *y) {
  // Need to invert Y on macOS, since origin is bottom-left.
  const NSWindow *nsWindow = window->window;
  *x = nsWindow.frame.origin.x;
  *y = NSScreen.mainScreen.frame.size.height -
       nsWindow.frame.size.height -
       nsWindow.frame.origin.y;
}

void opl_hide(struct opl_window *window) {
  [window->window setIsMiniaturized:YES];
}

int opl_is_hidden(struct opl_window *window) {
  return window->window.isMiniaturized;
}

void opl_show(struct opl_window *window) {
  [window->window setIsMiniaturized:NO];
}

int opl_is_shown(struct opl_window *window) {
  return !window->window.isMiniaturized;
}

void opl_toggle_fullscreen(struct opl_window *window) {
  [window->window toggleFullScreen:nil];
}

int opl_is_fullscreen(struct opl_window *window) {
  return window->window.styleMask & NSWindowStyleMaskFullScreen;
}

VkResult opl_vk_surface_create(
  struct opl_window *window,
  VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface
) {
  const VkMetalSurfaceCreateInfoEXT info = {
      .sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT,
      .pNext = NULL,
      .flags = 0,

      .pLayer = window->metal_layer,
  };

  return vkCreateMetalSurfaceEXT(instance, &info, allocator, surface);
}

void opl_vk_device_extensions(int *count, const char **names) {
  if (!names) {
    *count = 2;
    return;
  }

  names[0] = "VK_EXT_metal_surface";
  names[1] = "VK_KHR_surface";
}

