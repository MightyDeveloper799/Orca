/*********************************************
*
* Copyright © 2025 VEGA Enterprises LTD,.
* Licensed under the MIT License.
*
**********************************************/

#pragma once

#ifndef D3D_RENDERER_H
#define D3D_RENDERER_H

#include <wrl/client.h>
#include <Windows.h>
#include <d3d11.h>

struct RendererConfig
{
	HWND windowHandle = nullptr;
	int width, height;
	bool vsync = true;
};

namespace Orca
{
	class D3DRenderer
	{
	public:
		D3DRenderer();
		~D3DRenderer();

		bool Init(const RendererConfig& config);

		void Shutdown();

		void Render();

	private:
		template <typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		ComPtr<ID3D11Device> m_Device;
		ComPtr<ID3D11DeviceContext> m_DeviceContext;
		ComPtr<IDXGISwapChain> m_SwapChain;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		ComPtr<ID3D11DepthStencilView> m_DepthStencilView;

		D3D11_VIEWPORT m_Viewport;
		bool m_Initialized = false;

		int m_Width;
		int m_Height;
		bool m_Vsync = false;

		bool CreateDeviceAndSwapChain(HWND windowHandle);
		bool CreateRenderTargetAndDepthStencil();
		void SetupViewport();
	};
}

#endif