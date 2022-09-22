#pragma once
#include <vector>
#include <memory>

class ModelInstance;
class ModelFactory;
class Camera;

class Scene {
public:
	Scene();
	~Scene();

	ModelInstance *create_model_instance(const char* path);
	
	const std::vector<ModelInstance*> SceneModels() const {
		return _models;
	};
	std::vector<ModelInstance*> CullModels() const;
	
	const Camera *active_camera() const { return _main_camera; }

	std::vector<ModelInstance*> get_model_list() { return _models; }

private:
	std::unique_ptr<ModelFactory> _model_factory;

	std::vector<ModelInstance*> _models;
	Camera *_main_camera;
};