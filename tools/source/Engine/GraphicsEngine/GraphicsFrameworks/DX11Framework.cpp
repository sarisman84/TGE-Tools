#include <stdafx.h>

#include <DX11Framework.h>
#include <Win32Window.h>

ID3D11Device* DX11Framework::myDevice;
ID3D11DeviceContext* DX11Framework::myContext;

DX11Framework::DX11Framework()
{
	mySwapChain = nullptr;
	myDevice = nullptr;
	myContext = nullptr;
	myBackBuffer = nullptr;
}

DX11Framework::~DX11Framework()
{
	mySwapChain = nullptr;
	myDevice = nullptr;
	myContext = nullptr;
	myBackBuffer = nullptr;
}

bool DX11Framework::Init(std::shared_ptr<WindowHandler> aWindowHandler)
{
	HRESULT result;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = aWindowHandler->GetWindowHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mySwapChain,
		&myDevice,
		nullptr,
		&myContext
	);

	ID3D11Texture2D* backBufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
	if (FAILED(result))
	{
		return false;
	}

	result = myDevice->CreateRenderTargetView(backBufferTexture, nullptr, &myBackBuffer);
	if (FAILED(result))
	{
		return false;
	}

	result = backBufferTexture->Release();
	if (FAILED(result))
	{
		return false;
	}

	// TEMP
	ID3D11Texture2D* depthBufferTexture;
	D3D11_TEXTURE2D_DESC depthBufferDesc = { 0 };
	depthBufferDesc.Width = static_cast<unsigned int>(aWindowHandler->GetWidth());
	depthBufferDesc.Height = static_cast<unsigned int>(aWindowHandler->GetHeight());
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	result = myDevice->CreateTexture2D(&depthBufferDesc, nullptr, &depthBufferTexture);
	if (FAILED(result))
	{
		return false;
	}

	result = myDevice->CreateDepthStencilView(depthBufferTexture, nullptr, &myDepthBuffer);
	if (FAILED(result))
	{
		return false;
	}

	myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);

	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(aWindowHandler->GetWidth());
	viewport.Height = static_cast<float>(aWindowHandler->GetHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	myContext->RSSetViewports(1, &viewport);
	//END TEMP

	return true;
}

void DX11Framework::BeginFrame(std::array<float, 4> aClearColor) {
	myContext->ClearRenderTargetView(myBackBuffer, &aClearColor[0]);
	myContext->ClearDepthStencilView(myDepthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11Framework::EndFrame()
{
	mySwapChain->Present(1, 0);
}
