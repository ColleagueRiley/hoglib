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

int main(void) {
    hl_windowHandle window = hl_window_init("HogLib Example", 0, 0, 800, 600,
                                            hl_windowOpenGLModern | hl_windowCenter);
    hl_rendererHandle renderer = hl_window_getRenderer(window);
    hl_textureHandle logo = hl_renderer_createTextureFromImage(renderer, "logo.png");

    while (!hl_window_shouldClose(window)) {
        hl_pollEvents();
        if (hl_isKeyPressed(hl_keyEscape))
            break;

        hl_renderer_start(renderer); /* sets the active renderer */

        hl_clear(HL_RGB(240, 240, 240));

        hl_setColor(HL_RGB(255, 0, 0));
        hl_drawRect(HL_RECT(40, 40, 120, 120));

        hl_setTexture(logo);
        hl_setColor(HL_RGB(255, 255, 255));
        hl_drawRect(HL_RECT(200, 100, 256, 256));
        hl_setTexture(0);

        hl_renderer_finish();
    }

    hl_texture_free(logo);
    hl_window_close(window);
}
```
