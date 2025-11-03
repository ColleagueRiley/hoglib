#include <hoglib.h>

int main() {
	hl_windowHandle window = hl_window_init("window", 0, 0, 800, 600, hl_windowOpenGLModern | hl_windowCenter);
	hl_rendererHandle renderer = hl_window_getRenderer(window);

	hl_textureHandle texture = hl_renderer_createTextureFromImage(renderer, "logo.png");

	while (hl_window_shouldClose(window) == false) {
		hl_pollEvents();
		if (hl_isKeyPressed(hl_escape)) {
			break;
		}

		hl_renderer_start(renderer);

		hl_clear(HL_RGB(255, 255, 255));

		hl_setTexture(0);
		hl_setColor(HL_RGB(255, 0, 0));
		hl_drawRect(HL_RECT(20, 20, 100, 100));

		hl_setTexture(texture);
		hl_setColor(HL_RGB(255, 255, 255));
		hl_drawRect(HL_RECT(50, 50, 200, 200));

		hl_renderer_finish();
	}

	hl_renderer_freeTexture(renderer, texture);

	hl_window_close(window);
}
