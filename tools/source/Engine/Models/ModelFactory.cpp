#include <stdafx.h>

#include "ModelFactory.h"
#include "ModelInstance.h"
#include "Model.h"

#include <fstream>

#include <DX11Framework.h>

ModelFactory::ModelFactory() {
	_model_cache = std::unordered_map<const char *, Model*>();
}

ModelInstance ModelFactory::create_instance(const char* model_path) {
	return ModelInstance(GetModel(model_path));
}

Model* ModelFactory::GetModel(const char* someFilePath) {
	if (_model_cache.find(someFilePath) != _model_cache.end()) {
		return _model_cache[someFilePath];
	}

	_model_cache[someFilePath] = new Model(someFilePath);
	return _model_cache[someFilePath];
}