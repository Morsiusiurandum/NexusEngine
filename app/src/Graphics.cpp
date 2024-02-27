#include "Graphics.h"
#pragma comment(lib, "d3d11.lib")

Graphics::Graphics(HWND window)
{
    DXGI_SWAP_CHAIN_DESC swap_chain_desc               = {};
    swap_chain_desc.BufferDesc.Width                   = 0;
    swap_chain_desc.BufferDesc.Height                  = 0;
    swap_chain_desc.BufferDesc.Format                  = DXGI_FORMAT_B8G8R8A8_UNORM;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator   = 0;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0;
    swap_chain_desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
    swap_chain_desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.SampleDesc.Count                   = 1;
    swap_chain_desc.SampleDesc.Quality                 = 0;
    swap_chain_desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount                        = 1;
    swap_chain_desc.OutputWindow                       = window;
    swap_chain_desc.Windowed                           = TRUE;
    swap_chain_desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Flags                              = 0;

    D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &swap_chain_desc,
            &swap_chain_,
            &device_,
            nullptr,
            &device_context_);

    ID3D11Resource *back_buffer_ = nullptr;

    swap_chain_->GetBuffer(
            0,
            _uuidof(ID3D11Resource),
            reinterpret_cast<void **>(&back_buffer_));

    device_->CreateRenderTargetView(
            back_buffer_,
            nullptr,
            &render_target_view_);

    back_buffer_->Release();

}

Graphics::~Graphics()
{
    if (device_context_ != nullptr)
    {
        device_context_->Release();
    }
    if (swap_chain_ != nullptr)
    {
        swap_chain_->Release();
    }
    if (device_ != nullptr)
    {
        device_->Release();
    }
}

auto Graphics::EndFrame() -> void
{
    swap_chain_->Present(1U, 0U);
}

auto Graphics::ClearBuffer(float r, float g, float b) noexcept -> void
{
    const float color[] = {r, g, b, 1.0f};
    device_context_->ClearRenderTargetView(
            render_target_view_,
            color);
}
