#include "hoglib.h"
#include "internal.h"

#ifndef RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#endif

#include "RGFW.h"

void hl_setWindowRenderer(hl_windowHandle window, hl_rendererHandle renderer) {
	((RGFW_window*)window)->userPtr = renderer;
}

hl_rendererHandle hl_getWindowRenderer(hl_windowHandle window) {
	return ((RGFW_window*)window)->userPtr;
}

void hl_resizeHandler(RGFW_window* win, int32_t w, int32_t h)  {
	hl_updateRendererSize(win);
}

hl_windowHandle hl_createWindowPlatform(const char* name, int32_t width, int32_t height, hl_windowFlags flags) {
	RGFW_windowFlags win_flags = RGFW_windowCenter;

	if (flags & HL_WINDOW_NO_BORDER) win_flags |= RGFW_windowNoBorder;
	if (flags & HL_WINDOW_NO_RESIZE) win_flags |= RGFW_windowNoResize;
	if (flags & HL_WINDOW_ALLOW_DND) win_flags |= RGFW_windowAllowDND;
	if (flags & HL_WINDOW_HIDE_MOUSE) win_flags |= RGFW_windowHideMouse;
	if (flags & HL_WINDOW_FULLSCREEN) win_flags |= RGFW_windowFullscreen;
	if (flags & HL_WINDOW_OPAQUE) win_flags |= RGFW_windowTransparent;
	if (flags & HL_WINDOW_SCALE_TO_MONITOR) win_flags |= RGFW_windowScaleToMonitor;
	if (flags & HL_WINDOW_HIDE) win_flags |= RGFW_windowHide;
	if (flags & HL_WINDOW_MAXIMIZE) win_flags |= RGFW_windowMaximize;
	if (flags & HL_WINDOW_FLOATING) win_flags |= RGFW_windowFloating;
	if (flags & HL_WINDOW_FOCUS_ON_SHOW) win_flags |= RGFW_windowFocusOnShow;
	if (flags & HL_WINDOW_MINIMIZE) win_flags |= RGFW_windowMinimize;
	if (flags & HL_WINDOW_FOCUS) win_flags |= RGFW_windowFocus;

	if (flags & HL_RENDERER_GL_LEGACY) win_flags |= RGFW_windowOpenGL;
	if (flags & HL_RENDERER_GL_MODERN) win_flags |= RGFW_windowOpenGL;


	RGFW_window* window = RGFW_createWindow(name, 0, 0, width, height, win_flags);
	RGFW_setWindowResizedCallback(hl_resizeHandler);

	return window;
}

bool hl_windowShouldClose(hl_windowHandle window) {
	return RGFW_window_shouldClose((RGFW_window*)window);
}

void hl_pollEvents(void) {
	RGFW_pollEvents();
}

void hl_closeWindow(hl_windowHandle window) {
	hl_freeRenderer((RGFW_window*)window);
	RGFW_window_close((RGFW_window*)window);
}

void hl_swapInterval(hl_windowHandle window, int32_t swapInterval) {
	RGFW_window_swapInterval_OpenGL((RGFW_window*)window, swapInterval);
}

void hl_swapBuffers(hl_windowHandle window) {
	RGFW_window_swapBuffers_OpenGL((RGFW_window*)window);
}

hl_proc hl_getProcAddress(const char* procname) {
	return RGFW_getProcAddress_OpenGL(procname);
}

void hl_makeCurrentContext(hl_windowHandle window) {
	RGFW_window_makeCurrentContext_OpenGL((RGFW_window*)window);
}

HL_API bool hl_getWindowMouse(hl_windowHandle window, int32_t* x, int32_t* y) {
	return RGFW_window_getMouse(window, x, y);
}

void hl_getWindowSize(hl_windowHandle window, int32_t* width, int32_t* height) {
	RGFW_window_getSize(window, width, height);
}

bool hl_isKeyPressed(hl_keyCode key) {
	return RGFW_isKeyPressed(key);
}

bool hl_isKeyReleased(hl_keyCode key) {
	return RGFW_isKeyReleased(key);
}

bool hl_isKeyDown(hl_keyCode key) {
	return RGFW_isKeyDown(key);
}

bool hl_isMousePressed(hl_mouseButton button) {
	return RGFW_isMousePressed(button);
}

bool hl_isMouseReleased(hl_mouseButton button) {
	return RGFW_isMouseReleased(button);
}

bool hl_isMouseDown(hl_mouseButton button) {
	return RGFW_isMouseDown(button);
}

void hl_getMouseScroll(float* x, float* y) {
	return RGFW_getMouseScroll(x, y);
}

void hl_getMouseVector(float* x, float* y) {
	return RGFW_getMouseVector(x, y);
}
