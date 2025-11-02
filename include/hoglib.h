/*
* Hoglib 0.1 pre-alpha

*
* Hoglib is a multimedia abstraction library that
* combines serveral of my lightweight libraries into one cohesive library
*

* Copyright (C) 2025 Riley Mabb (@ColleagueRiley)
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

#ifndef HL_HEADER

#define HL_HEADER

/*
* This is here to ensure the functions have the correct visibility
*/

#if defined(HL_EXPORT) ||  defined(HL_IMPORT)
	#if defined(_WIN32)
		#if defined(__TINYC__) && (defined(HL_EXPORT) ||  defined(HL_IMPORT))
			#define __declspec(x) __attribute__((x))
		#endif

		#if defined(HL_EXPORT)
			#define HL_API __declspec(dllexport)
		#else
			#define HL_API __declspec(dllimport)
		#endif
	#else
		#if defined(HL_EXPORT)
			#define HL_API __attribute__((visibility("default")))
		#endif
	#endif
    #ifndef HL_API
        #define HL_API
    #endif
#endif

#ifndef HL_API
	#define HL_API
#endif

/* useful macros
 * these are macros I find useful for the Hoglib header
*/

/* returns the value of the nth bit (e.g.) 2 -> 4, 3 -> 8  */
/* this is useful for enum flags */
#define HL_BIT(n) (1 << (n))


/*
 * Currently, Hoglib is made for C99 and will use C99 types
 * stdint : standardized int types, 'int64_t', rather than default ctypes 'int'
 * stdbool : standardized bool type so Hoglib doesn't have to have a custom bool type
 * stddef : size_t and other standard size types
*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


/*
 * Hoglib types, these are types that will be used by/for Hoglib
*/


/*
 * Global types
 * these types are used across the entire Hoglib API
*/

/* Enum values for all of Hoglib's subsystems
 * These are used when requesting which subsystems you would like to initalize
*/
typedef enum hl_subsystems {
	HL_WINDOWING = HL_BIT(0), /* basic windowing features */
	HL_GRAPHICS = HL_BIT(1), /* rendering and graphical features */

	/* combos of enums to make it easier to init Hoglib */
	HL_VIDEO = HL_WINDOWING | HL_GRAPHICS
} hl_subsystems;

/*! @brief function pointer equivalent of void* */
typedef void (*hl_proc)(void);

typedef enum hl_textureFormat {
	hl_formatNone = 0,
	hl_formatRGB,    /*!< 8-bit RGB (3 channels) */
    hl_formatBGR,    /*!< 8-bit BGR (3 channels) */
	hl_formatRGBA,   /*!< 8-bit RGBA (4 channels) */
    hl_formatBGRA,   /*!< 8-bit BGRA (4 channels) */
    hl_formatRed,   /*!< 8-bit RED (1 channel) */
    hl_formatGrayscale,   /*!< 8-bit grayscale (1 channel) */
    hl_formatGrayscaleAlpha,   /*!< 8-bit grayscale alpha (1 channel) */
	hl_formatCount
} hl_textureFormat;

typedef enum hl_textureDataType {
	hl_textureDataInt = 0,
	hl_textureDataFloat
} hl_textureDataType;

typedef enum hl_textureFilter {
	hl_filterNearest = 0,
	hl_filterLinear
} hl_textureFilter;

typedef struct hl_textureBlob {
	void* data; /* input data */
	size_t width; /* width of the texture */
	size_t height; /* height of the texture */
	hl_textureDataType dataType;
	hl_textureFormat dataFormat; /* format of the input data */
	hl_textureFormat textureFormat; /* final format for the texture */
	hl_textureFilter minFilter; /* filter used when rendering a surface smaller than the base texture */
	hl_textureFilter magFilter;  /* filter used when rendering a surface bigger than the base texture */
} hl_textureBlob;

/*
 * Windowing subsystem types
 * these types are for Hoglib's windowing subsystem
*/

