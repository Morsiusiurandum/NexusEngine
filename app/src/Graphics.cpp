#include "Graphics.h"
#include <DirectXMath.h>
#include <cmath>
#include <d3dcompiler.h>
#include <sstream>

namespace wrl = Microsoft::WRL;
namespace dx  = DirectX;

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

    UINT swapCreateFlags = 0u;
#ifndef NDEBUG
    swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    GRAPHICS_EXCEPTION(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        swapCreateFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swap_chain_desc,
        &swap_chain,
        &device,
        nullptr,
        &device_context));

    // Use smart point to auto release
    Microsoft::WRL::ComPtr<ID3D11Resource> back_buffer;
    GRAPHICS_EXCEPTION(swap_chain->GetBuffer(0, _uuidof(ID3D11Resource), &back_buffer));
    GRAPHICS_EXCEPTION(device->CreateRenderTargetView(back_buffer.Get(), nullptr, &render_target_view));

    // create depth stensil state
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable              = TRUE;
    dsDesc.DepthWriteMask           = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc                = D3D11_COMPARISON_LESS;
    wrl::ComPtr<ID3D11DepthStencilState> pDSState;
    GRAPHICS_EXCEPTION(device->CreateDepthStencilState(&dsDesc, &pDSState));

    // bind depth state
    device_context->OMSetDepthStencilState(pDSState.Get(), 1u);

    // create depth stensil texture
    wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
    D3D11_TEXTURE2D_DESC         descDepth = {};
    descDepth.Width                        = 800u;
    descDepth.Height                       = 600u;
    descDepth.MipLevels                    = 1u;
    descDepth.ArraySize                    = 1u;
    descDepth.Format                       = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count             = 1u;
    descDepth.SampleDesc.Quality           = 0u;
    descDepth.Usage                        = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags                    = D3D11_BIND_DEPTH_STENCIL;
    GRAPHICS_EXCEPTION(device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

    // create view of depth stensil texture
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format                        = DXGI_FORMAT_D32_FLOAT;
    descDSV.ViewDimension                 = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice            = 0u;
    (device->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &pDSV));

    // bind depth stensil view to OM
    device_context->OMSetRenderTargets(1u, render_target_view.GetAddressOf(), pDSV.Get());

    // view port
    D3D11_VIEWPORT viewport;
    viewport.Width    = 800;
    viewport.Height   = 600;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    device_context->RSSetViewports(1U, &viewport);
}

auto Graphics::EndFrame() -> void
{
    HRESULT hr;
    if (FAILED(hr = swap_chain->Present(1U, 0U)))
     {
        if (hr == DXGI_ERROR_DEVICE_REMOVED)
        {
            GRAPHICS_EXCEPTION(device->GetDeviceRemovedReason());
        }
        else
        {
            GRAPHICS_EXCEPTION(hr);
        }
    }
}

auto Graphics::ClearBuffer(float r, float g, float b) noexcept -> void
{
    const std::array color = {r, g, b, 1.0f};

    device_context->ClearRenderTargetView(render_target_view.Get(), color.data());
    device_context->ClearDepthStencilView( pDSV.Get(),D3D11_CLEAR_DEPTH,1.0f,0u );
}

