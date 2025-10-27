/*
* mediahog 0.1 pre-alpha

*
* Mediahog is a multimedia abstraction library that
* combines serveral of my lightweight libraries into one cohesive library
*
* The library itself is broken up into two editions core and complete.
*
*
* Core includes the base library, with only the essnetials.
*
* Complete includes extra utilities and closed-source tools to help with development.
* As well as extra devlogs and other notes.
*
* A large part of this library's existance is as a means to fund
* the development of all of open source ventures.
* Since many people would never buy the tools.
*
* Although I also see the benefit of having this cohesive library,
* and would like to see people using it.
* Which is why the core part of it will be FOSS.
*

* Copyright (C) 2022-25 Riley Mabb (@ColleagueRiley)
*
* libpng license
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.

* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

#ifndef MEDIAHOG_HEADER

#define MEDIAHOG_HEADER

/*
* This is here to ensure the functions have the correct visibility
*/

#if defined(MEDIAHOG_EXPORT) ||  defined(MEDIAHOG_IMPORT)
	#if defined(_WIN32)
		#if defined(__TINYC__) && (defined(MEDIAHOG_EXPORT) ||  defined(MEDIAHOG_IMPORT))
			#define __declspec(x) __attribute__((x))
		#endif

		#if defined(MEDIAHOG_EXPORT)
			#define MEDIAHOG_API __declspec(dllexport)
		#else
			#define MEDIAHOG_API __declspec(dllimport)
		#endif
	#else
		#if defined(MEDIAHOG_EXPORT)
			#define MEDIAHOG_API __attribute__((visibility("default")))
		#endif
	#endif
    #ifndef MEDIAHOG_API
        #define MEDIAHOG_API
    #endif
#endif

#ifndef MEDIAHOG_API
	#define MEDIAHOG_API
#endif

/* useful macros
 * these are macros I find useful for the mediahog header
*/

/* returns the value of the nth bit (e.g.) 2 -> 4, 3 -> 8  */
/* this is useful for enum flags */
#define MEDIAHOG_BIT(n) (1 << (n))


/*
 * Currently, mediahog is made for C99 and will use C99 types
 * stdint : standardized int types, 'int64_t', rather than default ctypes 'int'
 * stdbool : standardized bool type so mediahog doesn't have to have a custom bool type
 * stddef : size_t and other standard size types
*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


/*
 * mediahog types, these are types that will be used by/for mediahog
*/


/*
 * Global types
 * these types are used across the entire mediahog API
*/

/* Enum values for all of mediahog's subsystems
 * These are used when requesting which subsystems you would like to initalize
*/
typedef enum mediahog_subsystems {
	MEDIAHOG_WINDOWING = MEDIAHOG_BIT(0), /* basic windowing features */
	MEDIAHOG_GRAPHICS = MEDIAHOG_BIT(1), /* rendering and graphical features */

	/* combos of enums to make it easier to init mediahog */
	MEIDAHOG_VIDEO = MEDIAHOG_WINDOWING | MEDIAHOG_GRAPHICS
} mediahog_subsystems;

/*
 * Windowing subsystem types
 * these types are for mediahog's windowing subsystem
*/

typedef void* mediahog_window;

typedef mediahog_ENUM(u8, mediahog_format) {
    mediahog_formatRGB8 = 0,    /*!< 8-bit RGB (3 channels) */
    mediahog_formatBGR8,    /*!< 8-bit BGR (3 channels) */
	mediahog_formatRGBA8,   /*!< 8-bit RGBA (4 channels) */
	mediahog_formatARGB8,   /*!< 8-bit RGBA (4 channels) */
    mediahog_formatBGRA8,   /*!< 8-bit BGRA (4 channels) */
    mediahog_formatABGR8,   /*!< 8-bit BGRA (4 channels) */
	mediahog_formatCount
};

typedef struct mediahog_nativeImage mediahog_nativeImage;
typedef struct mediahog_surface mediahog_surface;

/* RGFW mouse loading */
typedef void mediahog_mouse;

/* monitor mode data | can be changed by the user (with functions)*/
typedef struct mediahog_monitorMode {
	i32 w, h; /*!< monitor workarea size */
	u32 refreshRate; /*!< monitor refresh rate */
	u8 red, blue, green;
} mediahog_monitorMode;

/*! structure for monitor data */
typedef struct mediahog_monitor {
	i32 x, y; /*!< x - y of the monitor workarea */
	char name[128]; /*!< monitor name */
	float scaleX, scaleY; /*!< monitor content scale */
	float pixelRatio; /*!< pixel ratio for monitor (1.0 for regular, 2.0 for hiDPI)  */
	float physW, physH; /*!< monitor physical size in inches */
	mediahog_monitorMode mode;
} mediahog_monitor;

typedef mediahog_ENUM(u8, mediahog_modeRequest) {
mediahog_monitorScale = mediahog_BIT(0), /*!< scale the monitor size */
	mediahog_monitorRefresh = mediahog_BIT(1), /*!< change the refresh rate */
	mediahog_monitorRGB = mediahog_BIT(2), /*!< change the monitor RGB bits size */
	mediahog_monitorAll = mediahog_monitorScale | mediahog_monitorRefresh | mediahog_monitorRGB
	};

/*!
	key codes and mouse icon enums
*/
typedef mediahog_ENUM(u8, mediahog_key) {
	mediahog_keyNULL = 0,
	mediahog_escape = '\033',
	mediahog_backtick = '`',
	mediahog_0 = '0',
	mediahog_1 = '1',
	mediahog_2 = '2',
	mediahog_3 = '3',
	mediahog_4 = '4',
	mediahog_5 = '5',
	mediahog_6 = '6',
	mediahog_7 = '7',
	mediahog_8 = '8',
	mediahog_9 = '9',
	mediahog_minus = '-',
	mediahog_equals = '=',
	mediahog_backSpace = '\b',
	mediahog_tab = '\t',
	mediahog_space = ' ',
	mediahog_a = 'a',
	mediahog_b = 'b',
	mediahog_c = 'c',
	mediahog_d = 'd',
	mediahog_e = 'e',
	mediahog_f = 'f',
	mediahog_g = 'g',
	mediahog_h = 'h',
	mediahog_i = 'i',
	mediahog_j = 'j',
	mediahog_k = 'k',
	mediahog_l = 'l',
	mediahog_m = 'm',
	mediahog_n = 'n',
	mediahog_o = 'o',
	mediahog_p = 'p',
	mediahog_q = 'q',
	mediahog_r = 'r',
	mediahog_s = 's',
	mediahog_t = 't',
	mediahog_u = 'u',
	mediahog_v = 'v',
	mediahog_w = 'w',
	mediahog_x = 'x',
	mediahog_y = 'y',
	mediahog_z = 'z',
	mediahog_period = '.',
	mediahog_comma = ',',
	mediahog_slash = '/',
	mediahog_bracket = '[',
    mediahog_closeBracket = ']',
    mediahog_semicolon = ';',
	mediahog_apostrophe = '\'',
	mediahog_backSlash = '\\',
	mediahog_return = '\n',
	mediahog_enter = mediahog_return,
	mediahog_delete = '\177', /* 127 */
	mediahog_F1,
	mediahog_F2,
	mediahog_F3,
	mediahog_F4,
	mediahog_F5,
	mediahog_F6,
	mediahog_F7,
	mediahog_F8,
	mediahog_F9,
	mediahog_F10,
	mediahog_F11,
	mediahog_F12,
    mediahog_F13,
    mediahog_F14,
    mediahog_F15,
    mediahog_F16,
    mediahog_F17,
    mediahog_F18,
    mediahog_F19,
    mediahog_F20,
    mediahog_F21,
    mediahog_F22,
    mediahog_F23,
    mediahog_F24,
    mediahog_F25,
	mediahog_capsLock,
	mediahog_shiftL,
	mediahog_controlL,
	mediahog_altL,
	mediahog_superL,
	mediahog_shiftR,
	mediahog_controlR,
	mediahog_altR,
	mediahog_superR,
	mediahog_up,
	mediahog_down,
	mediahog_left,
	mediahog_right,
	mediahog_insert,
	mediahog_menu,
	mediahog_end,
	mediahog_home,
	mediahog_pageUp,
	mediahog_pageDown,
	mediahog_numLock,
	mediahog_kpSlash,
	mediahog_kpMultiply,
	mediahog_kpPlus,
	mediahog_kpMinus,
	mediahog_kpEqual,
	mediahog_kp1,
	mediahog_kp2,
	mediahog_kp3,
	mediahog_kp4,
	mediahog_kp5,
	mediahog_kp6,
	mediahog_kp7,
	mediahog_kp8,
	mediahog_kp9,
	mediahog_kp0,
	mediahog_kpPeriod,
	mediahog_kpReturn,
	mediahog_scrollLock,
    mediahog_printScreen,
    mediahog_pause,
	mediahog_world1,
    mediahog_world2,
    mediahog_keyLast = 256 /* padding for alignment ~(175 by default) */
};

