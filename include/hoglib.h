/*
* Hoglib 0.1 pre-alpha

*
* Hoglib is a multimedia abstraction library that
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

/*
 * Renderer types
 * these types are used for the renderer section of the Hoglib API
*/

typedef enum hl_renderer {
	hl_rendererOpenGLModern = 0, /*!< default renderer */
	hl_rendererOpenGLLegacy /*!< legacy OpenGL (1.0) renderer */
} hl_renderer;

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
 * @brief Sets whether the window should close.
 * @param win The target window.
 * @param shouldClose True to signal the window should close, false to keep it open.
*/
HL_API bool hl_window_shouldClose(hl_windowHandle window);

/**!
 * @brief closes the window and frees its associated structure
 * @param win a pointer to the target window
*/
HL_API void hl_window_close(hl_windowHandle window);


/* OpenGL Native API */

/**!
 * @brief Swaps the OpenGL buffers for the specified window.
 * @param win A pointer to the RGFW_window whose buffers should be swapped.
 *
 * @note Typically called by RGFW_window_swapInterval.
*/
HL_API void hl_window_swapBuffers_OpenGL(hl_windowHandle window);

/*
 * Rendering API
 * these are functions for Hoglib's rendering subsystem
*/

/**!
 * @brief set the global renderer
 * @param renderer backend value
*/
HL_API void hl_set_renderer(hl_renderer renderer);

#endif
