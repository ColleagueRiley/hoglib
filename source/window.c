#include "internal.h"

#ifndef RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#endif

#include "RGFW.h"


void hl_pollEvents(void) {
	RGFW_pollEvents();
}

hl_windowHandle hl_window_init(const char* name, int32_t x, int32_t y, int32_t width, int32_t height, hl_windowFlags flags) {
	RGFW_window* window = RGFW_createWindow(name, 0, 0, width, height, flags);

	return (hl_windowHandle)window;
}

bool hl_window_shouldClose(hl_windowHandle window) {
	return RGFW_window_shouldClose((RGFW_window*)window);
}

void hl_window_close(hl_windowHandle window) {
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