/*! mouse button codes (mediahog_event.button.value) */
typedef mediahog_ENUM(u8, mediahog_mouseButton) {
	mediahog_mouseLeft = 0, /*!< left mouse button is pressed */
	mediahog_mouseMiddle, /*!< mouse-wheel-button is pressed */
	mediahog_mouseRight, /*!< right mouse button is pressed */
	mediahog_mouseMisc1, mediahog_mouseMisc2, mediahog_mouseMisc3, mediahog_mouseMisc4, mediahog_mouseMisc5,
	mediahog_mouseFinal
};

/* for mediahog_event.lockstate */
typedef mediahog_ENUM(u8, mediahog_keymod) {
	mediahog_modCapsLock = mediahog_BIT(0),
	mediahog_modNumLock  = mediahog_BIT(1),
	mediahog_modControl  = mediahog_BIT(2),
	mediahog_modAlt = mediahog_BIT(3),
	mediahog_modShift  = mediahog_BIT(4),
	mediahog_modSuper = mediahog_BIT(5),
	mediahog_modScrollLock = mediahog_BIT(6)
};

typedef mediahog_ENUM(u8, mediahog_eventType) {
	/*! event codes */
	mediahog_eventNone = 0, /*!< no event has been sent */
 	mediahog_keyPressed, /* a key has been pressed */
	mediahog_keyReleased, /*!< a key has been released */
	/*! key event note
		the code of the key pressed is stored in
		mediahog_event.key.value
		!!Keycodes defined at the bottom of the mediahog_HEADER part of this file!!

		while a string version is stored in
		mediahog_event.key.valueString

		mediahog_event.key.mod holds the current mod
		this means if CapsLock, NumLock are active or not
	*/
	mediahog_mouseButtonPressed, /*!< a mouse button has been pressed (left,middle,right) */
	mediahog_mouseButtonReleased, /*!< a mouse button has been released (left,middle,right) */
	mediahog_mouseScroll, /*!< a mouse scroll event */
	mediahog_mousePosChanged, /*!< the position of the mouse has been changed */
	/*! mouse event note
		the x and y of the mouse can be found in the vector, mediahog_x, y

		mediahog_event.button.value holds which mouse button was pressed
	*/
	mediahog_windowMoved, /*!< the window was moved (by the user) */
	mediahog_windowResized, /*!< the window was resized (by the user), [on WASM this means the browser was resized] */
	mediahog_focusIn, /*!< window is in focus now */
	mediahog_focusOut, /*!< window is out of focus now */
	mediahog_mouseEnter, /* mouse entered the window */
	mediahog_mouseLeave, /* mouse left the window */
	mediahog_windowRefresh, /* The window content needs to be refreshed */

	/* attribs change event note
		The event data is sent straight to the window structure
		with win->x, win->y, win->w and win->h
	*/
	mediahog_quit, /*!< the user clicked the quit button */
	mediahog_dataDrop, /*!< a file has been dropped into the window */
	mediahog_dataDrag, /*!< the start of a drag and drop event, when the file is being dragged */
	/* drop data note
		The x and y coords of the drop are stored in the vector mediahog_x, y

		mediahog_event.drop.count holds how many files were dropped

		This is also the size of the array which stores all the dropped file string,
		mediahog_event.drop.files
	*/
	mediahog_windowMaximized, /*!< the window was maximized */
	mediahog_windowMinimized, /*!< the window was minimized */
	mediahog_windowRestored, /*!< the window was restored */
	mediahog_scaleUpdated /*!< content scale factor changed */
};


typedef mediahog_ENUM(u32, mediahog_eventFlag) {
    mediahog_keyPressedFlag = mediahog_BIT(mediahog_keyPressed),
    mediahog_keyReleasedFlag = mediahog_BIT(mediahog_keyReleased),
    mediahog_mouseScrollFlag = mediahog_BIT(mediahog_mouseScroll),
    mediahog_mouseButtonPressedFlag = mediahog_BIT(mediahog_mouseButtonPressed),
    mediahog_mouseButtonReleasedFlag = mediahog_BIT(mediahog_mouseButtonReleased),
    mediahog_mousePosChangedFlag = mediahog_BIT(mediahog_mousePosChanged),
    mediahog_mouseEnterFlag = mediahog_BIT(mediahog_mouseEnter),
    mediahog_mouseLeaveFlag = mediahog_BIT(mediahog_mouseLeave),
    mediahog_windowMovedFlag = mediahog_BIT(mediahog_windowMoved),
    mediahog_windowResizedFlag = mediahog_BIT(mediahog_windowResized),
    mediahog_focusInFlag = mediahog_BIT(mediahog_focusIn),
    mediahog_focusOutFlag = mediahog_BIT(mediahog_focusOut),
    mediahog_windowRefreshFlag = mediahog_BIT(mediahog_windowRefresh),
    mediahog_windowMaximizedFlag = mediahog_BIT(mediahog_windowMaximized),
    mediahog_windowMinimizedFlag = mediahog_BIT(mediahog_windowMinimized),
    mediahog_windowRestoredFlag = mediahog_BIT(mediahog_windowRestored),
    mediahog_scaleUpdatedFlag = mediahog_BIT(mediahog_scaleUpdated),
    mediahog_quitFlag = mediahog_BIT(mediahog_quit),
    mediahog_dataDropFlag = mediahog_BIT(mediahog_dataDrop),
    mediahog_dataDragFlag = mediahog_BIT(mediahog_dataDrag),

    mediahog_keyEventsFlag = mediahog_keyPressedFlag | mediahog_keyReleasedFlag,
    mediahog_mouseEventsFlag = mediahog_mouseButtonPressedFlag | mediahog_mouseButtonReleasedFlag | mediahog_mousePosChangedFlag | mediahog_mouseEnterFlag | mediahog_mouseLeaveFlag | mediahog_mouseScrollFlag ,
    mediahog_windowEventsFlag = mediahog_windowMovedFlag | mediahog_windowResizedFlag | mediahog_windowRefreshFlag | mediahog_windowMaximizedFlag | mediahog_windowMinimizedFlag | mediahog_windowRestoredFlag | mediahog_scaleUpdatedFlag,
    mediahog_focusEventsFlag = mediahog_focusInFlag | mediahog_focusOutFlag,
    mediahog_dataDropEventsFlag = mediahog_dataDropFlag | mediahog_dataDragFlag,
    mediahog_allEventFlags = mediahog_keyEventsFlag | mediahog_mouseEventsFlag | mediahog_windowEventsFlag | mediahog_focusEventsFlag | mediahog_dataDropEventsFlag | mediahog_quitFlag
};

