#pragma once
#include "roninpch.h"

#include <imgui.h>

#include "core/timestep.h"

class Layer {
private:
	std::string m_layerName;

public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();
	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate(Timestep timeStep) {}
	virtual void onEvent(GLFWwindow* window, Timestep timeStep) {}
	virtual void onImGui(ImGuiIO& io, Timestep timeStep) {}
};