/* Flags for creating a window */
typedef enum hl_windowFlags {
	hl_windowNoBorder = HL_BIT(0), /*!< the window doesn't have a border */
	hl_windowNoResize = HL_BIT(1), /*!< the window cannot be resized by the user */
	hl_windowAllowDND = HL_BIT(2), /*!< the window supports drag and drop */
	hl_windowHideMouse = HL_BIT(3), /*! the window should hide the mouse (can be toggled later on using `hl_window_showMouse`) */
	hl_windowFullscreen = HL_BIT(4), /*!< the window is fullscreen by default */
	hl_windowTransparent = HL_BIT(5), /*!< the window is transparent (only properly works on X11 and MacOS, although it's meant for for windows) */
	hl_windowCenter = HL_BIT(6), /*! center the window on the screen */
	hl_windowScaleToMonitor = HL_BIT(8), /*! scale the window to the screen */
	hl_windowHide = HL_BIT(9), /*! the window is hidden */
	hl_windowMaximize = HL_BIT(10),
	hl_windowCenterCursor = HL_BIT(11),
	hl_windowFloating = HL_BIT(12), /*!< create a floating window */
	hl_windowFocusOnShow = HL_BIT(13), /*!< focus the window when it's shown */
	hl_windowMinimize = HL_BIT(14), /*!< focus the window when it's shown */
	hl_windowFocus = HL_BIT(15), /*!< if the window is in focus */
	hl_windowOpenGL = HL_BIT(17), /*!< create an OpenGL context (you can also do this manually with hl_window_createContext_OpenGL) */
	hl_windowEGL = HL_BIT(18), /*!< create an EGL context (you can also do this manually with hl_window_createContext_EGL) */
	hl_windowedFullscreen = hl_windowNoBorder | hl_windowMaximize
} hl_windowFlags;

/* handle to the source RGFW window */
typedef void* hl_windowHandle;

typedef enum hl_key {
	hl_keyNULL = 0,
	hl_escape = '\033',
	hl_backtick = '`',
	hl_0 = '0',
	hl_1 = '1',
	hl_2 = '2',
	hl_3 = '3',
	hl_4 = '4',
	hl_5 = '5',
	hl_6 = '6',
	hl_7 = '7',
	hl_8 = '8',
	hl_9 = '9',
	hl_minus = '-',
	hl_equals = '=',
	hl_backSpace = '\b',
	hl_tab = '\t',
	hl_space = ' ',
	hl_a = 'a',
	hl_b = 'b',
	hl_c = 'c',
	hl_d = 'd',
	hl_e = 'e',
	hl_f = 'f',
	hl_g = 'g',
	hl_h = 'h',
	hl_i = 'i',
	hl_j = 'j',
	hl_k = 'k',
	hl_l = 'l',
	hl_m = 'm',
	hl_n = 'n',
	hl_o = 'o',
	hl_p = 'p',
	hl_q = 'q',
	hl_r = 'r',
	hl_s = 's',
	hl_t = 't',
	hl_u = 'u',
	hl_v = 'v',
	hl_w = 'w',
	hl_x = 'x',
	hl_y = 'y',
	hl_z = 'z',
	hl_period = '.',
	hl_comma = ',',
	hl_slash = '/',
	hl_bracket = '[',
    hl_closeBracket = ']',
    hl_semicolon = ';',
	hl_apostrophe = '\'',
	hl_backSlash = '\\',
	hl_return = '\n',
	hl_enter = hl_return,
	hl_delete = '\177', /* 127 */
	hl_F1,
	hl_F2,
	hl_F3,
	hl_F4,
	hl_F5,
	hl_F6,
	hl_F7,
	hl_F8,
	hl_F9,
	hl_F10,
	hl_F11,
	hl_F12,
    hl_F13,
    hl_F14,
    hl_F15,
    hl_F16,
    hl_F17,
    hl_F18,
    hl_F19,
    hl_F20,
    hl_F21,
    hl_F22,
    hl_F23,
    hl_F24,
    hl_F25,
	hl_capsLock,
	hl_shiftL,
	hl_controlL,
	hl_altL,
	hl_superL,
	hl_shiftR,
	hl_controlR,
	hl_altR,
	hl_superR,
	hl_up,
	hl_down,
	hl_left,
	hl_right,
	hl_insert,
	hl_menu,
	hl_end,
	hl_home,
	hl_pageUp,
	hl_pageDown,
	hl_numLock,
	hl_kpSlash,
	hl_kpMultiply,
	hl_kpPlus,
	hl_kpMinus,
	hl_kpEqual,
	hl_kp1,
	hl_kp2,
	hl_kp3,
	hl_kp4,
	hl_kp5,
	hl_kp6,
	hl_kp7,
	hl_kp8,
	hl_kp9,
	hl_kp0,
	hl_kpPeriod,
	hl_kpReturn,
	hl_scrollLock,
    hl_printScreen,
    hl_pause,
	hl_world1,
    hl_world2,
    hl_keyLast = 256 /* padding for alignment ~(175 by default) */
} hl_key;

