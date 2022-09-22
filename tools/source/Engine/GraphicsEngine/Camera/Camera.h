#pragma once

#include <Math/Transform.h>
#include <Math/Matrix4x4.h>

class Camera {
public:
	Camera(float fov=90.0f);
	~Camera() = default;

	bool init(float horizontal_fov, Vector2f resolution);

	void set_transform(Vector3f position, Vector3f rotation);
	void set_rotation(Rotator rotation);
	void set_position(Vector3f position);

	__forceinline Transform GetTransform() const { return myTransform; }
	__forceinline Matrix4x4f get_projection() const { return myProjection; }

private:
	Transform myTransform{};
	Matrix4x4f myProjection{};

	float myNear = 0.01f;
	float myFar = 100.0f;
};