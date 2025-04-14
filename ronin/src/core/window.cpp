#include "core/window.h"

Window::Window(const WindowProps& props) : m_windowProps(props) {}
Window::~Window() {}
void Window::onUpdate() {}
uint32_t Window::getWidth() {return 0;}
uint32_t Window::getHeight() {return 0;}

// Window attributes
//void SetEventCallback(const EventCallbackFn& callback) = 0;
void Window::setVSync(bool enabled) {}
bool Window::isVSync() {return 1;}
Window* Window::create(const WindowProps& props) {
	return new Window(props);
}