/*! Event structure(s) and union for checking/getting events */
typedef struct mediahog_commonEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
} mediahog_commonEvent;

typedef struct mediahog_mouseButtonEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	u8 value; /* !< which mouse button was pressed */
} mediahog_mouseButtonEvent;

typedef struct mediahog_mouseScrollEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	float x, y; /*!< the raw mouse scroll value */
} mediahog_mouseScrollEvent;

typedef struct mediahog_mousePosEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	i32 x, y; /*!< mouse x, y of event (or drop point) */
	float vecX, vecY; /*!< raw mouse movement */
} mediahog_mousePosEvent;

typedef struct mediahog_keyEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	mediahog_key value; /*!< the physical key of the event, refers to where key is physically !!Keycodes defined at the bottom of the mediahog_HEADER part of this file!! */
	u8 sym; /*!< mapped key char of the event */
	mediahog_bool repeat; /*!< key press event repeated (the key is being held) */
	mediahog_keymod mod;
} mediahog_keyEvent;

typedef struct mediahog_dataDropEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	/* 260 max paths with a max length of 260 */
	char** files; /*!< dropped files */
	size_t count; /*!< how many files were dropped */
} mediahog_dataDropEvent;

typedef struct mediahog_dataDragEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	i32 x, y; /*!< mouse x, y of event (or drop point) */
} mediahog_dataDragEvent;

typedef struct mediahog_scaleUpdatedEvent {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_window* win; /*!< the window this event applies too (for event queue events) */
	float x, y; /*!< DPI scaling */
} mediahog_scaleUpdatedEvent;

/*! mediahog_event union */
typedef union mediahog_event {
	mediahog_eventType type; /*!< which event has been sent?*/
	mediahog_commonEvent common; /*!< common event data (e.g.) type and win */
	mediahog_mouseButtonEvent button; /*!< data for a button press/release */
	mediahog_mouseScrollEvent scroll; /*!< data for a mouse scroll */
	mediahog_mousePosEvent mouse; /*!< data for mouse motion events */
	mediahog_keyEvent key; /*!< data for key press/release/hold events */
	mediahog_dataDropEvent drop; /*!< dropping a file events */
	mediahog_dataDragEvent drag; /* data for dragging a file events */
	mediahog_scaleUpdatedEvent scale; /* data for monitor scaling events */
} mediahog_event;

/*!
	for mediahog_the code is stupid and C++ waitForEvent
	waitMS -> Allows the function to keep checking for events even after there are no more events
			  if waitMS == 0, the loop will not wait for events
			  if waitMS > 0, the loop will wait that many miliseconds after there are no more events until it returns
			  if waitMS == -1 or waitMS == the max size of an unsigned 32-bit int, the loop will not return until it gets another event
*/
typedef mediahog_ENUM(i32, mediahog_eventWait) {
	mediahog_eventNoWait = 0,
	mediahog_eventWaitNext = -1
};

/*! Optional arguments for making a windows */
typedef mediahog_ENUM(u32, mediahog_windowFlags) {
	mediahog_windowNoBorder = mediahog_BIT(0), /*!< the window doesn't have a border */
	mediahog_windowNoResize = mediahog_BIT(1), /*!< the window cannot be resized by the user */
	mediahog_windowAllowDND = mediahog_BIT(2), /*!< the window supports drag and drop */
	mediahog_windowHideMouse = mediahog_BIT(3), /*! the window should hide the mouse (can be toggled later on using `mediahog_window_showMouse`) */
	mediahog_windowFullscreen = mediahog_BIT(4), /*!< the window is fullscreen by default */
	mediahog_windowTransparent = mediahog_BIT(5), /*!< the window is transparent (only properly works on X11 and MacOS, although it's meant for for windows) */
	mediahog_windowCenter = mediahog_BIT(6), /*! center the window on the screen */
	mediahog_windowScaleToMonitor = mediahog_BIT(8), /*! scale the window to the screen */
	mediahog_windowHide = mediahog_BIT(9), /*! the window is hidden */
	mediahog_windowMaximize = mediahog_BIT(10),
	mediahog_windowCenterCursor = mediahog_BIT(11),
	mediahog_windowFloating = mediahog_BIT(12), /*!< create a floating window */
	mediahog_windowFocusOnShow = mediahog_BIT(13), /*!< focus the window when it's shown */
	mediahog_windowMinimize = mediahog_BIT(14), /*!< focus the window when it's shown */
	mediahog_windowFocus = mediahog_BIT(15), /*!< if the window is in focus */
	mediahog_windowOpenGL = mediahog_BIT(17), /*!< create an OpenGL context (you can also do this manually with mediahog_window_createContext_OpenGL) */
	mediahog_windowEGL = mediahog_BIT(18), /*!< create an EGL context (you can also do this manually with mediahog_window_createContext_EGL) */
	mediahog_windowedFullscreen = mediahog_windowNoBorder | mediahog_windowMaximize
};

typedef mediahog_ENUM(u8, mediahog_icon) {
	mediahog_iconTaskbar = mediahog_BIT(0),
	mediahog_iconWindow = mediahog_BIT(1),
	mediahog_iconBoth = mediahog_iconTaskbar | mediahog_iconWindow
};

typedef mediahog_ENUM(u8, mediahog_mouseIcons) {
	mediahog_mouseNormal = 0,
	mediahog_mouseArrow,
	mediahog_mouseIbeam,
	mediahog_mouseCrosshair,
	mediahog_mousePointingHand,
	mediahog_mouseResizeEW,
	mediahog_mouseResizeNS,
	mediahog_mouseResizeNWSE,
	mediahog_mouseResizeNESW,
	mediahog_mouseResizeAll,
	mediahog_mouseNotAllowed,
	mediahog_mouseIconCount,
    mediahog_mouseIconFinal = 16 /* padding for alignment */
};

/** * @defgroup Clipboard
* @{ */
typedef ptrdiff_t mediahog_ssize_t;

/** * @defgroup error handling
* @{ */
typedef mediahog_ENUM(u8, mediahog_debugType) {
	mediahog_typeError = 0, mediahog_typeWarning, mediahog_typeInfo
};

typedef mediahog_ENUM(u8, mediahog_errorCode) {
	mediahog_noError = 0, /*!< no error */
	mediahog_errOutOfMemory,
	mediahog_errOpenGLContext, mediahog_errEGLContext, /*!< error with the OpenGL context */
	mediahog_errWayland, mediahog_errX11,
	mediahog_errDirectXContext,
	mediahog_errIOKit,
	mediahog_errClipboard,
	mediahog_errFailedFuncLoad,
	mediahog_errBuffer,
	mediahog_errEventQueue,
	mediahog_infoMonitor, mediahog_infoWindow, mediahog_infoBuffer, mediahog_infoGlobal, mediahog_infoOpenGL,
	mediahog_warningWayland, mediahog_warningOpenGL
};

typedef void (* mediahog_debugfunc)(mediahog_debugType type, mediahog_errorCode err, const char* msg);
typedef void (*mediahog_proc)(void); /* function pointer equivalent of void* */

/*! native rendering API functions */
typedef struct mediahog_glContext mediahog_glContext;
typedef struct mediahog_eglContext mediahog_eglContext;

