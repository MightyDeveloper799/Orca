/*********************************************
*
* Copyright © 2025 VEGA Enterprises LTD,.
* Licensed under the MIT License.
*
**********************************************/

#include "DXRenderer.h"
#include <stdexcept>

namespace Orca
{
    DXRenderer::DXRenderer() : m_featureLevel(D3D_FEATURE_LEVEL_11_0) {}

    DXRenderer::~DXRenderer() { Shutdown(); }

    void DXRenderer::Initialize(void* windowHandle)
    {
        HWND hwnd = static_cast<HWND>(windowHandle);

        DXGI_SWAP_CHAIN_DESC scd = {};
        scd.BufferCount = 1;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.OutputWindow = hwnd;
        scd.SampleDesc.Count = 1;
        scd.Windowed = TRUE;

        // Create Device, Context, and SwapChain
        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
            nullptr, 0, D3D11_SDK_VERSION, &scd,
            &m_swapChain, &m_device, &m_featureLevel, &m_deviceContext);

        if (FAILED(hr)) throw std::runtime_error("Failed to create DirectX Device");

        // Set up the Render Target View (The back buffer)
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
        m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_renderTargetView);

        m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);

        // Setup Viewport
        RECT rc;
        GetClientRect(hwnd, &rc);
        D3D11_VIEWPORT vp = { 0, 0, (float)(rc.right - rc.left), (float)(rc.bottom - rc.top), 0.0f, 1.0f };
        m_deviceContext->RSSetViewports(1, &vp);
    }

    void DXRenderer::BeginFrame()
    {
        // Use the Monokai Dark Grey background (39, 40, 34)
        const float clearColor[] = { 0.153f, 0.157f, 0.133f, 1.0f };
        m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    }

    void DXRenderer::Render()
    {
        // Actual draw calls for Scene components go here
    }

    void DXRenderer::EndFrame()
    {
        // Present the back buffer (VSync enabled)
        m_swapChain->Present(1, 0);
    }

    void DXRenderer::Shutdown()
    {
        // ComPtr handles cleanup automatically, but we can reset manually if needed
        m_renderTargetView.Reset();
        m_swapChain.Reset();
        m_deviceContext.Reset();
        m_device.Reset();
    }
}