auto Graphics::Draw(float a) -> void
{
    struct Vertex
    {
        float x;
        float y;
    };

    constexpr std::array<Vertex, 6> vertices{
        {{0.0f, 0.5f},
         {0.5f, -0.5f},
         {-0.5f, -0.5f},
         {-0.3f, 0.3f},
         {0.3f, 0.3f},
         {0.0f, -0.8f}}
    };

    // bind vertex buffer
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
    D3D11_BUFFER_DESC                    buffer_desc      = {};
    D3D11_SUBRESOURCE_DATA               subresource_data = {};

    buffer_desc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
    buffer_desc.CPUAccessFlags      = 0U;
    buffer_desc.MiscFlags           = 0U;
    buffer_desc.ByteWidth           = sizeof(vertices);
    buffer_desc.StructureByteStride = sizeof(Vertex);

    subresource_data.pSysMem = vertices.data();

    GRAPHICS_EXCEPTION(
        device->CreateBuffer(
            &buffer_desc,
            &subresource_data,
            &vertex_buffer));

    constexpr UINT stride = sizeof(Vertex);
    constexpr UINT offset = 0U;
    device_context->IASetVertexBuffers(
        0U,
        1U,
        vertex_buffer.GetAddressOf(),
        &stride,
        &offset);

    const unsigned short indexs[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 1,
        2, 1, 5};

    Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
    D3D11_BUFFER_DESC                    index_buffer_desc = {};
    index_buffer_desc.BindFlags                            = D3D11_BIND_VERTEX_BUFFER;
    index_buffer_desc.Usage                                = D3D11_USAGE_DEFAULT;
    index_buffer_desc.CPUAccessFlags                       = 0U;
    index_buffer_desc.MiscFlags                            = 0U;
    index_buffer_desc.ByteWidth                            = sizeof(indexs);
    index_buffer_desc.StructureByteStride                  = 16U;

    D3D11_SUBRESOURCE_DATA index_subresource_data = {};
    index_subresource_data.pSysMem                = indexs;

    GRAPHICS_EXCEPTION(
        device->CreateBuffer(
            &index_buffer_desc,
            &index_subresource_data,
            &index_buffer));

    device_context->IASetIndexBuffer(
        index_buffer.Get(),
        DXGI_FORMAT_R16_UINT,
        0U);

    struct ConstantBuffer
    {
        struct
        {
            float element[4][4];
        } transformation;
    };

    const ConstantBuffer constant_buffer = {
        {{{0.75f * cos(a), sin(a), 0.0f, 0.0f},
          {0.75f * -sin(a), cos(a), 0.0f, 0.0f},
          {0.0f, 0.0f, 1.0f, 0.0f},
          {0.0f, 0.0f, 0.0f, 1.0f}}}};

    Microsoft::WRL::ComPtr<ID3D11Buffer> const_buffer;
    D3D11_BUFFER_DESC                    const_buffer_desc = {};
    const_buffer_desc.BindFlags                            = D3D11_BIND_CONSTANT_BUFFER;
    const_buffer_desc.Usage                                = D3D11_USAGE_DYNAMIC;
    const_buffer_desc.CPUAccessFlags                       = D3D11_CPU_ACCESS_WRITE;
    const_buffer_desc.MiscFlags                            = 0U;
    const_buffer_desc.ByteWidth                            = sizeof(constant_buffer);
    const_buffer_desc.StructureByteStride                  = 0U;

    D3D11_SUBRESOURCE_DATA const_subresource_data = {};
    const_subresource_data.pSysMem                = &constant_buffer;

    GRAPHICS_EXCEPTION(
        device->CreateBuffer(
            &const_buffer_desc,
            &const_subresource_data,
            &const_buffer));
    device_context->VSSetConstantBuffers(0u, 1u, const_buffer.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3DBlob> blob;
    // create pixel shader
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader;              //smart point
    GRAPHICS_EXCEPTION(D3DReadFileToBlob(L"../PixelShader.cso", &blob)); //load flie
    GRAPHICS_EXCEPTION(device->CreatePixelShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &pixel_shader));
    device_context->PSSetShader(pixel_shader.Get(), nullptr, 0U); //bind

    // create vertex shader
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
    GRAPHICS_EXCEPTION(D3DReadFileToBlob(L"../VertexShader.cso", &blob));
    GRAPHICS_EXCEPTION(device->CreateVertexShader(
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &vertex_shader));
    device_context->VSSetShader(vertex_shader.Get(), nullptr, 0U); //bind

    // input layout
    Microsoft::WRL::ComPtr<ID3D11InputLayout>          input_latout;
    constexpr std ::array<D3D11_INPUT_ELEMENT_DESC, 1> input_element_desc = {

        {"Position",
         0,
         DXGI_FORMAT_R32G32_FLOAT,
         0,
         0,
         D3D11_INPUT_PER_VERTEX_DATA,
         0}
    };
    GRAPHICS_EXCEPTION(
        device->CreateInputLayout(
            input_element_desc.data(),
            (UINT) input_element_desc.size(),
            blob->GetBufferPointer(),
            blob->GetBufferSize(),
            &input_latout));

    // bind
    device_context->OMSetRenderTargets(1U, render_target_view.GetAddressOf(), nullptr); // render target
    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);      // primitive topology
    device_context->IASetInputLayout(input_latout.Get());                               // layout

    // view port
    D3D11_VIEWPORT viewport;
    viewport.Width    = 800;
    viewport.Height   = 600;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    device_context->RSSetViewports(1U, &viewport);

    // device_context->Draw(vertices.size(), 0U);

    device_context->DrawIndexed(std::size(indexs), 0U, 0U);
}

auto Graphics::DrawIndexed(UINT count) -> void
{
    device_context->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
    projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
    return projection;
}
