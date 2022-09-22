#include <stdafx.h>
#include "Camera.h"

Camera::Camera(float fov) {
	init(fov, { (float)Settings::window_data.w, (float)Settings::window_data.h });
	set_transform({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f });
}

bool Camera::init(float horizontal_fov, Vector2f resolution) {
	const float horizontal_fov_rad = horizontal_fov* (Math::Pi / 180);
	const float vertical_fov_rad = 2 * std::atan(std::tan(horizontal_fov_rad / 2) * (resolution.Y / resolution.X));

	float x_scale = 1 / std::tanf(horizontal_fov_rad * 0.5f);
	float y_scale = 1 / std::tanf(vertical_fov_rad * 0.5f);
	float q = myFar / (myFar - myNear);

	myProjection(1, 1) = x_scale;
	myProjection(2, 2) = y_scale;
	myProjection(3, 3) = q;
	myProjection(3, 4) = 1.0f / q;
	myProjection(4, 3) = -q * myNear;
	myProjection(4, 4) = 0.0f;

	return true;
}

void Camera::set_transform(Vector3f position, Vector3f rotation) {
	set_position(position);
	set_rotation(rotation);
}

void Camera::set_rotation(Rotator rotation)
{
	myTransform.SetRotation(rotation);
}

void Camera::set_position(Vector3f position)
{
	myTransform.SetPosition(position);
}