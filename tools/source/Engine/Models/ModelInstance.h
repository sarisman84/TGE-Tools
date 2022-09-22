#pragma once

//#include <Math/Math.hpp>
//#include <Math/Transform.h>

class Model;

class ModelInstance
{
public:
	ModelInstance(Model* model);

	Model* GetModel() const;

	__forceinline const Transform& GetTransform() const { return _transform; }

	void SetTransform(const Transform& someTransform);
	void SetRotation(Rotator someRotation);
	void SetLocation(Vector3f someLocation);
	
private:

	Model* _model{};
	Transform _transform{};
};

