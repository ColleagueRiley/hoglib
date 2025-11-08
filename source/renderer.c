#include "hoglib.h"
#include "internal.h"

#define RSGL_RFONT
#define RSGL_IMPLEMENTATION
#include <RSGL.h>
#include <RSGL_gl.h>
#include <RSGL_gl1.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define RFONT_IMPLEMENTATION
#include "RFont.h"

typedef struct hl_rendererInfo {
	RFont_renderer* renderer_rfont;
} hl_rendererInfo;

hl_rendererHandle hl_initRenderer(uint32_t type, hl_windowHandle window) {
	RSGL_renderer* renderer = NULL;

	switch (type) {
		case HL_RENDERER_GL_MODERN:
			renderer = RSGL_renderer_init(RSGL_GL_rendererProc(), (void*)hl_getProcAddress);
			break;
		case HL_RENDERER_GL_LEGACY:
			renderer = RSGL_renderer_init(RSGL_GL1_rendererProc(), (void*)hl_getProcAddress);
			break;
		default: break;
	}


	hl_rendererInfo* info = (hl_rendererInfo*)malloc(sizeof(hl_rendererInfo));
	info->renderer_rfont = RFont_RSGL_renderer_init(renderer);
	renderer->userPtr = info;

	hl_setWindowRenderer(window, renderer);

	hl_updateRendererSize(window);


	return (hl_rendererHandle)renderer;
}


void hl_updateRendererSize(hl_windowHandle window) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);

	int32_t w, h;
	hl_getWindowSize(window, &w, &h);
	RSGL_renderer_updateSize((RSGL_renderer*)renderer, w, h);
	RSGL_renderer_viewport((RSGL_renderer*)renderer, RSGL_RECT(0, 0, w, h));
}

void hl_freeRenderer(hl_windowHandle window) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	hl_rendererInfo* info = (hl_rendererInfo*)((RSGL_renderer*)renderer)->userPtr;

	RFont_RSGL_renderer_free(info->renderer_rfont);

	RSGL_renderer_free((RSGL_renderer*)renderer);
	free(info);
}

hl_fontHandle hl_loadFont(hl_windowHandle window, const char* name, uint32_t maxHeight) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	hl_rendererInfo* info = (hl_rendererInfo*)((RSGL_renderer*)renderer)->userPtr;

    RFont_font* font = RFont_font_init(info->renderer_rfont, name, maxHeight, maxHeight * 10, maxHeight * 20);

	return (hl_rendererHandle)font;
}

void hl_freeFont(hl_windowHandle window, hl_fontHandle font) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	hl_rendererInfo* info = (hl_rendererInfo*)((RSGL_renderer*)renderer)->userPtr;
    RFont_font_free(info->renderer_rfont, (RFont_font*)font);
}



hl_textureHandle hl_loadTextureFromBlob(hl_windowHandle window, const hl_textureBlob* blob) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	return (void*)RSGL_renderer_createTexture(renderer, (RSGL_textureBlob*)blob);
}

hl_textureHandle hl_loadTextureFromImage(hl_windowHandle window, const char* file) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
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

void hl_freeTexture(hl_windowHandle window, hl_textureHandle texture) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	RSGL_renderer_deleteTexture(renderer, (size_t)texture);
}

void hl_startFrame(hl_windowHandle window) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	assert(renderer);

	hl_makeCurrentContext(window);

	hl_setTexture(window, 0);
}

void hl_finishFrame(hl_windowHandle window) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	RSGL_renderer_render((RSGL_renderer*)renderer);

	hl_swapBuffers(window);
}

void hl_clear(hl_windowHandle window, hl_color color) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	RSGL_renderer_clear(renderer, *(RSGL_color*)&color);
}

void hl_setTexture(hl_windowHandle window, hl_textureHandle texture) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	RSGL_renderer_setTexture(renderer, (RSGL_texture)texture);
}

void hl_setColor(hl_windowHandle window, hl_color color) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	RSGL_renderer_setColor(renderer, *(RSGL_color*)&color);
}

void hl_drawRect(hl_windowHandle window, hl_rect rect) {
	hl_rendererHandle renderer = hl_getWindowRenderer(window);
	RSGL_drawRect(renderer, RSGL_RECT(rect.x, rect.y, rect.w, rect.h));
}

