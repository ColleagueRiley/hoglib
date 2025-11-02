#include <hoglib.h>

int main() {
	hl_windowHandle window = hl_window_init("window", 0, 0, 500, 500, hl_windowOpenGLModern | hl_windowCenter);
	hl_rendererHandle renderer = hl_window_getRenderer(window);

	while (hl_window_shouldClose(window) == false) {
		hl_pollEvents();
		if (hl_isKeyPressed(hl_escape)) {
			break;
		}

		hl_renderer_start(renderer);

		hl_renderer_clear(renderer, HL_RGB(255, 255, 255));

		hl_renderer_setColor(renderer, HL_RGB(255, 0, 0));
		hl_renderer_drawRect(renderer, HL_RECT(20, 20, 100, 100));

		hl_renderer_finish(renderer);
	}

	hl_window_close(window);
}
