#pragma once

#include <d3d11.h>

class Model {
public:
	struct ModelData {
		UINT num_vertices;
		UINT num_indices;
		UINT stride;
		UINT offset;
		ID3D11Buffer* vertex_buffer;
		ID3D11Buffer* index_buffer;
		ID3D11VertexShader* vertex_shader;
		ID3D11PixelShader* pixel_shader;
		D3D_PRIMITIVE_TOPOLOGY primitive_topology;
		ID3D11InputLayout* input_layout;
		ID3D11ShaderResourceView* texture;
		std::wstring texture_name;
	};

	Model(const char* aPath = "");
	//~Model() = default;

	FORCEINLINE const ModelData* GetModelData() const { return &myModelData; }
	FORCEINLINE const char* GetPath() const { return myPath; }

public:
	void set_texture(const std::wstring filename, const std::string path="");

private:
	ModelData myModelData = {};
	const char* myPath;
};