/*! OpenGL init hints */
typedef mediahog_ENUM(i32, mediahog_glReleaseBehavior)   { mediahog_glReleaseFlush = 0, mediahog_glReleaseNone };
typedef mediahog_ENUM(i32, mediahog_glProfile)  { mediahog_glCore = 0, mediahog_glCompatibility, mediahog_glES};
typedef mediahog_ENUM(i32, mediahog_glRenderer)  { mediahog_glAccelerated = 0, mediahog_glSoftware };

typedef struct mediahog_glHints {
	i32 stencil;  /*!< set stencil buffer bit size (0 by default) */
	i32 samples; /*!< set number of sample buffers (0 by default) */
	i32 stereo; /*!< hint the context to use stereoscopic frame buffers for 3D (false by default) */
	i32 auxBuffers; /*!< number of aux buffers (0 by default) */
	i32 doubleBuffer; /*!< request double buffering (true by default) */
	i32 red, green, blue, alpha; /*!< set color bit sizes (all 8 by default) */
	i32 depth; /*!< set depth buffer bit size (24 by default) */
	i32 accumRed, accumGreen, accumBlue, accumAlpha; /*!< set accumulated RGBA bit sizes (all 0 by default) */
	mediahog_bool sRGB; /*!< request sRGA format (false by default) */
	mediahog_bool robustness; /*!< request a "robust" (as in memory-safe) context (false by default). For more information check the overview section: https://registry.khronos.org/OpenGL/extensions/EXT/EXT_robustness.txt */
	mediahog_bool debug; /*!< request OpenGL debugging (false by default). */
	mediahog_bool noError; /*!< request no OpenGL errors (false by default). This causes OpenGL errors to be undefined behavior. For more information check the overview section: https://registry.khronos.org/OpenGL/extensions/KHR/KHR_no_error.txt */
	mediahog_glReleaseBehavior releaseBehavior; /*!< hint how the OpenGL driver should behave when changing contexts (mediahog_glReleaseNone by default). For more information check the overview section: https://registry.khronos.org/OpenGL/extensions/KHR/KHR_context_flush_control.txt */
	mediahog_glProfile profile; /*!< set OpenGL API profile (mediahog_glCore by default) */
	i32 major, minor;  /*!< set the OpenGL API profile version (by default mediahog_glMajor is 1, mediahog_glMinor is 0) */
	mediahog_glContext* share; /*!< Share this OpenGL context with newly created OpenGL contexts; defaults to NULL. */
	mediahog_eglContext* shareEGL; /*!< Share this EGL context with newly created OpenGL contexts; defaults to NULL. */
	mediahog_glRenderer renderer; /*!< renderer to use e.g. accelerated or software defaults to accelerated */
} mediahog_glHints;


/*! mediahog_windowMoved, the window and its new rect value  */
typedef void (* mediahog_windowMovedfunc)(mediahog_window* win, i32 x, i32 y);
/*! mediahog_windowResized, the window and its new rect value  */
typedef void (* mediahog_windowResizedfunc)(mediahog_window* win, i32 w, i32 h);
/*! mediahog_windowRestored, the window and its new rect value  */
typedef void (* mediahog_windowRestoredfunc)(mediahog_window* win, i32 x, i32 y, i32 w, i32 h);
/*! mediahog_windowMaximized, the window and its new rect value  */
typedef void (* mediahog_windowMaximizedfunc)(mediahog_window* win, i32 x, i32 y, i32 w, i32 h);
/*! mediahog_windowMinimized, the window and its new rect value  */
typedef void (* mediahog_windowMinimizedfunc)(mediahog_window* win);
/*! mediahog_quit, the window that was closed */
typedef void (* mediahog_windowQuitfunc)(mediahog_window* win);
/*! mediahog_focusIn / mediahog_focusOut, the window who's focus has changed and if its in focus */
typedef void (* mediahog_focusfunc)(mediahog_window* win, mediahog_bool inFocus);
/*! mediahog_mouseEnter / mediahog_mouseLeave, the window that changed, the point of the mouse (enter only) and if the mouse has entered */
typedef void (* mediahog_mouseNotifyfunc)(mediahog_window* win, i32 x, i32 y, mediahog_bool status);
/*! mediahog_mousePosChanged, the window that the move happened on, and the new point of the mouse  */
typedef void (* mediahog_mousePosfunc)(mediahog_window* win, i32 x, i32 y, float vecX, float vecY);
/*! mediahog_dataDrag, the window, the point of the drop on the windows */
typedef void (* mediahog_dataDragfunc)(mediahog_window* win, i32 x, i32 y);
/*! mediahog_windowRefresh, the window that needs to be refreshed */
typedef void (* mediahog_windowRefreshfunc)(mediahog_window* win);
/*! mediahog_keyPressed / mediahog_keyReleased, the window that got the event, the mapped key, the physical key, the string version, the state of the mod keys, if it was a press (else it's a release) */
typedef void (* mediahog_keyfunc)(mediahog_window* win, u8 key, u8 sym, mediahog_keymod mod, mediahog_bool repeat, mediahog_bool pressed);
/*! mediahog_mouseButtonPressed / mediahog_mouseButtonReleased, the window that got the event, the button that was pressed, the scroll value, if it was a press (else it's a release)  */
typedef void (* mediahog_mouseButtonfunc)(mediahog_window* win, mediahog_mouseButton button, mediahog_bool pressed);
/*! mediahog_mouseScroll, the window that got the event, the x scroll value, the y scroll value */
typedef void (* mediahog_mouseScrollfunc)(mediahog_window* win, float x, float y);
/*! mediahog_dataDrop the window that had the drop, the drop data and the number of files dropped */
typedef void (* mediahog_dataDropfunc)(mediahog_window* win, char** files, size_t count);
/*! mediahog_scaleUpdated, the window the event was sent to, content scaleX, content scaleY */
typedef void (* mediahog_scaleUpdatedfunc)(mediahog_window* win, float scaleX, float scaleY);



/*
 *
 * Mediahog API
 * these are functions for interfacing with mediahog and it's underlying systems
 *
*/

/*
 * Global API
 * these functions are used across the entire mediahog API
*/

/**
 * @brief initialize the library, allocating and setting up required data
 * @param `flags` are flags, from the mediahog_subsystems enums, for which subsystems you would like to init
 * @return returns a boolean value that returns true on success or false on failure.
*/

MEDIAHOG_API bool mediahog_init(mediahog_subsystems flags);

/**
 * @brief close the library, freeing and closing any leftover data
 * @return returns a boolean value that returns true on success or false on failure.
*/

MEDIAHOG_API bool mediahog_free(void);

/*
 * Windowing API
 * these are functions for mediahog's windowing subsystem
*/

/**
 * @brief
 * @return
*/

MEDIAHOG_API void mediahog_pollEvents(void);

/**
 * @brief
 * @return
*/

MEDIAHOG_API mediahog_window* mediahog_window_init(const char* name, int32_t x, int32_t y, int32_t w, int32_t h);

/**
 * @brief
 * @return
*/

MEDIAHOG_API bool mediahog_window_should_close(mediahog_window* window);

/**
 * @brief
 * @return
*/


MEDIAHOG_API void mediahog_window_free(mediahog_window* window);

/**
 * @brief
 * @return
*/


MEDIAHOG_API void mediahog_use_wayland(mediahog_bool wayland);

/**
 * @brief
 * @return
*/

MEDIAHOG_API mediahog_bool mediahog_using_wayland(void);


/**
 * @brief
 * @return
*/

MEDIAHOG_API void* mediahog_get_layer_OSX(void);

/**
 * @brief
 * @return
*/

MEDIAHOG_API void* mediahog_get_display_X11(void);

/**
 * @brief
 * @return
*/

