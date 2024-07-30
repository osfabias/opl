#include <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_metal.h>

#include "opl/opl.h"

@class ContentView;
@class WindowDelegate;
@class ApplicationDelegate;

typedef struct _OplCocoaWindow {
  NSWindow       *window;
  ContentView    *view;
  WindowDelegate *delegate;
  CAMetalLayer   *metalLayer;
  uint8_t         shouldClose;
} _OplCocoaWindow;

struct {
  uint8_t initialized;
  ApplicationDelegate *applicationDelegate;

  float deviceRatio;

  OplMouseState mouseState;
  OplKeyboardState keyboardState;
} s_cocoaState = { .initialized = OPL_FALSE };

static OplKey _translateKey(uint32_t keycode) {
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
  _OplCocoaWindow *oplWindow;
}

- (instancetype)initWithOplWindow:(_OplCocoaWindow*)initOplWindow;

@end // WindowDelegate


@implementation WindowDelegate

- (instancetype)initWithOplWindow:(_OplCocoaWindow*)initOplWindow {
  self = [super init];
  if (self != nil) {
    oplWindow = initOplWindow;
  }

  return self;
}

- (BOOL)windowShouldClose:(id)sender {
  oplWindow->shouldClose = OPL_TRUE;
  return YES;
}

@end // WindowDelegate

@interface ContentView : NSView <NSTextInputClient> {
  _OplCocoaWindow           *oplWindow;
  NSWindow                  *window;
  NSTrackingArea            *pRrackingArea;
  NSMutableAttributedString *pMarkedText;
}

- (instancetype)initWithOplWindow:(_OplCocoaWindow*)initOplWindow;

@end // ContentView

