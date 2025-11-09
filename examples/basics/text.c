#include <hoglib.h>

int main() {
	hl_windowHandle window = hl_createWindow("window", 800, 600, HL_RENDERER_GL_MODERN);

	hl_fontHandle font = hl_loadFont(window, "COMICSANS.ttf", 60);
	hl_setFont(window, font);

	while (hl_windowShouldClose(window) == false) {
		hl_pollEvents();
		if (hl_isKeyPressed(HL_KEY_ESCAPE)) {
			break;
		}

		hl_startFrame(window);

		hl_clear(window, HL_RGB(255, 255, 255));

		hl_drawText(window, "text", 400, 100, 60);

		hl_finishFrame(window);
	}

	hl_releaseFont(window, font);

	hl_closeWindow(window);
}