MEDIAHOG_API struct wl_display* mediahog_get_display_wayland(void);

/**
 * @brief
 * @return
*/

MEDIAHOG_API void mediahog_set_slass_name(const char* name);

/**
 * @brief
 * @return
*/

MEDIAHOG_API void mediahog_set_inst_Name_X11(const char* name); /*!< X11 instance name (window name will by used by default) */


/*
 * NOTE: when you create a surface using mediahog_createSurface / ptr, on X11 it uses the root window's visual
 * this means it may fail to render on any other window if the visual does not match
 * mediahog_window_createSurface and mediahog_window_createSurfacePtr exist only for X11 to address this issues
 * Of course, you can also manually set the root window with mediahog_setRootWindow
 */
MEDIAHOG_API mediahog_surface* mediahog_surface_init(u8* data, i32 w, i32 h, mediahog_format format);

MEDIAHOG_API mediahog_nativeImage* mediahog_surface_get_native_image(mediahog_surface* surface);

/*! free the surface pointer and buffers used for software rendering within the window */
MEDIAHOG_API void mediahog_surface_free(mediahog_surface* surface);

/*! copy image to another image, respecting each image's format */
MEDIAHOG_API void mediahog_copy_image_data(u8* dest_data, i32 w, i32 h, mediahog_format dest_format, u8* src_data, mediahog_format src_format);

MEDIAHOG_API mediahog_debugfunc mediahog_setDebugCallback(mediahog_debugfunc func);

MEDIAHOG_API const char* mediahog_readClipboard(size_t* size); /*!< read clipboard data */
/*! read clipboard data or send a NULL str to just get the length of the clipboard data */
MEDIAHOG_API mediahog_ssize_t mediahog_readClipboardPtr(char* str, size_t strCapacity);
MEDIAHOG_API void mediahog_writeClipboard(const char* text, u32 textLen); /*!< write text to the clipboard */
/** @} */




/*!< loads mouse icon from bitmap (similar to mediahog_window_setIcon). Icon NOT resized by default */
MEDIAHOG_API mediahog_mouse* mediahog_mouse_load(u8* data, i32 w, i32 h, mediahog_format format);
/*!< frees mediahog_mouse data */
MEDIAHOG_API void mediahog_mouse_free(mediahog_mouse* mouse);


/*! get an array of all the monitors (max 6) */
MEDIAHOG_API mediahog_monitor* mediahog_get_monitors(size_t* len);
/*! get the primary monitor */
MEDIAHOG_API mediahog_monitor mediahog_get_primary_monitor(void);

/*! request a specific mode */
MEDIAHOG_API mediahog_bool mediahog_monitor_requestMode(mediahog_monitor mon, mediahog_monitorMode mode, mediahog_modeRequest request);
/*! check if 2 monitor modes are the same */
MEDIAHOG_API mediahog_bool mediahog_monitorModeCompare(mediahog_monitorMode mon, mediahog_monitorMode mon2, mediahog_modeRequest request);
/*! scale monitor to window size */
MEDIAHOG_API mediahog_bool mediahog_monitor_scaleToWindow(mediahog_monitor mon, struct mediahog_window* win);

/*! sleep until RGFW gets an event or the timer ends (defined by OS) */
MEDIAHOG_API void mediahog_waitForEvent(i32 waitMS);

/*! if you you want events to be queued or not.
 * This is enabled when the queue is checked with mediahog_window_checkQueuedEvent or mediahog_window_checkEvent
 * Otherwise it's disabled by default */
MEDIAHOG_API void mediahog_setQueueEvents(mediahog_bool queue);

/*!
	check all the events until there are none left and updates window structure attributes
	adds them to a queue for mediahog_window_checkEvent to check if queueEvents is true
*/
MEDIAHOG_API void mediahog_pollEvents(void);

/*!
	tell mediahog_waitForEvent to stop waiting (to be ran from another thread)
*/
MEDIAHOG_API void mediahog_stopCheckEvents(void);

/** * @defgroup Input
* @{ */

MEDIAHOG_API mediahog_bool mediahog_isKeyPressed(mediahog_key key); /*!< if key is pressed during the current frame  (key code)*/

MEDIAHOG_API mediahog_bool mediahog_isKeyDown(mediahog_key key); /*!< if key is held (key code) */
MEDIAHOG_API mediahog_bool mediahog_isKeyReleased(mediahog_key key); /*!< if key is released (key code) */

