#include "hoglib.h"
#include "internal.h"

#ifndef RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#endif

#include "RGFW.h"

void hl_window_setRenderer(hl_windowHandle window, hl_rendererHandle renderer) {
	((RGFW_window*)window)->userPtr = renderer;
}

hl_rendererHandle hl_window_getRenderer(hl_windowHandle window) {
	return ((RGFW_window*)window)->userPtr;
}

void hl_resizeHandler(RGFW_window* win, int32_t w, int32_t h)  {
	hl_renderer_updateSize(hl_window_getRenderer(win));
}

void hl_pollEvents(void) {
	RGFW_pollEvents();
}

hl_windowHandle hl_window_init(const char* name, int32_t x, int32_t y, int32_t width, int32_t height, hl_windowFlags flags) {
	RGFW_windowFlags win_flags = 0;
	if (flags & hl_windowNoBorder) win_flags |= RGFW_windowNoBorder;
	if (flags & hl_windowNoResize) win_flags |= RGFW_windowNoResize;
	if (flags & hl_windowAllowDND) win_flags |= RGFW_windowAllowDND;
	if (flags & hl_windowHideMouse) win_flags |= RGFW_windowHideMouse;
	if (flags & hl_windowFullscreen) win_flags |= RGFW_windowFullscreen;
	if (flags & hl_windowTransparent) win_flags |= RGFW_windowTransparent;
	if (flags & hl_windowCenter) win_flags |= RGFW_windowCenter;
	if (flags & hl_windowScaleToMonitor) win_flags |= RGFW_windowScaleToMonitor;
	if (flags & hl_windowHide) win_flags |= RGFW_windowHide;
	if (flags & hl_windowMaximize) win_flags |= RGFW_windowMaximize;
	if (flags & hl_windowCenterCursor) win_flags |= RGFW_windowCenterCursor;
	if (flags & hl_windowFloating) win_flags |= RGFW_windowFloating;
	if (flags & hl_windowFocusOnShow) win_flags |= RGFW_windowFocusOnShow;
	if (flags & hl_windowMinimize) win_flags |= RGFW_windowMinimize;
	if (flags & hl_windowFocus) win_flags |= RGFW_windowFocus;
	if (flags & hl_windowedFullscreen) win_flags |= RGFW_windowedFullscreen;

	if (flags & hl_windowOpenGLLegacy) win_flags |= RGFW_windowOpenGL;
	if (flags & hl_windowOpenGLModern) win_flags |= RGFW_windowOpenGL;


	RGFW_window* window = RGFW_createWindow(name, x, y, width, height, win_flags);
	RGFW_setWindowResizedCallback(hl_resizeHandler);

	hl_rendererType type = -1;

	if (flags & hl_windowOpenGLLegacy)
		type = hl_rendererOpenGLModern;
	else if (flags & hl_windowOpenGLModern) win_flags |= RGFW_windowOpenGL;
		type = hl_rendererOpenGLLegacy;

	if (type != -1) {
		hl_rendererHandle renderer = hl_renderer_init(type, window);
		RGFW_UNUSED(renderer);
	}

	return (hl_windowHandle)window;
}

bool hl_window_shouldClose(hl_windowHandle window) {
	return RGFW_window_shouldClose((RGFW_window*)window);
}

void hl_window_close(hl_windowHandle window) {
	hl_renderer_free(((RGFW_window*)window)->userPtr);
	RGFW_window_close((RGFW_window*)window);
}

void hl_window_swapInterval_OpenGL(hl_windowHandle window, int32_t swapInterval) {
	RGFW_window_swapInterval_OpenGL((RGFW_window*)window, swapInterval);
}

void hl_window_swapBuffers_OpenGL(hl_windowHandle window) {
	RGFW_window_swapBuffers_OpenGL((RGFW_window*)window);
}

hl_proc hl_getProcAddress_OpenGL(const char* procname) {
	return RGFW_getProcAddress_OpenGL(procname);
}

void hl_window_makeCurrentContext_OpenGL(hl_windowHandle window) {
	RGFW_window_makeCurrentContext_OpenGL((RGFW_window*)window);
}

HL_API bool hl_window_getMouse(hl_windowHandle window, int32_t* x, int32_t* y) {
	return RGFW_window_getMouse(window, x, y);
}

