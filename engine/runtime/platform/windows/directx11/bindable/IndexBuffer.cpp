/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics &graphics, const std::vector<unsigned short> &index)
    : count(index.size())
{
    D3D11_BUFFER_DESC buffer_desc   = {};
    buffer_desc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
    buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
    buffer_desc.CPUAccessFlags      = 0U;
    buffer_desc.MiscFlags           = 0U;
    buffer_desc.ByteWidth           = count * sizeof(unsigned short);
    buffer_desc.StructureByteStride = 16U;

    D3D11_SUBRESOURCE_DATA subresource_data = {};
    subresource_data.pSysMem                = index.data();

    GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, &subresource_data, &index_buffer));
}

auto IndexBuffer::Bind(Graphics &graphics) noexcept -> void
{
    GetDeviceContext(graphics)->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R16_UINT, 0U);
}

auto IndexBuffer::GetCount() const noexcept -> UINT
{
    return count;
}