/*! @brief abstract mouse button codes */
typedef enum hl_mouseButton {
	hl_mouseLeft = 0, /*!< left mouse button is pressed */
	hl_mouseMiddle, /*!< mouse-wheel-button is pressed */
	hl_mouseRight, /*!< right mouse button is pressed */
	hl_mouseMisc1, hl_mouseMisc2, hl_mouseMisc3, hl_mouseMisc4, hl_mouseMisc5,
	hl_mouseFinal
} hl_mouseButton;

/*! abstract key modifier codes */
typedef enum hl_keymod {
	hl_modCapsLock = HL_BIT(0),
	hl_modNumLock  = HL_BIT(1),
	hl_modControl  = HL_BIT(2),
	hl_modAlt = HL_BIT(3),
	hl_modShift  = HL_BIT(4),
	hl_modSuper = HL_BIT(5),
	hl_modScrollLock = HL_BIT(6)
} hl_keymod;

/*! @brief codes for the event types that can be sent */
typedef enum hl_eventType {
	hl_eventNone = 0, /*!< no event has been sent */
 	hl_keyPressed, /* a key has been pressed */
	hl_keyReleased, /*!< a key has been released */
	/*! key event note
		the code of the key pressed is stored in
		hl_event.key.value
		!!Keycodes defined at the bottom of the hl_HEADER part of this file!!

		while a string version is stored in
		hl_event.key.valueString

		hl_event.key.mod holds the current mod
		this means if CapsLock, NumLock are active or not
	*/
	hl_mouseButtonPressed, /*!< a mouse button has been pressed (left,middle,right) */
	hl_mouseButtonReleased, /*!< a mouse button has been released (left,middle,right) */
	hl_mouseScroll, /*!< a mouse scroll event */
	hl_mousePosChanged, /*!< the position of the mouse has been changed */
	/*! mouse event note
		the x and y of the mouse can be found in the vector, hl_x, y

		hl_event.button.value holds which mouse button was pressed
	*/
	hl_windowMoved, /*!< the window was moved (by the user) */
	hl_windowResized, /*!< the window was resized (by the user), [on WASM this means the browser was resized] */
	hl_focusIn, /*!< window is in focus now */
	hl_focusOut, /*!< window is out of focus now */
	hl_mouseEnter, /* mouse entered the window */
	hl_mouseLeave, /* mouse left the window */
	hl_windowRefresh, /* The window content needs to be refreshed */

	/* attribs change event note
		The event data is sent straight to the window structure
		with win->x, win->y, win->w and win->h
	*/
	hl_quit, /*!< the user clicked the quit button */
	hl_dataDrop, /*!< a file has been dropped into the window */
	hl_dataDrag, /*!< the start of a drag and drop event, when the file is being dragged */
	/* drop data note
		The x and y coords of the drop are stored in the vector hl_x, y

		hl_event.drop.count holds how many files were dropped

		This is also the size of the array which stores all the dropped file string,
		hl_event.drop.files
	*/
	hl_windowMaximized, /*!< the window was maximized */
	hl_windowMinimized, /*!< the window was minimized */
	hl_windowRestored, /*!< the window was restored */
	hl_scaleUpdated /*!< content scale factor changed */
} hl_eventType;

