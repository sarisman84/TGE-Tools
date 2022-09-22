#pragma once
#include <array>
#include <d3d11.h>
#include <memory>

class WindowHandler;
struct ModelData;

// DirectX 11 Framework. Shorthand to make it easier to deal with.
class DX11Framework
{
	IDXGISwapChain* mySwapChain;
	ID3D11RenderTargetView* myBackBuffer;
	ID3D11DepthStencilView* myDepthBuffer;

	static ID3D11Device* myDevice;
	static ID3D11DeviceContext* myContext;
	
public:
	DX11Framework();
	~DX11Framework();

	bool Init(std::shared_ptr<WindowHandler> aWindowHandler);
	void BeginFrame(std::array<float, 4> aClearColor);
	void EndFrame();

public:
	FORCEINLINE static ID3D11Device* GetDevice() { return myDevice; }
	FORCEINLINE static ID3D11DeviceContext* GetContext() { return myContext; }
};

