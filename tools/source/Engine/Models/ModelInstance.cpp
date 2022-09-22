#include <stdafx.h>

#include "ModelInstance.h"
#include "Model.h"


ModelInstance::ModelInstance(Model *model) : _model(model) {}

Model* ModelInstance::GetModel() const {
	return _model;
}

void ModelInstance::SetTransform(const Transform& transform) {
	_transform = transform;
}

void ModelInstance::SetRotation(Rotator rotation) {
	// Really should unroll rotations as well somewhere
	// so we can use -180 to 180 instead of 0 to 360.
	_transform.SetRotation(rotation);
}

void ModelInstance::SetLocation(Vector3f location) {
	_transform.SetPosition(location);
}