/*! if a mouse button is pressed during the current frame */
MEDIAHOG_API mediahog_bool mediahog_isMousePressed(mediahog_mouseButton button /*!< mouse button code */ );
/*! if a mouse button is down */
MEDIAHOG_API mediahog_bool mediahog_isMouseDown(mediahog_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was released */
MEDIAHOG_API mediahog_bool mediahog_isMouseReleased(mediahog_mouseButton button /*!< mouse button code */ );
/*! get the current scroll value (of the frame) */
MEDIAHOG_API void mediahog_getMouseScroll(float* x, float* y);
/*! get the current vector value (of the frame) */
MEDIAHOG_API void mediahog_getMouseVector(float* x, float* y);
/** @} */

/* NOTE: (windows) if the executable has an icon resource named mediahog_ICON, it will be set as the initial icon for the window */

MEDIAHOG_API mediahog_window* mediahog_createWindow(
	const char* name, /* name of the window */
	i32 x, i32 y, /* position of the window */
	i32 w, i32 h, /* size of the window */
	mediahog_windowFlags flags /* extra arguments ((u32)0 means no flags used)*/
); /*!< function to create a window and struct */

MEDIAHOG_API mediahog_window* mediahog_createWindowPtr(
	const char* name, /* name of the window */
	i32 x, i32 y, /* position of the window */
	i32 w, i32 h, /* size of the window */
	mediahog_windowFlags flags, /* extra arguments (NULL / (u32)0 means no flags used) */
	mediahog_window* win/* ptr to the fat window struct you want to use */
); /*!< function to create a window (without allocating a window struct) */


/*
 * NOTE: when you create a surface using mediahog_createSurface / ptr, on X11 it uses the root window's visual
 * this means it may fail to render on any other window if the visual does not match
 * mediahog_window_createSurface and mediahog_window_createSurfacePtr exist only for X11 to address this issues
 * Of course, you can also manually set the root window with mediahog_setRootWindow
 */
MEDIAHOG_API mediahog_surface* mediahog_window_createSurface(mediahog_window* win, u8* data, i32 w, i32 h, mediahog_format format);
MEDIAHOG_API mediahog_bool mediahog_window_createSurfacePtr(mediahog_window* win, u8* data, i32 w, i32 h, mediahog_format format, mediahog_surface* surface);

/*! render the software rendering buffer */
MEDIAHOG_API void mediahog_window_blitSurface(mediahog_window* win, mediahog_surface* surface);

MEDIAHOG_API mediahog_bool mediahog_window_getPosition(mediahog_window* win, i32* x, i32* y); /*!< gets the position of the window | with mediahog_window.x and window.y */
MEDIAHOG_API mediahog_bool mediahog_window_getSize(mediahog_window* win, i32* w, i32* h);  /*!< gets the size of the window | with mediahog_window.w and window.h */

MEDIAHOG_API u32 mediahog_window_getFlags(mediahog_window* win); /*!< gets the flags of the window | returns mediahog_window._flags */

MEDIAHOG_API mediahog_key mediahog_window_getExitKey(mediahog_window* win); /*!< get the exit key for the window | returns mediahog_window.exitKey */
MEDIAHOG_API void mediahog_window_setExitKey(mediahog_window* win, mediahog_key key); /*!< set the exit key for the window |edits mediahog_window.exitKey */

/*! sets the types of events you want to receive, mediahog_allEventFlags by default (modifies mediahog_window._enabledEvents) */
MEDIAHOG_API void mediahog_window_setEnabledEvents(mediahog_window* win, mediahog_eventFlag events);
/*! gets all enabled events  mediahog_window._enabledEvents (returns mediahog_window._enabledEvents) */
MEDIAHOG_API mediahog_eventFlag mediahog_window_getEnabledEvents(mediahog_window* win);
/*! enables all events and then disables select events (modifies mediahog_window._enabledEvents)*/
MEDIAHOG_API void mediahog_window_setDisabledEvents(mediahog_window* win, mediahog_eventFlag events);
/*! directly enables or disabled a specific event, (or cluster of events) (modifies mediahog_window._enabledEvents */
MEDIAHOG_API void mediahog_window_setEventState(mediahog_window* win, mediahog_eventFlag event, mediahog_bool state);

MEDIAHOG_API void* mediahog_window_getUserPtr(mediahog_window* win); /*!< gets the userPtr of the window | returns mediahog_window.userPtr */
MEDIAHOG_API void mediahog_window_setUserPtr(mediahog_window* win, void* ptr); /*!< sets the userPtr of the window | writes to mediahog_window.userPtr */

MEDIAHOG_API mediahog_window_src* mediahog_window_getSrc(mediahog_window* win); /*!< returns fat pointer of window, which is sourced from the window casted to the fast pointer */

/* thiese functions return data from the `mediahog_window_src` object in `mediahog_window`, they return NULL if the platform is not in use.
 * (e.g. when trying to get OSX data on Windows) */
MEDIAHOG_API void mediahog_window_setLayer_OSX(mediahog_window* win, void* layer);
MEDIAHOG_API void* mediahog_window_getView_OSX(mediahog_window* win);
MEDIAHOG_API void* mediahog_window_getWindow_OSX(mediahog_window* win);
MEDIAHOG_API void* mediahog_window_getHWND(mediahog_window* win);
MEDIAHOG_API void* mediahog_window_getHDC(mediahog_window* win);
MEDIAHOG_API u64 mediahog_window_getWindow_X11(mediahog_window* win);
MEDIAHOG_API struct wl_surface* mediahog_window_getWindow_Wayland(mediahog_window* win);

/** * @defgroup Window_management
* @{ */

/*! set the window flags (will undo flags if they don't match the old ones) */
MEDIAHOG_API void mediahog_window_setFlags(mediahog_window* win, mediahog_windowFlags);

/*!
	polls the event queue if it's empty and pops the first event for the window from the event queue
	using this function without a while loop may cause event lag

	because this function polls events, it may not work for multi-threaded systems
	mediahog_pollEvents + mediahog_window_checkQueuedEvent should be used when using multi-threaded systems

	ex.

	mediahog_event;
	while (mediahog_window_checkEvent(win, &event)) [this keeps checking events until it reaches the last queued event]

	you may also use `mediahog_pollEvents` instead
*/
MEDIAHOG_API mediahog_bool mediahog_window_checkEvent(mediahog_window* win, mediahog_event* event); /*!< check current event (returns mediahog_TRUE if there is an event or mediahog_FALSE if there is no event)*/
/*! pops the first event for the window from the event queue */
MEDIAHOG_API mediahog_bool mediahog_window_checkQueuedEvent(mediahog_window* win, mediahog_event* event);

/*! checks only if the key is pressed while the window in focus. */
MEDIAHOG_API mediahog_bool mediahog_window_isKeyPressed(mediahog_window* win, mediahog_key key); /*!< if key is pressed (key code)*/

MEDIAHOG_API mediahog_bool mediahog_window_isKeyDown(mediahog_window* win, mediahog_key key); /*!< if key is held (key code) */
MEDIAHOG_API mediahog_bool mediahog_window_isKeyReleased(mediahog_window* win, mediahog_key key); /*!< if key is released (key code) */

/*! if a mouse button is pressed */
MEDIAHOG_API mediahog_bool mediahog_window_isMousePressed(mediahog_window* win, mediahog_mouseButton button /*!< mouse button code */ );
/*! if a mouse button is down */
MEDIAHOG_API mediahog_bool mediahog_window_isMouseDown(mediahog_window* win, mediahog_mouseButton button /*!< mouse button code */ );
/*! if a mouse button was released */
MEDIAHOG_API mediahog_bool mediahog_window_isMouseReleased(mediahog_window* win, mediahog_mouseButton button /*!< mouse button code */ );
/*! if the mouse left the window, only true for the first frame */
MEDIAHOG_API mediahog_bool mediahog_window_didMouseLeave(mediahog_window* win);
/*! if the mouse enter the window, only true for the first frame */
MEDIAHOG_API mediahog_bool mediahog_window_didMouseEnter(mediahog_window* win);
/*! if the mouse is within the window or not */
MEDIAHOG_API mediahog_bool mediahog_window_isMouseInside(mediahog_window* win);

/*! if there is data being dragged to/in the window, only true for the first frame */
MEDIAHOG_API mediahog_bool mediahog_window_isDataDragging(mediahog_window* win);
/*! gets the drag point, returns true if if there is data being dragged to/in the window, only true for the first frame */
MEDIAHOG_API mediahog_bool mediahog_window_getDataDrag(mediahog_window* win, i32* x, i32* y);
/* true the first frame there was a data drop (drag and drop) to the window */
MEDIAHOG_API mediahog_bool mediahog_window_didDataDrop(mediahog_window* win);
/* sets file pointer to the internal files pointer, fills count with the number of files, true the first frame there was a data drop (drag and drop) to the window */
MEDIAHOG_API mediahog_bool mediahog_window_getDataDrop(mediahog_window* win, const char*** files, size_t* count);

/*! window managment functions */
MEDIAHOG_API void mediahog_window_close(mediahog_window* win); /*!< close the window and free the window struct */
MEDIAHOG_API void mediahog_window_closePtr(mediahog_window* win); /*!< close the window, don't free the window struct */

/*! move a window to a given point */
MEDIAHOG_API void mediahog_window_move(mediahog_window* win,
	i32 x, i32 y /*!< new pos */
);

/*! move window to a specific monitor */
MEDIAHOG_API void mediahog_window_moveToMonitor(mediahog_window* win, mediahog_monitor m /* monitor */);

/*! resize window to a current size/area */
MEDIAHOG_API void mediahog_window_resize(mediahog_window* win, /*!< source window */ i32 w, i32 h /*!< new size */);

/*! set window aspect ratio */
MEDIAHOG_API void mediahog_window_setAspectRatio(mediahog_window* win, i32 w, i32 h);
/*! set the minimum dimensions of a window */
MEDIAHOG_API void mediahog_window_setMinSize(mediahog_window* win, i32 w, i32 h);
/*! set the maximum dimensions of a window */
MEDIAHOG_API void mediahog_window_setMaxSize(mediahog_window* win,  i32 w, i32 h);

MEDIAHOG_API void mediahog_window_focus(mediahog_window* win); /*!< sets the focus to this window */
MEDIAHOG_API mediahog_bool mediahog_window_isInFocus(mediahog_window* win); /*!< checks the focus to this window */
MEDIAHOG_API void mediahog_window_raise(mediahog_window* win); /*!< raise the window (to the top) */
MEDIAHOG_API void mediahog_window_maximize(mediahog_window* win); /*!< maximize the window */
MEDIAHOG_API void mediahog_window_setFullscreen(mediahog_window* win, mediahog_bool fullscreen); /*!< turn fullscreen on / off for a window */
MEDIAHOG_API void mediahog_window_center(mediahog_window* win); /*!< center the window */
MEDIAHOG_API void mediahog_window_minimize(mediahog_window* win); /*!< minimize the window (in taskbar (per OS))*/
MEDIAHOG_API void mediahog_window_restore(mediahog_window* win); /*!< restore the window from minimized (per OS)*/
MEDIAHOG_API void mediahog_window_setFloating(mediahog_window* win, mediahog_bool floating); /*!< make the window a floating window */
MEDIAHOG_API void mediahog_window_setOpacity(mediahog_window* win, u8 opacity); /*!< sets the opacity of a window */

/*! if the window should have a border or not (borderless) based on bool value of `border` */
MEDIAHOG_API void mediahog_window_setBorder(mediahog_window* win, mediahog_bool border);
MEDIAHOG_API mediahog_bool mediahog_window_borderless(mediahog_window* win);

/*! turn on / off dnd (mediahog_windowAllowDND stil must be passed to the window)*/
MEDIAHOG_API void mediahog_window_setDND(mediahog_window* win, mediahog_bool allow);
/*! check if DND is allowed */
MEDIAHOG_API mediahog_bool mediahog_window_allowsDND(mediahog_window* win);


/*! turn on / off mouse passthrough */
MEDIAHOG_API void mediahog_window_setMousePassthrough(mediahog_window* win, mediahog_bool passthrough);

/*! rename window to a given string */
MEDIAHOG_API void mediahog_window_setName(mediahog_window* win,
	const char* name
);

/*!< image MAY be resized by default, set both the taskbar and window icon */
MEDIAHOG_API mediahog_bool mediahog_window_setIcon(mediahog_window* win, u8* data, i32 w, i32 h, mediahog_format format);
MEDIAHOG_API mediahog_bool mediahog_window_setIconEx(mediahog_window* win, u8* data, i32 w, i32 h, mediahog_format format, mediahog_icon type);

/*!< sets mouse to mediahog_mouse icon (loaded from a bitmap struct) */
MEDIAHOG_API void mediahog_window_setMouse(mediahog_window* win, mediahog_mouse* mouse);

/*!< sets the mouse to a standard API cursor (based on mediahog_MOUSE, as seen at the end of the mediahog_HEADER part of this file) */
MEDIAHOG_API	mediahog_bool mediahog_window_setMouseStandard(mediahog_window* win, mediahog_mouseIcons mouse);

MEDIAHOG_API mediahog_bool mediahog_window_setMouseDefault(mediahog_window* win); /*!< sets the mouse to the default mouse icon */
/*
	Locks cursor at the center of the window
	x, y becomes raw mouse movement data

	this is useful for a 3D camera
*/
MEDIAHOG_API void mediahog_window_holdMouse(mediahog_window* win);
/*! if the mouse is held by RGFW */
MEDIAHOG_API mediahog_bool mediahog_window_isHoldingMouse(mediahog_window* win);
/*! stop holding the mouse and let it move freely */
MEDIAHOG_API void mediahog_window_unholdMouse(mediahog_window* win);

/*! hide the window */
MEDIAHOG_API void mediahog_window_hide(mediahog_window* win);
/*! show the window */
MEDIAHOG_API void mediahog_window_show(mediahog_window* win);

/*
	makes it so `mediahog_window_shouldClose` returns true or overrides a window close
	by modifying window flags
*/
MEDIAHOG_API void mediahog_window_setShouldClose(mediahog_window* win, mediahog_bool shouldClose);

/*! where the mouse is on the screen */
MEDIAHOG_API mediahog_bool mediahog_getGlobalMouse(i32* x, i32* y);

/*! where the mouse is on the window */
MEDIAHOG_API mediahog_bool mediahog_window_getMouse(mediahog_window* win, i32* x, i32* y);

/*! show the mouse or hide the mouse */
MEDIAHOG_API void mediahog_window_showMouse(mediahog_window* win, mediahog_bool show);
/*! if the mouse is hidden */
MEDIAHOG_API mediahog_bool mediahog_window_isMouseHidden(mediahog_window* win);
/*! move the mouse to a given point */
MEDIAHOG_API void mediahog_window_moveMouse(mediahog_window* win, i32 x, i32 y);

/*! if the window should close (mediahog_close was sent or escape was pressed) */
MEDIAHOG_API mediahog_bool mediahog_window_shouldClose(mediahog_window* win);
/*! if the window is fullscreen */
MEDIAHOG_API mediahog_bool mediahog_window_isFullscreen(mediahog_window* win);
/*! if the window is hidden */
MEDIAHOG_API mediahog_bool mediahog_window_isHidden(mediahog_window* win);
/*! if the window is minimized */
MEDIAHOG_API mediahog_bool mediahog_window_isMinimized(mediahog_window* win);
/*! if the window is maximized */
MEDIAHOG_API mediahog_bool mediahog_window_isMaximized(mediahog_window* win);
/*! if the window is floating */
MEDIAHOG_API mediahog_bool mediahog_window_isFloating(mediahog_window* win);
/** @} */

/** * @defgroup Monitor
* @{ */

/*
	scale the window to the monitor.
	This is run by default if the user uses the arg `mediahog_scaleToMonitor` during window creation
*/
MEDIAHOG_API void mediahog_window_scaleToMonitor(mediahog_window* win);
/*! get the struct of the window's monitor  */
MEDIAHOG_API mediahog_monitor mediahog_window_getMonitor(mediahog_window* win);

/** @} */
MEDIAHOG_API void mediahog_sendDebugInfo(mediahog_debugType type, mediahog_errorCode err, const char* msg);
/** @} */

/**


	event callbacks.
	These are completely optional, so you can use the normal
	mediahog_checkEvent() method if you prefer that

* @defgroup Callbacks
* @{
*/
/*! set callback for a window move event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_windowMovedfunc mediahog_setWindowMovedCallback(mediahog_windowMovedfunc func);
/*! set callback for a window resize event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_windowResizedfunc mediahog_setWindowResizedCallback(mediahog_windowResizedfunc func);
/*! set callback for a window quit event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_windowQuitfunc mediahog_setWindowQuitCallback(mediahog_windowQuitfunc func);
/*! set callback for a mouse move event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_mousePosfunc mediahog_setMousePosCallback(mediahog_mousePosfunc func);
/*! set callback for a window refresh event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_windowRefreshfunc mediahog_setWindowRefreshCallback(mediahog_windowRefreshfunc func);
/*! set callback for a window focus change event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_focusfunc mediahog_setFocusCallback(mediahog_focusfunc func);
/*! set callback for a mouse notify event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_mouseNotifyfunc mediahog_setMouseNotifyCallback(mediahog_mouseNotifyfunc func);
/*! set callback for a drop event event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_dataDropfunc mediahog_setDataDropCallback(mediahog_dataDropfunc func);
/*! set callback for a start of a drop event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_dataDragfunc mediahog_setDataDragCallback(mediahog_dataDragfunc func);
/*! set callback for a key (press / release) event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_keyfunc mediahog_setKeyCallback(mediahog_keyfunc func);
/*! set callback for a mouse button (press / release) event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_mouseButtonfunc mediahog_setMouseButtonCallback(mediahog_mouseButtonfunc func);
/*! set callback for a mouse scale  event. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_mouseScrollfunc mediahog_setMouseScrollCallback(mediahog_mouseScrollfunc func);
/*! set call back for when window is maximized. Returns the previous callback function (if it was set) */
MEDIAHOG_API mediahog_windowMaximizedfunc mediahog_setWindowMaximizedCallback(mediahog_windowMaximizedfunc func);
/*! set call back for when window is minimized. Returns the previous callback function (if it was set) */
MEDIAHOG_API mediahog_windowMinimizedfunc mediahog_setWindowMinimizedCallback(mediahog_windowMinimizedfunc func);
/*! set call back for when window is restored. Returns the previous callback function (if it was set) */
MEDIAHOG_API mediahog_windowRestoredfunc mediahog_setWindowRestoredCallback(mediahog_windowRestoredfunc func);
/*! set callback for when the DPI changes. Returns previous callback function (if it was set)  */
MEDIAHOG_API mediahog_scaleUpdatedfunc mediahog_setScaleUpdatedCallback(mediahog_scaleUpdatedfunc func);
/** @} */

/** * @defgroup graphics_API
* @{ */

/*! set global OpenGL hints to your pointer */
MEDIAHOG_API void mediahog_setGlobalHints_OpenGL(mediahog_glHints* hints);
/*! reset global OpenGL hints to the defaults */
MEDIAHOG_API void mediahog_resetGlobalHints_OpenGL(void);
/*! get the current global OpenGL hint pointer */
MEDIAHOG_API mediahog_glHints* mediahog_getGlobalHints_OpenGL(void);

/* these are native opengl specific functions and will NOT work with EGL */

/*!< make the window the current OpenGL drawing context

	NOTE:
 	if you want to switch the graphics context's thread,
	you have to run mediahog_window_makeCurrentContext_OpenGL(NULL); on the old thread
	then mediahog_window_makeCurrentContext_OpenGL(valid_window) on the new thread
*/


/*!< creates and allocates an OpenGL context for the RGFW window */
MEDIAHOG_API mediahog_glContext* mediahog_window_createContext_OpenGL(mediahog_window* win, mediahog_glHints* hints);
/*!< create an OpenGL context for the RGFW window using the user supplied context struct */
MEDIAHOG_API mediahog_bool mediahog_window_createContextPtr_OpenGL(mediahog_window* win, mediahog_glContext* ctx, mediahog_glHints* hints);
/*!, get the context that is tied to the window, returns NULL if there is no context OR if the context is a EGL context */
MEDIAHOG_API mediahog_glContext* mediahog_window_getContext_OpenGL(mediahog_window* win);
/*!< deletes and frees the opengl context | this will be automatically called by `mediahog_window_close` if the window's context is not NULL */
MEDIAHOG_API void mediahog_window_deleteContext_OpenGL(mediahog_window* win, mediahog_glContext* ctx);
/*!< deletes the opengl context | this will be automatically called by `mediahog_window_close` if the window's context is not NULL */
MEDIAHOG_API void mediahog_window_deleteContextPtr_OpenGL(mediahog_window* win, mediahog_glContext* ctx);

MEDIAHOG_API void* mediahog_glContext_getSourceContext(mediahog_glContext* ctx);

MEDIAHOG_API void mediahog_window_makeCurrentWindow_OpenGL(mediahog_window* win); /*!< to be called by mediahog_window_makeCurrent */
MEDIAHOG_API void mediahog_window_makeCurrentContext_OpenGL(mediahog_window* win); /*!< to be called by mediahog_window_makeCurrent */
MEDIAHOG_API void mediahog_window_swapBuffers_OpenGL(mediahog_window* win); /*!< swap OpenGL buffer (only) called by mediahog_window_swapInterval  */

MEDIAHOG_API void* mediahog_getCurrentContext_OpenGL(void); /*!< get the current context (OpenGL backend (GLX) (WGL) (cocoa) (webgl))*/
MEDIAHOG_API mediahog_window* mediahog_getCurrentWindow_OpenGL(void); /*!< get the current window (set by mediahog_window_makeCurrentWindow) */

/*! set swapInterval / enable vsync */
MEDIAHOG_API void mediahog_window_swapInterval_OpenGL(mediahog_window* win, i32 swapInterval);

MEDIAHOG_API mediahog_proc mediahog_getProcAddress_OpenGL(const char* procname); /*!< get native OpenGL proc address */
MEDIAHOG_API mediahog_bool mediahog_extensionSupported_OpenGL(const char* extension, size_t len);	/*!< check if whether the specified API extension is supported by the current OpenGL or OpenGL ES context */
MEDIAHOG_API mediahog_bool mediahog_extensionSupportedPlatform_OpenGL(const char* extension, size_t len);	/*!< check if whether the specified platform-specific API extension is supported by the current OpenGL or OpenGL ES context */

/* these are EGL specific functions, they may fallback to OpenGL */
/*!< creates and allocates an OpenGL/EGL context for the RGFW window */
MEDIAHOG_API mediahog_eglContext* mediahog_window_createContext_EGL(mediahog_window* win, mediahog_glHints* hints);
/*!< creates an OpenGL/EGL context for the RGFW window using the user supplied context struct */
MEDIAHOG_API mediahog_bool mediahog_window_createContextPtr_EGL(mediahog_window* win, mediahog_eglContext* ctx, mediahog_glHints* hints);
/*!< frees and deletes an OpenGL/EGL context | called by `mediahog_window_close` if RGFW owns the context */
MEDIAHOG_API void mediahog_window_deleteContext_EGL(mediahog_window* win, mediahog_eglContext* ctx);
/*!< deletes an OpenGL/EGL context | called by `mediahog_window_close` if RGFW owns the context */
MEDIAHOG_API void mediahog_window_deleteContextPtr_EGL(mediahog_window* win, mediahog_eglContext* ctx);
/*!, get the context that is tied to the window, returns NULL if there is no context OR if the context is a native OpenGL context */
MEDIAHOG_API mediahog_eglContext* mediahog_window_getContext_EGL(mediahog_window* win);

MEDIAHOG_API void* mediahog_getDisplay_EGL(void);
MEDIAHOG_API void* mediahog_eglContext_getSourceContext(mediahog_eglContext* ctx);
MEDIAHOG_API void* mediahog_eglContext_getSurface(mediahog_eglContext* ctx);
MEDIAHOG_API struct wl_egl_window* mediahog_eglContext_wlEGLWindow(mediahog_eglContext* ctx);

MEDIAHOG_API void mediahog_window_swapBuffers_EGL(mediahog_window* win); /*!< swap OpenGL buffer (only) called by mediahog_window_swapInterval  */

MEDIAHOG_API void mediahog_window_makeCurrentWindow_EGL(mediahog_window* win); /*!< to be called by mediahog_window_makeCurrent */
MEDIAHOG_API void mediahog_window_makeCurrentContext_EGL(mediahog_window* win); /*!< to be called by mediahog_window_makeCurrent */

MEDIAHOG_API void* mediahog_getCurrentContext_EGL(void); /*!< get the current context (EGL)*/
MEDIAHOG_API mediahog_window* mediahog_getCurrentWindow_EGL(void); /*!< get the current window (set by mediahog_window_makeCurrentWindow) (EGL)*/

/*! set swapInterval / enable vsync */
MEDIAHOG_API void mediahog_window_swapInterval_EGL(mediahog_window* win, i32 swapInterval);

MEDIAHOG_API mediahog_proc mediahog_getProcAddress_EGL(const char* procname); /*!< get native OpenGL proc address */
MEDIAHOG_API mediahog_bool mediahog_extensionSupported_EGL(const char* extension, size_t len);	/*!< check if whether the specified API extension is supported by the current OpenGL or OpenGL ES context */
MEDIAHOG_API mediahog_bool mediahog_extensionSupportedPlatform_EGL(const char* extension, size_t len);	/*!< check if whether the specified platform-specific API extension is supported by the current OpenGL or OpenGL ES context */

/*
 * Rendering API
 * these are functions for mediahog's rendering subsystem
*/

#endif