/*! Event structure(s) and union for checking/getting events */

/*! @brief common event data across all events */
typedef struct hl_commonEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
} hl_commonEvent;

/*! @brief event data for any mouse button event (press/release) */
typedef struct hl_mouseButtonEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	uint8_t value; /* !< which mouse button was pressed */
} hl_mouseButtonEvent;

/*! @brief event data for any mouse scroll event */
typedef struct hl_mouseScrollEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	float x, y; /*!< the raw mouse scroll value */
} hl_mouseScrollEvent;

/*! @brief event data for any mouse position event (hl_mousePosChanged) */
typedef struct hl_mousePosEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	int32_t x, y; /*!< mouse x, y of event (or drop point) */
	float vecX, vecY; /*!< raw mouse movement */
} hl_mousePosEvent;

/*! @brief event data for any key event (press/release) */
typedef struct hl_keyEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	hl_key value; /*!< the physical key of the event, refers to where key is physically !!Keycodes defined at the bottom of the hl_HEADER part of this file!! */
	uint8_t sym; /*!< mapped key char of the event */
	bool repeat; /*!< key press event repeated (the key is being held) */
	hl_keymod mod;
} hl_keyEvent;

/*! @brief event data for any data drop event */
typedef struct hl_dataDropEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	/* 260 max paths with a max length of 260 */
	char** files; /*!< dropped files */
	size_t count; /*!< how many files were dropped */
} hl_dataDropEvent;

/*! @brief event data for any data drag event */
typedef struct hl_dataDragEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	int32_t x, y; /*!< mouse x, y of event (or drop point) */
} hl_dataDragEvent;

/*! @brief event data for when the window scale (DPI) is updated */
typedef struct hl_scaleUpdatedEvent {
	hl_eventType type; /*!< which event has been sent?*/
	hl_windowHandle win; /*!< the window this event applies too (for event queue events) */
	float x, y; /*!< DPI scaling */
} hl_scaleUpdatedEvent;

/*! @brief union for all of the event stucture types */
typedef union hl_event {
	hl_eventType type; /*!< which event has been sent?*/
	hl_commonEvent common; /*!< common event data (e.g.) type and win */
	hl_mouseButtonEvent button; /*!< data for a button press/release */
	hl_mouseScrollEvent scroll; /*!< data for a mouse scroll */
	hl_mousePosEvent mouse; /*!< data for mouse motion events */
	hl_keyEvent key; /*!< data for key press/release/hold events */
	hl_dataDropEvent drop; /*!< dropping a file events */
	hl_dataDragEvent drag; /* data for dragging a file events */
	hl_scaleUpdatedEvent scale; /* data for monitor scaling events */
} hl_event;

/*! @brief the type of debug message */
typedef enum hl_debugType {
	hl_typeError = 0, hl_typeWarning, hl_typeInfo
} hl_debugType;

/*! @brief error codes for known failure types */
typedef enum hl_errorCode {
	hl_noError = 0, /*!< no error */
	hl_errOutOfMemory,
	hl_errOpenGLContext, hl_errEGLContext, /*!< error with the OpenGL context */
	hl_errWayland, hl_errX11,
	hl_errDirectXContext,
	hl_errIOKit,
	hl_errClipboard,
	hl_errFailedFuncLoad,
	hl_errBuffer,
	hl_errEventQueue,
	hl_infoMonitor, hl_infoWindow, hl_infoBuffer, hl_infoGlobal, hl_infoOpenGL,
	hl_warningWayland, hl_warningOpenGL
} hl_errorCode;

/*! @brief callback function type for debug messags */

typedef void (* hl_debugfunc)(hl_debugType type, hl_errorCode err, const char* msg);

