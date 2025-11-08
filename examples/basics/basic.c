#include <hoglib.h>

int main() {
	hl_windowHandle window = hl_createWindow("window", 800, 600, HL_RENDERER_GL_MODERN);
	hl_textureHandle texture = hl_loadTextureFromImage(window, "logo.png");

	while (hl_windowShouldClose(window) == false) {
		hl_pollEvents();
		if (hl_isKeyPressed(HL_KEY_ESCAPE)) {
			break;
		}

		hl_startFrame(window);

		hl_clear(window, HL_RGB(255, 255, 255));

		hl_setColor(window, HL_RGB(255, 0, 0));
		hl_drawRect(window, HL_RECT(20, 20, 100, 100));

		hl_setTexture(window, texture);
		hl_setColor(window, HL_RGB(255, 255, 255));
		hl_drawRect(window, HL_RECT(50, 50, 200, 200));

		hl_finishFrame(window);
	}

	hl_releaseTexture(window, texture);

	hl_closeWindow(window);
}
