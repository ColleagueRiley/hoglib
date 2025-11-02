#include <hoglib.h>

#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#include "RGFW.h"


void hl_pollEvents(void) {
	RGFW_pollEvents();
}

hl_windowHandle hl_window_init(const char* name, int32_t x, int32_t y, int32_t width, int32_t height, hl_windowFlags flags) {
	RGFW_window* window = RGFW_createWindow(name, 0, 0, width, height, flags);

	return (hl_windowHandle)window;
}

bool hl_window_shouldClose(hl_windowHandle window) {
	return RGFW_window_shouldClose((RGFW_window*)window);
}

void hl_window_close(hl_windowHandle window) {
	RGFW_window_close((RGFW_window*)window);
}

void hl_window_swapBuffers_OpenGL(hl_windowHandle window) {
	RGFW_window_swapBuffers_OpenGL((RGFW_window*)window);
}
