#pragma once

#include <Math/Math.hpp>
#include <Math/Transform.h>

class Model;

class ModelInstance
{
public:
	ModelInstance(Model* model);

	ModelInstance(const ModelInstance& anInstance)
	{
		_model = anInstance._model;
		_transform = anInstance._transform;
		_transform.AssignOwner(this);
		_selected = anInstance._selected;
	}
	void operator=(const ModelInstance& anInstance)
	{
		_model = anInstance._model;
		_transform = anInstance._transform;
		_transform.AssignOwner(this);
		_selected = anInstance._selected;
	}


	Model* GetModel() const;

	__forceinline const Transform& GetTransform() const { return _transform; }
	__forceinline Transform& GetTransform() { return _transform; }
	__forceinline const Transform CopyTransform() const { return _transform; }
	__forceinline const bool GetSelected() const { return _selected; }

	void SetTransform(const Transform& someTransform);
	void SetRotation(const Rotator& someRotation);
	void SetLocation(const Vector3f& someLocation);
	void SetScale(const Vector3f& someScale);
	void SetSelected(bool true_or_false = true) { _selected = true_or_false; }
	inline void SetSceneIndex(const int aSceneIndex) noexcept { _sceneIndex = aSceneIndex; }


	inline const int GetSceneIndex() const noexcept { return _sceneIndex; }

private:

	Model* _model{};
	Transform _transform{};
	bool _selected = false;
	int _sceneIndex;
};

