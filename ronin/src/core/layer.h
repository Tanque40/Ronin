#include "roninpch.h"

#include <imgui.h>

class Layer {
private:
	std::string m_layerName;

public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();
	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate() {}
	virtual void onEvent() {}
	virtual void onImGui( ImGuiIO& io ) {}
};
