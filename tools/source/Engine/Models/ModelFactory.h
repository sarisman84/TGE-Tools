#pragma once
#include <unordered_map>
#include <ModelInstance.h>


class Model;
//struct ID3D11Device;

class ModelFactory {
public:
	ModelFactory();
	~ModelFactory() = default;

	ModelInstance create_instance(const char *model_path);

private:
	Model* GetModel(const char*);

private:
	std::unordered_map<const char *, Model*> _model_cache;
};