#include "roninpch.h"

#include "core/layer.h"

class SandBox : public Layer {
public:
	SandBox();
	virtual ~SandBox();
	virtual void setup() override;
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate() override;
	virtual void onEvent() override;
};
