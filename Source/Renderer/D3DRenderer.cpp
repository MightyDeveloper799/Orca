/*********************************************
*
* Copyright © 2025 VEGA Enterprises LTD,.
* Licensed under the MIT License.
*
**********************************************/

#include "D3DRenderer.h"
#include <iostream>
#include <wrl/client.h>
#include <algorithm>

#define HR_CHECK(hr, message) if (FAILED(hr)) { std::cerr << "[D3DRenderer] " << message << " failed with HRESULT: 0x" << std::hex << hr << std::dec << std::endl; return false; }

namespace Orca
{
	D3DRenderer::D3DRenderer() {}

	D3DRenderer::~D3DRenderer()
	{
		Shutdown();
	}

	bool D3DRenderer::Init(const RendererConfig& config)
	{
		if (m_Initialized) return true;

		m_Width = config.width;
		m_Height = config.height;
		m_Vsync = config.vsync;

		std::cout << "[D3DRenderer] Initializing Direct3D 11 (" << m_Width << "x" << m_Height << ")..." << std::endl;

		if (!CreateDeviceAndSwapChain(config.windowHandle))
		{
			std::cerr << "[D3DRenderer] Fatal: Failed to create D3D Device/Swap Chain." << std::endl;
			return false;
		}

		if (!CreateRenderTargetAndDepthStencil())
		{
			std::cerr << "[D3DRenderer] Fatal: Failed to create RTV/DSV resources." << std::endl;
			return false;
		}

		SetupViewport();

		// Set the render targets and viewport once during initialization
		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
		m_DeviceContext->RSSetViewports(1, &m_Viewport);

		m_Initialized = true;
		std::cout << "[D3DRenderer] Direct3D 11 initialized successfully." << std::endl;
		return true;
	}

	void D3DRenderer::Shutdown()
	{
		if (!m_Initialized) return;

		std::cout << "[D3DRenderer] Shutting down Direct3D 11." << std::endl;

		// Before releasing, set context to default state to avoid dangling references
		if (m_DeviceContext)
		{
			m_DeviceContext->ClearState();
		}

		// ComPtr handles the automatic Release() calls for all DirectX objects.
		m_Initialized = false;
	}

	bool D3DRenderer::CreateDeviceAndSwapChain(HWND windowHandle)
	{
		if (!windowHandle)
		{
			std::cerr << "[D3DRenderer] Error: Invalid window handle provided. Cannot create D3D device." << std::endl;
			return false;
		}

		UINT createDeviceFlags = 0;

		// #ifdef _DEBUG 
		// createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		// #endif

		D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE };
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr = S_OK;

		// --- Swap Chain Description ---
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1; // Double buffering
		sd.BufferDesc.Width = m_Width;
		sd.BufferDesc.Height = m_Height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60; // Assuming 60Hz
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = windowHandle; // Must be a valid HWND
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			createDeviceFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&sd,
			m_SwapChain.GetAddressOf(),
			m_Device.GetAddressOf(),
			&featureLevel,
			m_DeviceContext.GetAddressOf()
		);

		HR_CHECK(hr, "D3D11CreateDeviceAndSwapChain");
		return true;
	}

	bool D3DRenderer::CreateRenderTargetAndDepthStencil()
	{
		HRESULT hr;

		ComPtr<ID3D11Texture2D> backBuffer;
		hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backBuffer.GetAddressOf());
		HR_CHECK(hr, "SwapChain->GetBuffer (Back Buffer)");

		hr = m_Device->CreateRenderTargetView(backBuffer.Get(), NULL, m_RenderTargetView.GetAddressOf());
		HR_CHECK(hr, "Device->CreateRenderTargetView");

		D3D11_TEXTURE2D_DESC depthBufferDesc = {};
		depthBufferDesc.Width = m_Width;
		depthBufferDesc.Height = m_Height;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ComPtr<ID3D11Texture2D> depthStencilBuffer;
		hr = m_Device->CreateTexture2D(&depthBufferDesc, NULL, depthStencilBuffer.GetAddressOf());
		HR_CHECK(hr, "Device->CreateTexture2D for Depth Buffer");

		hr = m_Device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, m_DepthStencilView.GetAddressOf());
		HR_CHECK(hr, "Device->CreateDepthStencilView");

		return true;
	}

	void D3DRenderer::SetupViewport()
	{
		m_Viewport.Width = (float)m_Width;
		m_Viewport.Height = (float)m_Height;
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
	}

	void D3DRenderer::Render()
	{
		if (!m_Initialized) return;

		const float clearColor[4] = { 0.1f, 0.1f, 0.2f, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		m_SwapChain->Present(m_Vsync ? 1 : 0, 0);
	}
}