#include "core/window.h"

Window::Window(const WindowProps& props) : m_windowProps(props) {}
Window::~Window() {}
void Window::onUpdate() {}
uint32_t Window::getWidth() {}
uint32_t Window::getHeight() {}

// Window attributes
//void SetEventCallback(const EventCallbackFn& callback) = 0;
void Window::setVSync(bool enabled) {}
bool Window::isVSync() {}
Window* Window::create(const WindowProps& props = WindowProps()) {
	return new Window(props);
}
