#include <stdafx.h>
#include <ForwardRenderer.h>

#include <vector>

#include <DX11Framework.h>

#include "ModelInstance.h"
#include "Model.h"
#include "Camera/Camera.h"

bool ForwardRenderer::Init() {
	HRESULT result = S_FALSE;

	ID3D11DeviceContext* Context = DX11Framework::GetContext();
	ID3D11Device* Device = DX11Framework::GetDevice();

	D3D11_BUFFER_DESC bufferDescription = { 0 };
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bufferDescription.ByteWidth = sizeof(FrameBufferData);
	result = Device->CreateBuffer(&bufferDescription, nullptr, &_frame_buffer);
	if (FAILED(result))	{
		return false;
	}

	bufferDescription.ByteWidth = sizeof(ObjectBufferData);
	result = Device->CreateBuffer(&bufferDescription, nullptr, &_object_buffer);
	if (FAILED(result))	{
		return false;
	}

	return true;
}

void ForwardRenderer::Render(const Camera* camera, const std::vector<ModelInstance*> &someModelInstances ) {
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE buffer_data;

	auto context = DX11Framework::GetContext();

	_frame_buffer_data.to_camera= Matrix4x4f::GetFastInverse(camera->GetTransform().GetMatrix());
	_frame_buffer_data.to_projection = camera->get_projection();

	ZeroMemory(&buffer_data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	result = context->Map(_frame_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &buffer_data);
	if (FAILED(result))	{
		// Boom!
	}

	memcpy(buffer_data.pData, &_frame_buffer_data, sizeof(FrameBufferData));
	context->Unmap(_frame_buffer, 0);
	context->VSSetConstantBuffers(0, 1, &_frame_buffer);

	for (ModelInstance* model_instance : someModelInstances) {
		//model_instance->SetLocation(Vector3f(1, 1, 0));
		Model* model = model_instance->GetModel();
		const Model::ModelData *model_data = model->GetModelData();

		_object_buffer_data.to_world = model_instance->GetWorldMatrix();
		_object_buffer_data.selected = model_instance->GetSelected();
		ZeroMemory(&buffer_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		result = context->Map(_object_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &buffer_data);
		if (FAILED(result)) {
			// Boom!
		}

		memcpy(buffer_data.pData, &_object_buffer_data, sizeof(ObjectBufferData));
		context->Unmap(_object_buffer, 0);

		context->IASetPrimitiveTopology(model_data->primitive_topology);
		context->IASetInputLayout(model_data->input_layout);

		context->IASetVertexBuffers(0, 1, &model_data->vertex_buffer, &model_data->stride, &model_data->offset);
		context->IASetIndexBuffer(model_data->index_buffer, DXGI_FORMAT_R32_UINT, 0);

		context->VSSetConstantBuffers(1, 1, &_object_buffer);
		context->PSSetConstantBuffers(1, 1, &_object_buffer);

		context->VSSetShader(model_data->vertex_shader, nullptr, 0);
		context->PSSetShader(model_data->pixel_shader, nullptr, 0);

		context->PSSetShaderResources(0, 1, &model_data->texture);

		context->DrawIndexed(model_data->num_indices, 0, 0);
	}
}
