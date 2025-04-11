#include "roninpch.h"

struct WindowProps {
	std::string title;
	uint16_t width;
	uint16_t height;

	WindowProps(
		const std::string& _title = "Window",
		uint16_t _width = 1720,
		uint16_t _height = 1080
	) : title(_title), width(_width), height(_height) {
	}
};

class Window {
private:
	WindowProps m_windowProps;

public:
	//using EventCallbackFn = std::function<void(Event&)>;
	Window(const WindowProps& props);
	virtual ~Window();

	virtual void onUpdate();

	virtual uint32_t getWidth();
	virtual uint32_t getHeight();

	// Window attributes
	//virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void setVSync(bool enabled);
	virtual bool isVSync();

	static Window* create(const WindowProps& props = WindowProps());
};
