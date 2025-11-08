# hoglib
**Integrated toolset for frictionless graphics development**

Hoglive is a lightweight C framework for building desktop focused graphics applications, games and tools. It provides a depedency free API build on a strong base with RGFW, RSGL and other lightweight single header of mine to avoid pain points when integrating them.


# Features

- Cross-platform windowing (Windows, Linux, macOS, Web)
- Simple immediate-mode 2D renderer
- easily replaceable and extendable rendering backend
- Explicit handles with minimal global state

# Example

Basic hoglib example

```c
#include <hoglib.h>

int main() {
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
```
