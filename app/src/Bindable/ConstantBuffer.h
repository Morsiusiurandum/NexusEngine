#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
    ConstantBuffer(Graphics &graphics, const C &consts)
    {
        D3D11_BUFFER_DESC buffer_desc   = {};
        buffer_desc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
        buffer_desc.Usage               = D3D11_USAGE_DYNAMIC;
        buffer_desc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
        buffer_desc.MiscFlags           = 0U;
        buffer_desc.ByteWidth           = sizeof(consts);
        buffer_desc.StructureByteStride = 0U;

        D3D11_SUBRESOURCE_DATA subresource_data = {};
        subresource_data.pSysMem                = &consts;

        GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, &subresource_data, &const_buffer));
    }

    ConstantBuffer(Graphics &graphics)
    {
        D3D11_BUFFER_DESC buffer_desc   = {};
        buffer_desc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
        buffer_desc.Usage               = D3D11_USAGE_DYNAMIC;
        buffer_desc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
        buffer_desc.MiscFlags           = 0U;
        buffer_desc.ByteWidth           = sizeof(C);
        buffer_desc.StructureByteStride = 0U;

        GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, nullptr, &const_buffer));
    }

    void Update(Graphics &graphics, const C &consts)
    {
        D3D11_MAPPED_SUBRESOURCE mapped_subresource;
        GRAPHICS_EXCEPTION(GetDeviceContext(graphics)->Map(const_buffer.Get(), 0U, D3D11_MAP_WRITE_DISCARD, 0U, &mapped_subresource));
        memcpy(mapped_subresource.pData, &consts, sizeof(consts));
        GetDeviceContext(graphics)->Unmap(const_buffer.Get(), 0U);
    }

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> const_buffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
    using ConstantBuffer<C>::const_buffer;
    using Bindable::GetDeviceContext;

public:
    using ConstantBuffer<C>::ConstantBuffer;

    auto Bind(Graphics &graphics) noexcept -> void override
    {
        GetDeviceContext(graphics)->VSSetConstantBuffers(0u, 1u, const_buffer.GetAddressOf());
    }
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
    using ConstantBuffer<C>::const_buffer;
    using Bindable::GetDeviceContext;

public:
    using ConstantBuffer<C>::ConstantBuffer;

    auto Bind(Graphics &graphics) noexcept -> void override
    {
        GetDeviceContext(graphics)->PSSetConstantBuffers(0u, 1u, const_buffer.GetAddressOf());
    }
};

#endif //CONSTANT_BUFFER_H
