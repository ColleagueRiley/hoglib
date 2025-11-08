#include <hoglib.h>

HL_API void hl_updateRendererSize(hl_windowHandle window);

HL_API void hl_setWindowRenderer(hl_windowHandle window, hl_rendererHandle renderer);

/* OpenGL Native API */

/**!
 * @brief Swaps the OpenGL buffers for the specified window.
 * @param handle to the window object
*/
HL_API void hl_swapBuffers(hl_windowHandle window);

/**!
 * @brief Retrieves the address of a native OpenGL procedure.
 * @param procname The name of the OpenGL function to look up.
 * @return A pointer to the function, or NULL if not found.
*/
HL_API hl_proc hl_getProcAddress(const char* procname);

/**!
 * @brief make the window this current OpenGL context
 * @param handle to the window object
*/
HL_API void hl_makeCurrentContext(hl_windowHandle window);

/**!
 * @brief Sets the OpenGL swap interval (vsync).
 * @param swapInterval The desired swap interval value (0 to disable vsync, 1 to enable).
 * @param handle to the window object
*/
HL_API void hl_swapInterval(hl_windowHandle window, int32_t swapInterval);