void hl_window_getSize(hl_windowHandle window, int32_t* width, int32_t* height) {
	RGFW_window_getSize(window, width, height);
}

bool hl_isKeyPressed(hl_key key) {
	return RGFW_isKeyPressed(key);
}

bool hl_isKeyReleased(hl_key key) {
	return RGFW_isKeyReleased(key);
}

bool hl_isKeyDown(hl_key key) {
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

bool hl_window_checkEvent(hl_windowHandle window, hl_event* event) {
	return RGFW_window_checkEvent(window, (RGFW_event*)event);
}

bool hl_window_checkQueuedEvent(hl_windowHandle window, hl_event* event) {
	return RGFW_window_checkQueuedEvent(window, (RGFW_event*)event);
}

hl_windowMovedfunc hl_setWindowMovedCallback(hl_windowMovedfunc func) {
    return (hl_windowMovedfunc)RGFW_setWindowMovedCallback((RGFW_windowMovedfunc)func);
}

hl_windowResizedfunc hl_setWindowResizedCallback(hl_windowResizedfunc func) {
    return (hl_windowResizedfunc)RGFW_setWindowResizedCallback((RGFW_windowResizedfunc)func);
}

hl_windowQuitfunc hl_setWindowQuitCallback(hl_windowQuitfunc func) {
    return (hl_windowQuitfunc)RGFW_setWindowQuitCallback((RGFW_windowQuitfunc)func);
}

hl_mousePosfunc hl_setMousePosCallback(hl_mousePosfunc func) {
    return (hl_mousePosfunc)RGFW_setMousePosCallback((RGFW_mousePosfunc)func);
}

hl_windowRefreshfunc hl_setWindowRefreshCallback(hl_windowRefreshfunc func) {
    return (hl_windowRefreshfunc)RGFW_setWindowRefreshCallback((RGFW_windowRefreshfunc)func);
}

hl_focusfunc hl_setFocusCallback(hl_focusfunc func) {
    return (hl_focusfunc)RGFW_setFocusCallback((RGFW_focusfunc)func);
}

hl_mouseNotifyfunc hl_setMouseNotifyCallback(hl_mouseNotifyfunc func) {
    return (hl_mouseNotifyfunc)RGFW_setMouseNotifyCallback((RGFW_mouseNotifyfunc)func);
}

hl_dataDropfunc hl_setDataDropCallback(hl_dataDropfunc func) {
    return (hl_dataDropfunc)RGFW_setDataDropCallback((RGFW_dataDropfunc)func);
}

hl_dataDragfunc hl_setDataDragCallback(hl_dataDragfunc func) {
    return (hl_dataDragfunc)RGFW_setDataDragCallback((RGFW_dataDragfunc)func);
}

hl_keyfunc hl_setKeyCallback(hl_keyfunc func) {
    return (hl_keyfunc)RGFW_setKeyCallback((RGFW_keyfunc)func);
}

hl_mouseButtonfunc hl_setMouseButtonCallback(hl_mouseButtonfunc func) {
    return (hl_mouseButtonfunc)RGFW_setMouseButtonCallback((RGFW_mouseButtonfunc)func);
}

hl_mouseScrollfunc hl_setMouseScrollCallback(hl_mouseScrollfunc func) {
    return (hl_mouseScrollfunc)RGFW_setMouseScrollCallback((RGFW_mouseScrollfunc)func);
}

hl_windowMaximizedfunc hl_setWindowMaximizedCallback(hl_windowMaximizedfunc func) {
    return (hl_windowMaximizedfunc)RGFW_setWindowMaximizedCallback((RGFW_windowMaximizedfunc)func);
}

hl_windowMinimizedfunc hl_setWindowMinimizedCallback(hl_windowMinimizedfunc func) {
    return (hl_windowMinimizedfunc)RGFW_setWindowMinimizedCallback((RGFW_windowMinimizedfunc)func);
}

hl_windowRestoredfunc hl_setWindowRestoredCallback(hl_windowRestoredfunc func) {
    return (hl_windowRestoredfunc)RGFW_setWindowRestoredCallback((RGFW_windowRestoredfunc)func);
}

hl_scaleUpdatedfunc hl_setScaleUpdatedCallback(hl_scaleUpdatedfunc func) {
    return (hl_scaleUpdatedfunc)RGFW_setScaleUpdatedCallback((RGFW_scaleUpdatedfunc)func);
}