/*! @brief hl_windowMoved, the window and its new rect value  */
typedef void (* hl_windowMovedfunc)(hl_windowHandle win, int32_t x, int32_t y);
/*! @brief hl_windowResized, the window and its new rect value  */
typedef void (* hl_windowResizedfunc)(hl_windowHandle win, int32_t w, int32_t h);
/*! @brief hl_windowRestored, the window and its new rect value  */
typedef void (* hl_windowRestoredfunc)(hl_windowHandle win, int32_t x, int32_t y, int32_t w, int32_t h);
/*! @brief hl_windowMaximized, the window and its new rect value  */
typedef void (* hl_windowMaximizedfunc)(hl_windowHandle win, int32_t x, int32_t y, int32_t w, int32_t h);
/*! @brief hl_windowMinimized, the window and its new rect value  */
typedef void (* hl_windowMinimizedfunc)(hl_windowHandle win);
/*! @brief hl_quit, the window that was closed */
typedef void (* hl_windowQuitfunc)(hl_windowHandle win);
/*! @brief hl_focusIn / hl_focusOut, the window who's focus has changed and if its in focus */
typedef void (* hl_focusfunc)(hl_windowHandle win, bool inFocus);
/*! @brief hl_mouseEnter / hl_mouseLeave, the window that changed, the point of the mouse (enter only) and if the mouse has entered */
typedef void (* hl_mouseNotifyfunc)(hl_windowHandle win, int32_t x, int32_t y, bool status);
/*! @brief hl_mousePosChanged, the window that the move happened on, and the new point of the mouse  */
typedef void (* hl_mousePosfunc)(hl_windowHandle win, int32_t x, int32_t y, float vecX, float vecY);
/*! @brief hl_dataDrag, the window, the point of the drop on the windows */
typedef void (* hl_dataDragfunc)(hl_windowHandle win, int32_t x, int32_t y);
/*! @brief hl_windowRefresh, the window that needs to be refreshed */
typedef void (* hl_windowRefreshfunc)(hl_windowHandle win);
/*! @brief hl_keyPressed / hl_keyReleased, the window that got the event, the mapped key, the physical key, the string version, the state of the mod keys, if it was a press (else it's a release) */
typedef void (* hl_keyfunc)(hl_windowHandle win, uint8_t key, uint8_t sym, hl_keymod mod, bool repeat, bool pressed);
/*! @brief hl_mouseButtonPressed / hl_mouseButtonReleased, the window that got the event, the button that was pressed, the scroll value, if it was a press (else it's a release)  */
typedef void (* hl_mouseButtonfunc)(hl_windowHandle win, hl_mouseButton button, bool pressed);
/*! @brief hl_mouseScroll, the window that got the event, the x scroll value, the y scroll value */
typedef void (* hl_mouseScrollfunc)(hl_windowHandle win, float x, float y);
/*! @brief hl_dataDrop the window that had the drop, the drop data and the number of files dropped */
typedef void (* hl_dataDropfunc)(hl_windowHandle win, char** files, size_t count);
/*! @brief hl_scaleUpdated, the window the event was sent to, content scaleX, content scaleY */
typedef void (* hl_scaleUpdatedfunc)(hl_windowHandle win, float scaleX, float scaleY);


/*
 * Renderer types
 * these types are used for the renderer section of the Hoglib API
*/

typedef enum hl_rendererType {
	hl_rendererOpenGLModern = 0, /*!< default renderer */
	hl_rendererOpenGLLegacy /*!< legacy OpenGL (0.0) renderer */
} hl_rendererType;

/* handle to the source RSGL renderer */
typedef void* hl_rendererHandle;

/* handle to a texture resource */
typedef void* hl_textureHandle;

typedef struct hl_rect { float x, y, w, h; } hl_rect;

#define HL_RECT(x, y, w, h) (hl_rect){(float)x, (float)y, (float)w, (float)h}

typedef struct hl_color {
    uint8_t a, b, g, r;
} hl_color;

