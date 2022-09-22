#pragma once

#include <Transform.h>
#include <Matrix4x4.h>

class Camera {
public:
	Camera(float fov=90.0f);
	~Camera() = default;

	bool init(float horizontal_fov, Vector2f resolution);

	void set_transform(Vector3f position, Vector3f rotation);
	void set_rotation(Rotator rotation);
	void set_position(Vector3f position);

	__forceinline Transform get_transform() const { return _transform; }
	__forceinline Matrix4x4f get_projection() const { return _projection; }

private:
	Transform _transform{};
	Matrix4x4f _projection{};

	float _near = 0.01f;
	float _far = 100.0f;
};