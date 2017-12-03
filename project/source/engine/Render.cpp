#include "Pch.h"
#include "Core.h"
#include "Render.h"
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>


IDXGISwapChain* pSwapChain;
ID3D11Device* pDevice;
ID3D11DeviceContext* context;


Render::Render()
{

}

Render::~Render()
{

}

void Render::Init(void* hwnd)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if(FAILED(result))
		throw 0;

	result = factory->EnumAdapters(0, &adapter);
	if(FAILED(result))
		throw 1;



	DXGI_SWAP_CHAIN_DESC swap_chain = { 0 };
	swap_chain.BufferCount = 1;
	swap_chain.BufferDesc.Width = 1024;
	swap_chain.BufferDesc.Height = 768;
	swap_chain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	/*if(m_vsync_enabled)
	{
		swap_chain.BufferDesc.RefreshRate.Numerator = numerator;
		swap_chain.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else*/
	{
		swap_chain.BufferDesc.RefreshRate.Numerator = 0;
		swap_chain.BufferDesc.RefreshRate.Denominator = 1;
	}

	swap_chain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swap_chain.OutputWindow = (HWND)hwnd;

	// Turn multisampling off.
	swap_chain.SampleDesc.Count = 1;
	swap_chain.SampleDesc.Quality = 0;

	swap_chain.Windowed = true;

	// Set the scan line ordering and scaling to unspecified.
	// ???
	swap_chain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swap_chain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	// ???
	swap_chain.Flags = 0;


	D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;

	result = D3D11CreateDeviceAndSwapChain(adapter, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &feature_level, 1,
		D3D11_SDK_VERSION, &swap_chain, &pSwapChain, &pDevice, nullptr, &context);
	if(FAILED(result))
		throw 2;
}

void Render::Draw()
{
	float color[4];


	// Setup the color to clear the buffer to.
	color[0] = 0;
	color[1] = 0.5f;
	color[2] = 1;
	color[3] = 1;

	// Clear the back buffer.
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
}