@implementation ContentView

  - (instancetype)initWithOplWindow:(_OplCocoaWindow*)initOplWindow {
    self = [super init];
    if (self != nil) {
      oplWindow = initOplWindow;
      window    = oplWindow->window;
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
    s_cocoaState.mouseState.buttons[OPL_MOUSE_BUTTON_LEFT] = 1;
  }

  - (void)mouseDragged:(NSEvent *)event {
    // Equivalent to moving the mouse for now
    [self mouseMoved:event];
  }

  - (void)mouseUp:(NSEvent *)event {
    s_cocoaState.mouseState.buttons[OPL_MOUSE_BUTTON_LEFT] = 0;
  }

  - (void)mouseMoved:(NSEvent *)event {
    const NSPoint pos = [event locationInWindow];

    // Need to invert Y on macOS, since origin is bottom-left.
    // Also need to scale the mouse position by the device pixel
    // ratio so screen lookups are correct.
    NSSize window_size = oplWindow->metalLayer.drawableSize;
    s_cocoaState.mouseState.x
      = pos.x * oplWindow->metalLayer.contentsScale;
    s_cocoaState.mouseState.y =
      window_size.height - (pos.y * oplWindow->metalLayer.contentsScale);
  }

  - (void)rightMouseDown:(NSEvent *)event {
    s_cocoaState.mouseState.buttons[OPL_MOUSE_BUTTON_RIGHT] = 1;
  }

  - (void)rightMouseDragged:(NSEvent *)event  {
    // Equivalent to moving the mouse for now
    [self mouseMoved:event];
  }

  - (void)rightMouseUp:(NSEvent *)event {
    s_cocoaState.mouseState.buttons[OPL_MOUSE_BUTTON_RIGHT] = 0;
  }

  - (void)otherMouseDown:(NSEvent *)event {
    // Interpreted as middle click
    s_cocoaState.mouseState.buttons[OPL_MOUSE_BUTTON_MIDDLE] = 1;
  }

  - (void)otherMouseDragged:(NSEvent *)event {
    // Equivalent to moving the mouse for now
    [self mouseMoved:event];
  }

  - (void)otherMouseUp:(NSEvent *)event {
    // Interpreted as middle click
    s_cocoaState.mouseState.buttons[OPL_MOUSE_BUTTON_MIDDLE] = 0;
  }

  - (void)keyDown:(NSEvent *)event {
    OplKey key = _translateKey((uint32_t)[event keyCode]);
    s_cocoaState.keyboardState.keys[key] = 1;

    // [self interpretKeyEvents:@[event]];
  }

  - (void)keyUp:(NSEvent *)event {
    OplKey key = _translateKey((uint32_t)[event keyCode]);
    s_cocoaState.keyboardState.keys[key] = 1;
  }

  - (void)scrollWheel:(NSEvent *)event {
    s_cocoaState.mouseState.wheel = ((int8_t)[event scrollingDeltaY]);
  }

  // If these methods not implemented - compiler generates warnings and
  // program crashes on platform initialization
  - (void)insertText:(id)string replacementRange:(NSRange)replacementRange {}

  - (void)setMarkedText:(id)string selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange {}

  - (void)unmarkText {}

  // Defines a constant for empty ranges in NSTextInputClient
  static const NSRange kEmptyRange = { NSNotFound, 0 };

  - (NSRange)selectedRange {return kEmptyRange;}

  - (NSRange)markedRange {return kEmptyRange;}

  - (BOOL)hasMarkedText {return false;}

  - (nullable NSMutableAttributedString *)attributedSubstringForProposedRange:(NSRange)range actualRange:(nullable NSRangePointer)actualRange {return nil;}

  - (NSArray<NSAttributedStringKey> *)validAttributesForMarkedText {return [NSArray array];}

  - (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(nullable NSRangePointer)actualRange {return NSMakeRect(0, 0, 0, 0);}

  - (NSUInteger)characterIndexForPoint:(NSPoint)point {return 0;}
@end // ContentView

@interface ApplicationDelegate : NSObject <NSApplicationDelegate> {}

@end // ApplicationDelegate

@implementation ApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  // Posting an empty event at start
  @autoreleasepool {
    NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
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

uint8_t oplInit() {
  if (s_cocoaState.initialized) { return OPL_TRUE; }

  // I don't know what this line stands for (o_O)
  [NSApplication sharedApplication];

  // App delegate creation
  s_cocoaState.applicationDelegate = [[ApplicationDelegate alloc] init];
  if (!s_cocoaState.applicationDelegate) { return OPL_FALSE; }
  [NSApp setDelegate:s_cocoaState.applicationDelegate];

  // Starting application
  if (![[NSRunningApplication currentApplication] isFinishedLaunching]) {
    [NSApp run];
  }

  // Making the app a proper UI app since we're unbundled
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  // Making it possible to create windows in front of others
  [NSApp activateIgnoringOtherApps:YES];

  s_cocoaState.initialized = OPL_TRUE;

  return OPL_TRUE;
}

void oplTerminate() {
  if (!s_cocoaState.initialized) { return; }

  [NSApp setDelegate:nil];
  [s_cocoaState.applicationDelegate release];

  s_cocoaState.initialized = OPL_FALSE;
}

OplWindow oplWindowCreate(const OplWindowCreateInfo *createInfo) {
  _OplCocoaWindow *window = oplAlloc(sizeof(_OplCocoaWindow));

  // Window delegate creation
  window->delegate = [[WindowDelegate alloc] initWithOplWindow:window];
  if (!window->delegate) { return OPL_FALSE; }

  // Window creation
  NSWindowStyleMask styleMask = 0;
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_TITLED) {
    styleMask |= NSWindowStyleMaskTitled;
  }
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_CLOSABLE) {
    styleMask |= NSWindowStyleMaskClosable;
  }
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_RESIZABLE) {
    styleMask |= NSWindowStyleMaskResizable;
  }
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_BORDERLESS) {
    styleMask |= NSWindowStyleMaskBorderless;
  }
  if (createInfo->styleFlags & OPL_WINDOW_STYLE_MINIATURIZABLE) {
    styleMask |= NSWindowStyleMaskMiniaturizable;
  }

  window->window = [[NSWindow alloc]
    initWithContentRect:NSMakeRect(
      createInfo->x,
      NSScreen.mainScreen.frame.size.height - createInfo->height - createInfo->y,
      createInfo->width,
      createInfo->height)
    styleMask: styleMask
    backing: NSBackingStoreBuffered
    defer: NO
  ];

  if (!window->window) {
    oplFree(window);
    return 0;
  }

  if (createInfo->styleFlags & OPL_WINDOW_STYLE_FULLSCREEN) {
    [window->window toggleFullScreen: nil];
  }

  // View creation
  window->view = [[ContentView alloc] initWithOplWindow:window];
  [window->view setWantsLayer:YES];

  // Layer creation
  window->metalLayer = [CAMetalLayer layer];

  // Setting window properties
  [window->window setRestorable:NO];
  [window->window setContentView:window->view];
  [window->window setDelegate:window->delegate];
  [window->window setLevel:NSNormalWindowLevel];
  [window->window setTitle:@(createInfo->title)];
  [window->window setAcceptsMouseMovedEvents:YES];
  [window->window makeFirstResponder:window->view];


  // Putting window in front on launch
  [window->window makeKeyAndOrderFront:nil];

  // Handle content scaling for various fidelity displays (i.e. Retina)
  window->metalLayer.bounds = window->view.bounds;

  // It's important to set the drawableSize to the actual backing
  // pixels. When rendering full-screen, we can skip the macOS compositor
  // if the size matches the display size.
  window->metalLayer.drawableSize =
    [window->view convertSizeToBacking:window->view.bounds.size];

  // In its implementation of vkGetPhysicalDeviceSurfaceCapabilitiesKHR, 
  // MoltenVK takes into consideration both the size (in points) of the
  // bounds, and the contentsScale of the CAMetalLayer from which the
  // Vulkan surface was created.
  // NOTE: See also https://github.com/KhronosGroup/MoltenVK/issues/428
  window->metalLayer.contentsScale = window->view.window.backingScaleFactor;

  // Save off the device pixel ratio.
  // window->deviceRatio = window->metalLayer.contentsScale;

  // Set view's Metal layer
  [window->view setLayer:window->metalLayer];

  // This is set to NO by default, but is also important to ensure we
  // can bypass the compositor in full-screen mode
  // NOTE: See "Direct to Display" http://metalkit.org/2017/06/30/introducing-metal-2.html.
  window->metalLayer.opaque = YES;

  return window;
}

