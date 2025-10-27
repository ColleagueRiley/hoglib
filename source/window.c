#include <mediahog/mediahog.h>

#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

mediahog_window* mediahog_window_init(const char* name, int32_t x, int32_t y, int32_t w, int32_t h) {
	RGFW_window* window = RGFW_createWindow(name, x, y, w, h, 0);
	return (mediahog_window*)window;
}

bool mediahog_window_should_close(mediahog_window* window) {
	RGFW_window* win = (RGFW_window*)window;
	return RGFW_window_shouldClose(win);
}

void mediahog_pollEvents(void) {
	RGFW_pollEvents();
}

void mediahog_window_free(mediahog_window* window) {
	RGFW_window* win = (RGFW_window*)window;
	RGFW_window_close(win);
}


