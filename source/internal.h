#include <hoglib.h>

HL_API void hl_renderer_updateSize(hl_rendererHandle* renderer);

HL_API void hl_window_setRenderer(hl_windowHandle window, hl_rendererHandle renderer);

/* OpenGL Native API */

/**!
 * @brief Swaps the OpenGL buffers for the specified window.
 * @param handle to the window object
*/
HL_API void hl_window_swapBuffers_OpenGL(hl_windowHandle window);

/**!
 * @brief Retrieves the address of a native OpenGL procedure.
 * @param procname The name of the OpenGL function to look up.
 * @return A pointer to the function, or NULL if not found.
*/
HL_API hl_proc hl_getProcAddress_OpenGL(const char* procname);

/**!
 * @brief make the window this current OpenGL context
 * @param handle to the window object
*/
HL_API void hl_window_makeCurrentContext_OpenGL(hl_windowHandle window);

/**!
 * @brief Sets the OpenGL swap interval (vsync).
 * @param swapInterval The desired swap interval value (0 to disable vsync, 1 to enable).
 * @param handle to the window object
*/
HL_API void hl_window_swapInterval_OpenGL(hl_windowHandle window, int32_t swapInterval);