void oplWindowDestroy(OplWindow window) {
  _OplCocoaWindow *cocoaWindow = (_OplCocoaWindow*)(window);
  [cocoaWindow->window orderOut:nil];

  [cocoaWindow->window setDelegate:nil];
  [cocoaWindow->delegate release];

  [cocoaWindow->view release];
  [cocoaWindow->window close];

  oplFree(cocoaWindow);
}

uint8_t oplWindowShouldClose(OplWindow window) {
  return ((_OplCocoaWindow*)window)->shouldClose;
}

void oplWindowSetTitle(OplWindow window, const char *title) {
  [((_OplCocoaWindow*)window)->window setTitle:@(title)];
}

const char* oplWindowGetTitle(OplWindow window) {
  return [((_OplCocoaWindow*)window)->window.title cStringUsingEncoding:NSASCIIStringEncoding];
}

void oplWindowSetSize(OplWindow window, uint16_t width, uint16_t height) {
  const NSWindow *nsWindow = ((_OplCocoaWindow*)window)->window;
  const uint16_t topBarHeight =
    nsWindow.frame.size.height - [nsWindow contentRectForFrameRect: nsWindow.frame].size.height;

  [nsWindow
    setFrame:NSMakeRect(
      nsWindow.frame.origin.x,
      nsWindow.frame.origin.y,
      width,
      height + topBarHeight
    )
    display:YES
    animate:YES
  ];
}

void oplWindowGetSize(OplWindow window, uint16_t *width, uint16_t *height) {
  const NSWindow *nsWindow = ((_OplCocoaWindow*)window)->window;
  const NSSize size = [nsWindow contentRectForFrameRect: nsWindow.frame].size;

  *width  = (uint16_t)size.width;
  *height = (uint16_t)size.height;
}

void oplWindowSetPosition(OplWindow window, uint16_t x, uint16_t y) {
  const NSWindow *nsWindow = ((_OplCocoaWindow*)window)->window;

  [nsWindow
    setFrame:NSMakeRect(
      x,
      NSScreen.mainScreen.frame.size.height - nsWindow.frame.size.height - y,
      nsWindow.frame.size.width,
      nsWindow.frame.size.height
    )
    display:YES
    animate:YES
  ];
}

void oplWindowGetPosition(OplWindow window, uint16_t *x, uint16_t *y) {
  // Need to invert Y on macOS, since origin is bottom-left.
  const NSWindow *nsWindow = ((_OplCocoaWindow*)window)->window;
  *x = nsWindow.frame.origin.x;
  *y = NSScreen.mainScreen.frame.size.height -
       nsWindow.frame.size.height -
       nsWindow.frame.origin.y;
}

void oplWindowMiniaturize(OplWindow window) {
  [((_OplCocoaWindow*)window)->window setIsMiniaturized:YES];
}

uint8_t oplWindowIsMinituarized(OplWindow window) {
  return ((_OplCocoaWindow*)window)->window.isMiniaturized;
  return OPL_FALSE;
}

void oplWindowMaximize(OplWindow window) {
  [((_OplCocoaWindow*)window)->window setIsMiniaturized:NO];
}

uint8_t oplWindowIsMaximized(OplWindow window) {
  return !((_OplCocoaWindow*)window)->window.isMiniaturized;
  return OPL_FALSE;
}

void oplWindowToggleFullscreen(OplWindow window) {
  [((_OplCocoaWindow*)window)->window toggleFullScreen: nil];
}

uint8_t oplWindowIsFullscreen(OplWindow window) {
  return ((_OplCocoaWindow*)window)->window.styleMask &
         NSWindowStyleMaskFullScreen;
}

void oplPumpMessages() {
  @autoreleasepool {
    NSEvent* event;

    while (1) {
      event = [NSApp 
        nextEventMatchingMask:NSEventMaskAny
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

void oplConsoleWrite(const char *message, OplColor color) {
  // none, trace, info, warn, error, fatal
  const char* clrStrings[] = { "0", "1;30", "1;32", "1;33", "1;31", "0;41", };
  printf("\033[%sm%s\033[0m", clrStrings[color], message);
}

VkResult oplCreateSurface(
  OplWindow window, VkInstance instance,
  const VkAllocationCallbacks *allocator,
  VkSurfaceKHR *surface) {

  VkMetalSurfaceCreateInfoEXT info = {
    .sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT,
    .pNext = 0,
    .flags = 0,
    .pLayer = ((_OplCocoaWindow*)window)->metalLayer,
  };

  return vkCreateMetalSurfaceEXT(instance, &info, allocator, surface);
}

void oplGetDeviceExtensions(
  uint32_t *extensionsCount, const char* *extensionNames) {
  if (!extensionNames) { *extensionsCount = 2; return; }

  extensionNames[0] = "VK_EXT_metal_surface";
  extensionNames[1] = "VK_KHR_surface";
}

