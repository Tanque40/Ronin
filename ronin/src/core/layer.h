#include "roninpch.h"

class Layer {
private:
	std::string m_layerName;

public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();
	virtual void setup() {}
	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate() {}
	virtual void onEvent() {}
};
