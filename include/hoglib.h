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

#ifdef __cplusplus
extern "C" {
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

/* math defines for help */
#ifndef HL_PI /* math pi */
    #define HL_PI 3.14159265358979323846f
#endif
#ifndef HL_DEG2RAD /* degree to radians  */
    #define HL_DEG2RAD (float)(HL_PI / 180.0f)
#endif
#ifndef HL_RAD2DEG /* radians to degrees */
    #define HL_RAD2DEG (float)(180.0f / HL_PI)
#endif



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

/*! @brief function pointer equivalent of void* */
typedef void (*hl_proc)(void);

typedef enum hl_textureFormat {
	HL_FORMAT_NONE = 0,
	HL_FORMAT_RGB,    /*!< 8-bit RGB (3 channels) */
    HL_FORMAT_BGR,    /*!< 8-bit BGR (3 channels) */
	HL_FORMAT_RGBA,   /*!< 8-bit RGBA (4 channels) */
    HL_FORMAT_BGRA,   /*!< 8-bit BGRA (4 channels) */
    HL_FORMAT_RED,   /*!< 8-bit RED (1 channel) */
    HL_FORMAT_GRAYSCALE,   /*!< 8-bit grayscale (1 channel) */
    HL_FORMAT_GRAYSCALEALPHA,   /*!< 8-bit grayscale alpha (1 channel) */
	HL_FORMAT_COUNT
} hl_textureFormat;

typedef enum hl_textureDataType {
	HL_TEXTURE_DATA_INT = 0,
	HL_TEXTURE_DATA_FLOAT
} hl_textureDataType;

typedef enum hl_textureFilter {
	HL_FILTER_NEAREST = 0,
	HL_FILTER_LINEAR
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
	HL_WINDOW_NO_BORDER = HL_BIT(0), /*!< the window doesn't have a border */
	HL_WINDOW_NO_RESIZE = HL_BIT(1), /*!< the window cannot be resized by the user */
	HL_WINDOW_ALLOW_DND = HL_BIT(2), /*!< the window supports drag and drop */
	HL_WINDOW_HIDE_MOUSE = HL_BIT(3), /*! the window should hide the mouse  */
	HL_WINDOW_FULLSCREEN = HL_BIT(4), /*!< the window is fullscreen by default */
	HL_WINDOW_OPAQUE = HL_BIT(5), /*!< the window is transparent */
	HL_WINDOW_SCALE_TO_MONITOR = HL_BIT(7), /*! scale the window to the screen */
	HL_WINDOW_HIDE = HL_BIT(8), /*! the window is hidden */
	HL_WINDOW_MAXIMIZE = HL_BIT(9),
	HL_WINDOW_FLOATING = HL_BIT(11), /*!< create a floating window */
	HL_WINDOW_FOCUS_ON_SHOW = HL_BIT(12), /*!< focus the window when it's shown */
	HL_WINDOW_MINIMIZE = HL_BIT(13), /*!< focus the window when it's shown */
	HL_WINDOW_FOCUS = HL_BIT(14), /*!< if the window is in focus */

	/* renderer flags */
	HL_RENDERER_GL_LEGACY = HL_BIT(15), /*!< use the modern OpenGL renderer */
	HL_RENDERER_GL_MODERN = HL_BIT(16), /*!< use the legacy OpenGL renderer */
} hl_windowFlags;

/* handle to the source RGFW window */
typedef void* hl_windowHandle;

typedef enum hl_keyCode {
	HL_KEY_NULL = 0,
	HL_KEY_ESCAPE = '\033',
	HL_KEY_BACKTICK = '`',
	HL_KEY_0 = '0',
	HL_KEY_1 = '1',
	HL_KEY_2 = '2',
	HL_KEY_3 = '3',
	HL_KEY_4 = '4',
	HL_KEY_5 = '5',
	HL_KEY_6 = '6',
	HL_KEY_7 = '7',
	HL_KEY_8 = '8',
	HL_KEY_9 = '9',
	HL_KEY_MINUS = '-',
	HL_KEY_EQUALS = '=',
	HL_KEY_BACKSPACE = '\b',
	HL_KEY_TAB = '\t',
	HL_KEY_SPACE = ' ',
	HL_KEY_A = 'a',
	HL_KEY_B = 'b',
	HL_KEY_C = 'c',
	HL_KEY_D = 'd',
	HL_KEY_E = 'e',
	HL_KEY_F = 'f',
	HL_KEY_G = 'g',
	HL_KEY_H = 'h',
	HL_KEY_I = 'i',
	HL_KEY_J = 'j',
	HL_KEY_K = 'k',
	HL_KEY_L = 'l',
	HL_KEY_M = 'm',
	HL_KEY_N = 'n',
	HL_KEY_O = 'o',
	HL_KEY_P = 'p',
	HL_KEY_Q = 'q',
	HL_KEY_R = 'r',
	HL_KEY_S = 's',
	HL_KEY_T = 't',
	HL_KEY_U = 'u',
	HL_KEY_V = 'v',
	HL_KEY_W = 'w',
	HL_KEY_X = 'x',
	HL_KEY_Y = 'y',
	HL_KEY_Z = 'z',
	HL_KEY_PERIOD = '.',
	HL_KEY_COMMA = ',',
	HL_KEY_SLASH = '/',
	HL_KEY_BRACKET = '[',
    HL_KEY_CLOSE_BRACKET = ']',
    HL_KEY_SEMICOLON = ';',
	HL_KEY_APOSTROPHE = '\'',
	HL_KEY_BACKSLASH = '\\',
	HL_KEY_RETURN = '\n',
	HL_KEY_ENTER = HL_KEY_RETURN,
	HL_KEY_DELETE = '\177', /* 127 */
	HL_KEY_F1,
	HL_KEY_F2,
	HL_KEY_F3,
	HL_KEY_F4,
	HL_KEY_F5,
	HL_KEY_F6,
	HL_KEY_F7,
	HL_KEY_F8,
	HL_KEY_F9,
	HL_KEY_F10,
	HL_KEY_F11,
	HL_KEY_F12,
    HL_KEY_F13,
    HL_KEY_F14,
    HL_KEY_F15,
    HL_KEY_F16,
    HL_KEY_F17,
    HL_KEY_F18,
    HL_KEY_F19,
    HL_KEY_F20,
    HL_KEY_F21,
    HL_KEY_F22,
    HL_KEY_F23,
    HL_KEY_F24,
    HL_KEY_F25,
	HL_KEY_CAPSLOCK,
	HL_KEY_SHIFT_LEFT,
	HL_KEY_CONTROL_LEFT,
	HL_KEY_ALT_LEFT,
	HL_KEY_SUPER_LEFT,
	HL_KEY_SHIFT_RIGHT,
	HL_KEY_CONTROL_RIGHT,
	HL_KEY_ALT_RIGHT,
	HL_KEY_SUPER_RIGHT,
	HL_KEY_UP,
	HL_KEY_DOWN,
	HL_KEY_LEFT,
	HL_KEY_RIGHT,
	HL_KEY_INSERT,
	HL_KEY_MENU,
	HL_KEY_END,
	HL_KEY_HOME,
	HL_KEY_PAGE_UP,
	HL_KEY_PAGE_DOWN,
	HL_KEY_NUMLOCK,
	HL_KEY_KP_SLASH,
	HL_KEY_KP_MULTIPLY,
	HL_KEY_KP_PLUS,
	HL_KEY_KP_MINUS,
	HL_KEY_KP_EQUAL,
	HL_KEY_KP_1,
	HL_KEY_KP_2,
	HL_KEY_KP_3,
	HL_KEY_KP_4,
	HL_KEY_KP_5,
	HL_KEY_KP_6,
	HL_KEY_KP_7,
	HL_KEY_KP_8,
	HL_KEY_KP_9,
	HL_KEY_KP_0,
	HL_KEY_KP_PERIOD,
	HL_KEY_KP_RETURN,
	HL_KEY_SCROLLLOCK,
    HL_KEY_PRINTSCREEN,
    HL_KEY_PAUSE,
	HL_KEY_WORLD1,
    HL_KEY_WORLD2,
    HL_KEYLast = 256 /* padding for alignment ~(175 by default) */
} hl_keyCode;

/*! @brief abstract mouse button codes */
typedef enum hl_mouseButton {
	HL_MOUSE_LEFT = 0, /*!< left mouse button is pressed */
	HL_MOUSE_MIDDLE, /*!< mouse-wheel-button is pressed */
	HL_MOUSE_RIGHT, /*!< right mouse button is pressed */
	HL_MOUSE_MISC1, HL_MOUSE_MISC2, HL_MOUSE_MISC3, HL_MOUSE_MISC4, HL_MOUSE_MISC5,
	HL_MOUSE_FINAL
} hl_mouseButton;

/*! abstract key modifier codes */
typedef enum hl_keymod {
	HL_MOD_CAPSLOCK = HL_BIT(0),
	HL_MOD_NUMLOCK  = HL_BIT(1),
	HL_MOD_CONTROL  = HL_BIT(2),
	HL_MOD_ALT = HL_BIT(3),
	HL_MOD_SHIFT  = HL_BIT(4),
	HL_MOD_SUPER = HL_BIT(5),
	HL_MOD_SCROLLLOCK = HL_BIT(6)
} hl_keymod;

/*
 * Renderer types
 * these types are used for the renderer section of the Hoglib API
*/

/* handle to the source RSGL renderer */
typedef void* hl_rendererHandle;

/* handle to a texture resource */
typedef void* hl_textureHandle;

/* handle to font resource */
typedef void* hl_fontHandle;

typedef struct hl_vec2D { float x, y; } hl_vec2D;

#define HL_VEC2D(x, y) (hl_vec2D){x, y}

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

/**!
 * @brief fetch the current time
 * @param key the key code of the key you want to check
 * @return the time in seconds
*/
HL_API double hl_getTime(void);

/**!
 * @brief sleep (wait) for a given amount of time
 * @param the amount of time to sleep in seconds
*/
HL_API void hl_sleep(double seconds);

/*
 * Windowing API
 * these functions are used across the entire Hoglib API
*/


/**!
* @brief checks all events and updates internal structures
*/
HL_API void hl_pollEvents(void);

/** * @defgroup Input
* @{ */

/**!
 * @brief returns true if the key is pressed during the current frame
 * @param key the key code of the key you want to check
 * @return The boolean value if the key is pressed or not
*/
HL_API bool hl_isKeyPressed(hl_keyCode key);

/**!
 * @brief returns true if the key was released during the current frame
 * @param key the key code of the key you want to check
 * @return The boolean value if the key is released or not
*/
HL_API bool hl_isKeyReleased(hl_keyCode key);

/**!
 * @brief returns true if the key is down
 * @param key the key code of the key you want to check
 * @return The boolean value if the key is down or not
*/
HL_API bool hl_isKeyDown(hl_keyCode key);

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
 * @param w the requested width of the window
 * @param h the requested height of the window
 * @param flags extra arguments ((u32)0 means no flags used)
 * @return A handle to the newly created window structure
*/
HL_API hl_windowHandle hl_createWindow(const char* name, int32_t width, int32_t height, hl_windowFlags flags);

/**!
 * @brief closes the window and frees its associated structure
 * @param win a handle to the target window
*/
HL_API void hl_closeWindow(hl_windowHandle window);

/**!
 * @brief Sets whether the window should close.
 * @param handle to the window object
 * @param win The target window.
 * @param shouldClose True to signal the window should close, false to keep it open.
*/
HL_API bool hl_windowShouldClose(hl_windowHandle window);

/**!
 * @brief Retrieves the mouse position relative to the window.
 * @param handle to the window object
 * @param x [OUTPUT] handle to store the X position within the window.
 * @param y [OUTPUT] handle to store the Y position within the window.
 * @return True if the position was successfully retrieved.
*/
HL_API bool hl_getWindowMouse(hl_windowHandle window, int32_t* x, int32_t* y);

/**!
 * @brief fetch the window size
 * @param handle to the window object
 * @param [OUTPUT] handle to int width part
 * @param [OUTPUT] handle to int height part
*/
HL_API void hl_getWindowSize(hl_windowHandle window, int32_t* width, int32_t* height);

/**!
 * @brief fetch the window's renderer object
 * @param the source window
 * @return returns a handle to the window's renderer object
*/
HL_API hl_rendererHandle hl_getWindowRenderer(hl_windowHandle window);

/*
 * Rendering API
 * these are functions for Hoglib's rendering subsystem
*/

/**!
 * @brief create a renderer from an existing renderer type
 * @param the backend renderer to use
 * @return returns a handle (or NULL on failure) to the renderer
*/

HL_API hl_rendererHandle hl_initRenderer(uint32_t type, hl_windowHandle window);
HL_API void hl_freeRenderer(hl_rendererHandle handle);

/**!
 * @brief setup renderer for the new frame
 * @param handle to the window surface to renderer to that includes an attached renderer
*/
HL_API void hl_startFrame(hl_rendererHandle window);

/**!
 * @brief finish rendering the new frame using the render data
 * @param handle to the window surface to renderer to that includes an attached renderer
*/
HL_API void hl_finishFrame(hl_windowHandle window);


/**!
 * @brief clear surface to a set background color
 * @param color object
*/
HL_API void hl_clear(hl_windowHandle window, hl_color color);

/**!
 * @brief create font resource from a source font file
 * @param handle to the surface object
 * @param the file name
 * @param the max height supported by the font
 * @return a handle to the created font resource objects
*/
HL_API hl_fontHandle hl_loadFont(hl_windowHandle window, const char* name, uint32_t maxHeight);

/**!
 * @brief create font resource from a source font file
 * @param handle to the surface object
 * @param handle to the font resource object
*/
HL_API void hl_releaseFont(hl_windowHandle window, hl_fontHandle font);

/**!
 * @brief create texture from raw image data
 * @param handle to the surface object
 * @param blob of texture data
 * @return handle to the created texture resource
*/
HL_API hl_textureHandle hl_loadTextureFromBlob(hl_windowHandle window, const hl_textureBlob* blob);

/**!
 * @brief create texture from a image file
 * @param handle to the surface object
 * @param file name string
 * @return handle to the created texture resource
*/
HL_API hl_textureHandle hl_loadTextureFromImage(hl_windowHandle window, const char* file);

/**!
 * @brief free the texture
 * @param handle to texture resource
*/
HL_API void hl_releaseTexture(hl_windowHandle window, hl_textureHandle texture);

/**!
 * @brief set texture to use for rendering
 * @param handle renderer object
 * @param handle to the texture resource
*/
HL_API void hl_setTextureSource(hl_windowHandle window, hl_textureHandle texture, hl_rect rect);

/**!
 * @brief set texture to use for rendering
 * @param handle renderer object
 * @param handle to the texture resource
*/
HL_API void hl_setTexture(hl_windowHandle window, hl_textureHandle texture);

/**!
 * @brief set font to use for text rendering
 * @param handle renderer object
 * @param handle to the font resource
*/
HL_API void hl_setFont(hl_windowHandle window, hl_fontHandle font);

/**!
 * @brief set font to use for text rendering based on the length of the string
 * @param handle renderer object
 * @param handle to the font resource
*/
HL_API void hl_drawTextLen(hl_windowHandle window, const char* text, size_t len, int32_t x, int32_t y, int32_t size);

/**!
 * @brief set font to use for text rendering
 * @param handle renderer object
 * @param handle to the font resource
*/
HL_API void hl_drawText(hl_windowHandle window, const char* text, int32_t x, int32_t y, int32_t size);

/**!
 * @brief set draw foreground color
 * @param handle to the surface object
 * @param color object
*/
HL_API void hl_setColor(hl_windowHandle window, hl_color color);

/**!
 * @brief draw rectangle to the surface
 * @param handle to the surface object
 * @param rect object
*/
HL_API void hl_drawRect(hl_windowHandle window, hl_rect rect);

/**!
 * @brief draw line to the surface
 * @param handle to the surface object
 * @param first endpoint object
 * @param second endpoint object
*/
HL_API void hl_drawLine(hl_windowHandle window, hl_vec2D vec1, hl_vec2D vec2);

#ifdef __cplusplus
}
#endif

#endif
