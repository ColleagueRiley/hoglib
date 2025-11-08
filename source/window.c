#include "hoglib.h"
#include "internal.h"

#if defined(HL_PLATFORM_RGFW)
	#include "platforms/hoglib_rgfw.c"
#else
	#error no platform defined
#endif

hl_windowHandle hl_createWindow(const char* name, int32_t width, int32_t height, hl_windowFlags flags) {
	hl_windowHandle window = hl_createWindowPlatform(name, width, height, flags);

	uint32_t type = -1;

	if (flags & HL_RENDERER_GL_LEGACY)
		type = HL_RENDERER_GL_LEGACY;
	else if (flags & HL_RENDERER_GL_MODERN)
		type = HL_RENDERER_GL_MODERN;

	if (type != -1) {
		hl_rendererHandle renderer = hl_initRenderer(type, window);
		(void)(renderer);
	}

	return (hl_windowHandle)window;
}

