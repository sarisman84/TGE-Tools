#include <stdafx.h>

#include "Model.h"

#include <DX11Framework.h>
#include <DDSTextureLoader11.h>

#include <fstream>

Model::Model(const char* aPath) : myPath(aPath) {
    HRESULT result;
    
    Vertex vertices[24] = {

        {0.5f, -0.5f, 0.5f, 1, 1, 1, 1, 1, 0, 1},
        {0.5f, 0.5f, 0.5f, 1, 1, 1, 1, 1, 0, 0},
        {-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, 1, 1, 0},
        {-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, 1, 1, 1},

        {-0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1, 0, 1},
        {-0.5f, 0.5f, 0.5f, 1, 1, 0, 0, 1, 0, 0},
        {-0.5f, 0.5f, -0.5f, 1, 1, 0, 0, 1, 1, 0},
        {-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, 1, 1, 1},

        {-0.5f, -0.5f, -0.5f, 1, 0, 1, 0, 1, 0, 1},
        {-0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 1, 0, 0},
        {0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 1, 1, 0},
        {0.5f, -0.5f, -0.5f, 1, 0, 1, 0, 1, 1, 1},

        {0.5f, -0.5f, -0.5f, 1, 0, 0, 1, 1, 0, 1},
        {0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 1, 0, 0},
        {0.5f, 0.5f, 0.5f, 1, 0, 0, 1, 1, 1, 0},
        {0.5f, -0.5f, 0.5f, 1, 0, 0, 1, 1, 1, 1},

        {0.5f, 0.5f, 0.5f, 1, 1, 1, 0, 1, 0, 1},
        {0.5f, 0.5f, -0.5f, 1, 1, 1, 0, 1, 0, 0},
        {-0.5f, 0.5f, -0.5f, 1, 1, 1, 0, 1, 1, 0},
        {-0.5f, 0.5f, 0.5f, 1, 1, 1, 0, 1, 1, 1},

        {-0.5f, -0.5f, 0.5f, 1, 1, 0, 1, 1, 0, 1},
        {-0.5f, -0.5f, -0.5f, 1, 1, 0, 1, 1, 0, 0},
        {0.5f, -0.5f, -0.5f, 1, 1, 0, 1, 1, 1, 0},
        {0.5f, -0.5f, 0.5f, 1, 1, 0, 1, 1, 1, 1},
    };

    unsigned int indices[36] = {
        0, 1, 2,        /* |/ */
        0, 2, 3,        /* /| */
        4, 5, 6,        /* |/ */
        4, 6, 7,        /* /| */
        8, 9, 10,       /* |/ */
        8, 10, 11,      /* /| */
        12, 13, 14,     /* |/ */
        12, 14, 15,     /* /| */
        16, 17, 18,     /* |/ */
        16, 18, 19,     /* /| */
        20, 21, 22,     /* |/ */
        20, 22, 23      /* /| */
    };
    // End

    D3D11_BUFFER_DESC vertexBufferDesc{};
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexSubresourceData{};
    vertexSubresourceData.pSysMem = vertices;

    ID3D11Buffer* vertexBuffer;
    result = DX11Framework::GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
    if (FAILED(result)) {
        return;
    }

    D3D11_BUFFER_DESC indexBufferDesc{};
    indexBufferDesc.ByteWidth = sizeof(indices);
    indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA indexSubresourceData{};
    indexSubresourceData.pSysMem = indices;

    ID3D11Buffer* indexBuffer;
    result = DX11Framework::GetDevice()->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
    if (FAILED(result)) {
        return;
    }
    //End Vertex

    //Start Shader
    std::ifstream vsFile;
    vsFile.open(Settings::paths["shaders"] + "/VertexShader.vs.cso", std::ios::binary);
    std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
    ID3D11VertexShader* vertexShader;
    result = DX11Framework::GetDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
    if (FAILED(result)) {
        return;
    }
    vsFile.close();

    std::ifstream psFile;
    psFile.open(Settings::paths["shaders"] + "/PixelShader.ps.cso", std::ios::binary);
    std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
    ID3D11PixelShader* pixelShader;
    result = DX11Framework::GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
    if (FAILED(result)) {
        return;
    }
    psFile.close();
    //End Shader

    //Start Layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    ID3D11InputLayout* inputLayout;
    result = DX11Framework::GetDevice()->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), &inputLayout);
    if (FAILED(result)) {
        return;
    }
    //End Layout

    set_texture(L"Texture2.dds");

    myModelData.num_vertices        = sizeof(vertices) / sizeof(Vertex);
    myModelData.num_indices         = sizeof(indices) / sizeof(unsigned int);    
    myModelData.stride              = sizeof(Vertex);
    myModelData.offset              = 0;
    myModelData.vertex_buffer       = vertexBuffer;
    myModelData.index_buffer        = indexBuffer;
    myModelData.vertex_shader       = vertexShader;
    myModelData.pixel_shader        = pixelShader;
    myModelData.primitive_topology  = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    myModelData.input_layout        = inputLayout;
    //myModelData.texture             = set_texture("");
}

void Model::set_texture(const std::wstring filename, const std::string path) {
    std::string asset_path = path.empty() ? Settings::paths["engine_assets"] : path;
    
    std::wstring wpath = std::wstring(asset_path.begin(), asset_path.end()) + L"/Textures/" + filename.c_str();
    ID3D11ShaderResourceView* SRV;
    HRESULT result = DirectX::CreateDDSTextureFromFile(DX11Framework::GetDevice(), wpath.c_str(), nullptr, &SRV);
    if (FAILED(result)) {
        //return false;
    }

    myModelData.texture = SRV;
    myModelData.texture_name = filename;
}