#pragma once

#include <Math/Math.hpp>
#include <Math/Transform.h>

class Model;

class ModelInstance
{
public:
	ModelInstance(Model* model);


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



	inline ModelInstance* GetParent() noexcept
	{
		return _parent;
	}


	inline std::vector<ModelInstance*> GetChildren() {
		return _children;
	}

	inline void SetParent(ModelInstance* aParent)
	{
		if (aParent == this) return;

		if (_parent)
		{
			_parent->_children.erase(std::remove(_parent->_children.begin(), _parent->_children.end(), this), _parent->_children.end());
		}

		_parent = aParent;
		aParent->_children.push_back(this);

		_transform.SetMatrix(GetLocalMatrix() * Matrix4x4f::Inverse(_parent->GetWorldMatrix()));

	}




	std::string GetID();
	Matrix4x4f GetLocalMatrix();
	Matrix4x4f GetWorldMatrix();

	void ApplyMatrix4x4f(Matrix4x4f aMatrix);

private:






	Model* _model{};
	Transform _transform{};
	bool _selected = false;
	int _sceneIndex;
	ModelInstance* _parent;
	std::vector<ModelInstance*> _children;
};

