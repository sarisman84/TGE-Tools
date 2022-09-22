#include <stdafx.h>
#include "Scene.h"

#include <Camera/Camera.h>
#include <ModelInstance.h>
#include <ModelFactory.h>

Scene::Scene() {
	_main_camera = new Camera();
	_model_factory = std::unique_ptr<ModelFactory>(new ModelFactory());
}

Scene::~Scene() {
	delete _main_camera;
	_main_camera = nullptr;
}


ModelInstance *Scene::create_model_instance(const char* path) {
	_models.push_back(new ModelInstance(std::move(_model_factory->create_instance(path))));
	return _models.back();

//	_models.push_back(new ModelInstance(std::move(*aModelInstance)));
//	AddModel(&_model_factory->create_instance(model_path));
}

std::vector<ModelInstance*> Scene::CullModels() const {
	return _models;
}