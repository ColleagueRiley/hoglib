#include "hoglib.h"
#include "internal.h"

#define RSGL_IMPLEMENTATION
#include <RSGL.h>
#include <RSGL_gl.h>
#include <RSGL_gl1.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define RFONT_IMPLEMENTATION
#include "RFont.h"

hl_rendererHandle hl_renderer_init(hl_rendererType type, hl_windowHandle window) {
	RSGL_renderer* renderer = NULL;

	switch (type) {
		case hl_rendererOpenGLModern:
			renderer = RSGL_renderer_init(RSGL_GL_rendererProc(), (void*)hl_getProcAddress_OpenGL);
			break;
		case hl_rendererOpenGLLegacy:
			renderer = RSGL_renderer_init(RSGL_GL1_rendererProc(), (void*)hl_getProcAddress_OpenGL);
			break;
		default: break;
	}

	renderer->userPtr = window;
	hl_window_setRenderer(window, renderer);

	hl_renderer_updateSize((hl_rendererHandle)renderer);

	return (hl_rendererHandle)renderer;
}


void hl_renderer_updateSize(hl_rendererHandle* renderer) {
	hl_windowHandle window = (hl_windowHandle)((RSGL_renderer*)renderer)->userPtr;

	int32_t w, h;
	hl_window_getSize(window, &w, &h);
	RSGL_renderer_updateSize((RSGL_renderer*)renderer, w, h);
	RSGL_renderer_viewport((RSGL_renderer*)renderer, RSGL_RECT(0, 0, w, h));
}

void hl_renderer_free(hl_rendererHandle renderer) {
	RSGL_renderer_free((RSGL_renderer*)renderer);
}

hl_textureHandle hl_createTextureFromBlob(hl_rendererHandle renderer, const hl_textureBlob* blob) {
    return (void*)RSGL_renderer_createTexture(renderer, (RSGL_textureBlob*)blob);
}

hl_textureHandle hl_renderer_createTextureFromImage(hl_rendererHandle renderer, const char* file) {
    int w, h, c;
    u8* data = stbi_load(file, &w, &h, &c, 0);

	RSGL_textureBlob blob;
	blob.data = data;
	blob.width = w;
	blob.height = h;
	blob.dataType = RSGL_textureDataInt;
	blob.dataFormat = (c == 4) ? RSGL_formatRGBA : RSGL_formatRGB;
	blob.textureFormat = blob.dataFormat;
    size_t texture = RSGL_renderer_createTexture(renderer, &blob);

    free(data);

	return (void*)texture;
}

void hl_renderer_freeTexture(hl_rendererHandle renderer, hl_textureHandle texture) {
	RSGL_renderer_deleteTexture(renderer, (size_t)texture);
}

void hl_renderer_start(hl_rendererHandle renderer) {
	assert(renderer);

	hl_windowHandle window = (hl_windowHandle)((RSGL_renderer*)renderer)->userPtr;
	hl_window_makeCurrentContext_OpenGL(window);
}

void hl_renderer_finish(hl_rendererHandle renderer) {
	hl_windowHandle window = (hl_windowHandle)((RSGL_renderer*)renderer)->userPtr;
	RSGL_renderer_render((RSGL_renderer*)renderer);

	hl_window_swapBuffers_OpenGL(window);
}

void hl_renderer_clear(hl_rendererHandle renderer, hl_color color) {
	RSGL_renderer_clear(renderer, *(RSGL_color*)&color);
}

void hl_renderer_setColor(hl_rendererHandle renderer, hl_color color) {
	RSGL_renderer_setColor(renderer, *(RSGL_color*)&color);
}

void hl_renderer_drawRect(hl_rendererHandle renderer, hl_rect rect) {
	RSGL_drawRect(renderer, *(RSGL_rect*)&rect);
}

