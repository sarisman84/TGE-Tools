#pragma once
#include <d3d11.h>
#include <iosfwd>
#include <vector>

class ModelInstance;
class Camera;

class ForwardRenderer
{
public:
	ForwardRenderer() = default;
	~ForwardRenderer() = default;
	bool Init();
	void Render(const Camera *camera, const std::vector<ModelInstance*> &someModelInstances );
	
private:
	struct FrameBufferData {
		Matrix4x4f to_camera;
		Matrix4x4f to_projection;
	} _frame_buffer_data;

	struct ObjectBufferData {
		Matrix4x4f to_world;
	} _object_buffer_data;

	ID3D11Buffer* _frame_buffer;
	ID3D11Buffer* _object_buffer;
};

