#include <hoglib.h>

int main(void) {
	hl_windowHandle window = hl_createWindow("window", 800, 600, HL_RENDERER_GL_MODERN);

	while (hl_windowShouldClose(window) == false) {
		hl_pollEvents();
		if (hl_isKeyPressed(HL_KEY_ESCAPE)) {
			break;
		}

		hl_startFrame(window);

		hl_clear(window, HL_RGB(255, 255, 255));

		hl_setColor(window, HL_RGB(255, 0, 0));
		hl_drawRect(window, HL_RECT(20, 20, 100, 100));

		hl_finishFrame(window);
	}

	hl_closeWindow(window);
}
