/*********************************************
* 
* Copyright © 2025 VEGA Enterprises LTD,.
* Licensed under the MIT License.
* 
**********************************************/

#pragma once

#ifndef DX_RENDERER_H
#define DX_RENDERER_H

#include "Renderer.h" // Assuming this is your base class
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

namespace Orca
{
	class DXRenderer : public Renderer
	{
    public:
        DXRenderer();
        virtual ~DXRenderer() override;

        // Base class overrides
        virtual void Initialize(void* windowHandle) override;
        virtual void Render() override;
        virtual void Shutdown() override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;

    private:
        // Using ComPtr for automatic memory management of DirectX objects
        Microsoft::WRL::ComPtr<ID3D11Device> m_device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

        D3D_FEATURE_LEVEL m_featureLevel;
	};
}

#endif