#define HL_RGBA(r, g, b, a) ((hl_color){(uint8_t)(a), (uint8_t)(b), (uint8_t)(g), (uint8_t)(r)})
#define HL_RGB(r, g, b) ((hl_color){255, (uint8_t)(b), (uint8_t)(g), (uint8_t)(r)})


/*
 *
 * Hoglib API
 * these are functions for interfacing with Hoglib and it's underlying systems
 *
*/

/*
 * Global API
 * these functions are used across the entire Hoglib API
*/

/*
 * Windowing API
 * these functions are used across the entire Hoglib API
*/


/**!
* @brief check all the events until there are none left and updates window structure attributes
*/
HL_API void hl_pollEvents(void);

/** * @defgroup Input
* @{ */

/**!
 * @brief returns true if the key is pressed during the current frame
 * @param key the key code of the key you want to check
 * @return The boolean value if the key is pressed or not
*/
HL_API bool hl_isKeyPressed(hl_key key);

/**!
 * @brief returns true if the key was released during the current frame
 * @param key the key code of the key you want to check
 * @return The boolean value if the key is released or not
*/
HL_API bool hl_isKeyReleased(hl_key key);

/**!
 * @brief returns true if the key is down
 * @param key the key code of the key you want to check
 * @return The boolean value if the key is down or not
*/
HL_API bool hl_isKeyDown(hl_key key);

/**!
 * @brief returns true if the mouse button is pressed during the current frame
 * @param button the mouse button code of the button you want to check
 * @return The boolean value if the button is pressed or not
*/
HL_API bool hl_isMousePressed(hl_mouseButton button);

/**!
 * @brief returns true if the mouse button is released during the current frame
 * @param button the mouse button code of the button you want to check
 * @return The boolean value if the button is released or not
*/
HL_API bool hl_isMouseReleased(hl_mouseButton button);

/**!
 * @brief returns true if the mouse button is down
 * @param button the mouse button code of the button you want to check
 * @return The boolean value if the button is down or not
*/
HL_API bool hl_isMouseDown(hl_mouseButton button);

/**!
 * @brief outputs the current x, y position of the mouse
 * @param X [OUTPUT] a pointer for the output X value
 * @param Y [OUTPUT] a pointer for the output Y value
*/
HL_API void hl_getMouseScroll(float* x, float* y);

/**!
 * @brief outputs the current x, y movement vector of the mouse
 * @param X [OUTPUT] a pointer for the output X vector value
 * @param Y [OUTPUT] a pointer for the output Y vector value
*/
HL_API void hl_getMouseVector(float* x, float* y);
/** @} */

/**!
 * @brief creates a new window
 * @param name the requested title of the window
 * @param x the requested x position of the window
 * @param y the requested y position of the window
 * @param w the requested width of the window
 * @param h the requested height of the window
 * @param flags extra arguments ((u32)0 means no flags used)
 * @return A pointer to the newly created window structure
*/
HL_API hl_windowHandle hl_window_init(const char* name, int32_t x, int32_t y, int32_t width, int32_t height, hl_windowFlags flags);

/**!
 * @brief closes the window and frees its associated structure
 * @param win a pointer to the target window
*/
HL_API void hl_window_close(hl_windowHandle window);

/**!
 * @brief Sets whether the window should close.
 * @param handle to the window object
 * @param win The target window.
 * @param shouldClose True to signal the window should close, false to keep it open.
*/
HL_API bool hl_window_shouldClose(hl_windowHandle window);

/**!
 * @brief polls and pops the next event from the window's event queue
 * @param handle to the window object
 * @param event [OUTPUT] a pointer to store the retrieved event
 * @return hl_TRUE if an event was found, hl_FALSE otherwise
 *
 * NOTE: Using this function without a loop may cause event lag.
 * For multi-threaded systems, use hl_pollEvents combined with hl_window_checkQueuedEvent.
 *
 * Example:
 * hl_event event;
 * while (hl_window_checkEvent(win, &event)) {
 *     // handle event
 * }
*/
HL_API bool hl_window_checkEvent(hl_windowHandle window, hl_event* event);

