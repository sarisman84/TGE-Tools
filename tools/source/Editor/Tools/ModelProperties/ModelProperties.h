#pragma once

#include <ToolsInterface/ToolsInterface.h>
#include <Math/Vector3.h>

#include <vector>

class ModelInstance;

class ModelProperties : public ToolsInterface {
public:
	ModelProperties(std::vector<ModelInstance*> &model_list);

	virtual void Draw() override;

private:
	std::vector<ModelInstance*> _model_list;
	Vector3f _start_position;
	std::wstring _og_Texture;
};