#include <stdafx.h>

#include "ModelInstance.h"
#include "Model.h"


ModelInstance::ModelInstance(Model* model) : _model(model) {
	_parent = nullptr;
}

Model* ModelInstance::GetModel() const {
	return _model;
}

void ModelInstance::SetTransform(const Transform& transform) {
	_transform = transform;
}

void ModelInstance::SetScale(const Vector3f& scale) {
	_transform.SetScale(scale);
}

std::string ModelInstance::GetID()
{
	std::string id = GetModel()->GetPath();
	id += "_" + std::to_string(_sceneIndex);
	auto parent = GetParent();
	if (parent)
	{
		id += "[P: " + std::to_string(parent->GetSceneIndex()) + "]";
	}

	return id;
}

Matrix4x4f ModelInstance::GetLocalMatrix()
{
	return _transform.GetMatrix();
}

Matrix4x4f ModelInstance::GetWorldMatrix()
{
	if (!_parent) return GetLocalMatrix();


	return GetLocalMatrix() * _parent->GetWorldMatrix();



}

void ModelInstance::ApplyMatrix4x4f(Matrix4x4f childToWorld)
{
	Matrix4x4f childToParent;
	if (!_parent)
	{
		_transform.SetMatrix(childToWorld);

		return;
	}
	else
	{
		Matrix4x4f parentToWorld = _parent->GetWorldMatrix();
		childToParent = childToWorld * Matrix4x4f::Inverse(parentToWorld);
	}


	_transform.SetMatrix(childToParent);



}



void ModelInstance::SetRotation(const Rotator& rotation) {
	// Really should unroll rotations as well somewhere
	// so we can use -180 to 180 instead of 0 to 360.
	_transform.SetRotation(rotation);
}

void ModelInstance::SetLocation(const Vector3f& location) {
	_transform.SetPosition(location);
}