/**!
 * @brief pops the first queued event for the window
 * @param handle to the window object
 * @param event [OUTPUT] a pointer to store the retrieved event
 * @return hl_TRUE if an event was found, hl_FALSE otherwise
*/
HL_API bool hl_window_checkQueuedEvent(hl_windowHandle window, hl_event* event);

/** * @defgroup error handling
* @{ */
/**!
 * @brief Sets the callback function to handle debug messages from RGFW.
 * @param func The function pointer to be used as the debug callback.
 * @return The previously set debug callback function.
*/
HL_API hl_debugfunc hl_setDebugCallback(hl_debugfunc func);

/**!
 * @brief Sends a debug message manually through the currently set debug callback.
 * @param type The type of debug message being sent.
 * @param err The associated error code.
 * @param msg The debug message text.
*/
HL_API void hl_sendDebugInfo(hl_debugType type, hl_errorCode err, const char* msg);
/** @} */

/**


	event callbacks.
	These are completely optional, so you can use the normal
	hl_checkEvent() method if you prefer that

* @defgroup Callbacks
* @{
*/

/**!
 * @brief Sets the callback function for window move events.
 * @param func The function to be called when the window is moved.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowMovedfunc hl_setWindowMovedCallback(hl_windowMovedfunc func);

/**!
 * @brief Sets the callback function for window resize events.
 * @param func The function to be called when the window is resized.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowResizedfunc hl_setWindowResizedCallback(hl_windowResizedfunc func);

/**!
 * @brief Sets the callback function for window quit events.
 * @param func The function to be called when the window receives a quit signal.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowQuitfunc hl_setWindowQuitCallback(hl_windowQuitfunc func);

/**!
 * @brief Sets the callback function for mouse move events.
 * @param func The function to be called when the mouse moves within the window.
 * @return The previously set callback function, if any.
*/
HL_API hl_mousePosfunc hl_setMousePosCallback(hl_mousePosfunc func);

/**!
 * @brief Sets the callback function for window refresh events.
 * @param func The function to be called when the window needs to be refreshed.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowRefreshfunc hl_setWindowRefreshCallback(hl_windowRefreshfunc func);

/**!
 * @brief Sets the callback function for focus change events.
 * @param func The function to be called when the window gains or loses focus.
 * @return The previously set callback function, if any.
*/
HL_API hl_focusfunc hl_setFocusCallback(hl_focusfunc func);

/**!
 * @brief Sets the callback function for mouse notification events.
 * @param func The function to be called when a mouse notification event occurs.
 * @return The previously set callback function, if any.
*/
HL_API hl_mouseNotifyfunc hl_setMouseNotifyCallback(hl_mouseNotifyfunc func);

/**!
 * @brief Sets the callback function for data drop events.
 * @param func The function to be called when data is dropped into the window.
 * @return The previously set callback function, if any.
*/
HL_API hl_dataDropfunc hl_setDataDropCallback(hl_dataDropfunc func);

/**!
 * @brief Sets the callback function for the start of a data drag event.
 * @param func The function to be called when data dragging begins.
 * @return The previously set callback function, if any.
*/
HL_API hl_dataDragfunc hl_setDataDragCallback(hl_dataDragfunc func);

/**!
 * @brief Sets the callback function for key press and release events.
 * @param func The function to be called when a key is pressed or released.
 * @return The previously set callback function, if any.
*/
HL_API hl_keyfunc hl_setKeyCallback(hl_keyfunc func);

/**!
 * @brief Sets the callback function for mouse button press and release events.
 * @param func The function to be called when a mouse button is pressed or released.
 * @return The previously set callback function, if any.
*/
HL_API hl_mouseButtonfunc hl_setMouseButtonCallback(hl_mouseButtonfunc func);

/**!
 * @brief Sets the callback function for mouse scroll events.
 * @param func The function to be called when the mouse wheel is scrolled.
 * @return The previously set callback function, if any.
*/
HL_API hl_mouseScrollfunc hl_setMouseScrollCallback(hl_mouseScrollfunc func);

/**!
 * @brief Sets the callback function for window maximize events.
 * @param func The function to be called when the window is maximized.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowMaximizedfunc hl_setWindowMaximizedCallback(hl_windowMaximizedfunc func);

/**!
 * @brief Sets the callback function for window minimize events.
 * @param func The function to be called when the window is minimized.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowMinimizedfunc hl_setWindowMinimizedCallback(hl_windowMinimizedfunc func);

/**!
 * @brief Sets the callback function for window restore events.
 * @param func The function to be called when the window is restored from a minimized or maximized state.
 * @return The previously set callback function, if any.
*/
HL_API hl_windowRestoredfunc hl_setWindowRestoredCallback(hl_windowRestoredfunc func);

/**!
 * @brief Sets the callback function for DPI (scale) update events.
 * @param func The function to be called when the window’s DPI or scale changes.
 * @return The previously set callback function, if any.
*/
HL_API hl_scaleUpdatedfunc hl_setScaleUpdatedCallback(hl_scaleUpdatedfunc func);
/** @} */

/**!
 * @brief Retrieves the mouse position relative to the window.
 * @param handle to the window object
 * @param x [OUTPUT] Pointer to store the X position within the window.
 * @param y [OUTPUT] Pointer to store the Y position within the window.
 * @return True if the position was successfully retrieved.
*/
HL_API bool hl_window_getMouse(hl_windowHandle window, int32_t* x, int32_t* y);

/**!
 * @brief fetch the window size
 * @param handle to the window object
 * @param [OUTPUT] pointer to int width part
 * @param [OUTPUT] pointer to int height part
*/
HL_API void hl_window_getSize(hl_windowHandle window, int32_t* width, int32_t* height);

/*
 * Rendering API
 * these are functions for Hoglib's rendering subsystem
*/

/**!
 * @brief create a renderer from an existing renderer type
 * @param the backend renderer to use
 * @return returns a handle (or NULL on failure) to the renderer
*/

HL_API hl_rendererHandle hl_renderer_init(hl_rendererType type);
HL_API void hl_renderer_free(hl_rendererHandle handle);

/**!
 * @brief setup renderer for the new frame
 * @param handle to the renderer object
*/
HL_API void hl_renderer_start(hl_rendererHandle renderer);

/**!
 * @brief finish rendering the new frame using the render data
 * @param handle to the renderer object
*/
HL_API void hl_renderer_finish(hl_rendererHandle renderer);


/**!
 * @brief clear surface to a set background color
 * @param handle to the renderer object
 * @param color object
*/
HL_API void hl_renderer_clear(hl_rendererHandle renderer, hl_color color);

/**!
 * @brief set window surface to render to
 * @param handle renderer object
 * @param handle to the window object
*/
HL_API void hl_renderer_setWindow(hl_rendererHandle renderer, hl_windowHandle window);

/**!
 * @brief create texture from raw image data
 * @param blob of texture data
 * @return handle to the created texture resource
*/
HL_API hl_textureHandle hl_createTextureFromBlob(hl_rendererHandle renderer, const hl_textureBlob* blob);

/**!
 * @brief create texture from a image file
 * @param file name string
 * @return handle to the created texture resource
*/
HL_API hl_textureHandle hl_renderer_createTextureFromImage(hl_rendererHandle renderer, const char* file);

/**!
 * @brief set texture to use for rendering
 * @param handle renderer object
 * @param handle to the texture resource
*/
HL_API void hl_renderer_setTexture(hl_rendererHandle renderer, hl_textureHandle texture);

/**!
 * @brief set draw foreground color
 * @param handle to the renderer object
 * @param color object
*/
HL_API void hl_renderer_setColor(hl_rendererHandle renderer, hl_color color);

/**!
 * @brief draw rectangle to the surface
 * @param handle to the renderer object
 * @param rect object
*/
HL_API void hl_renderer_drawRect(hl_rendererHandle renderer, hl_rect rect);

#endif
