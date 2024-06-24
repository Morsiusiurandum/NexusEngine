/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "../vertex.h"
#include "Bindable.h"

#include <vector>

namespace windows_dirtex11
{
    /**
     * \brief Vertex data buffers bound on DirectX.
     */
    class vertex_buffer final : public Bindable
    {
    public:
        vertex_buffer(Graphics &graphics, const std::vector<vertex> &vertex_vector)
            : stride(sizeof(vertex))
        {
            D3D11_BUFFER_DESC buffer_desc   = {};
            buffer_desc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
            buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
            buffer_desc.CPUAccessFlags      = 0U;
            buffer_desc.MiscFlags           = 0U;
            buffer_desc.ByteWidth           = vertex_vector.size() * sizeof(vertex);
            buffer_desc.StructureByteStride = sizeof(vertex);

            D3D11_SUBRESOURCE_DATA subresource_data = {};
            subresource_data.pSysMem                = vertex_vector.data();

            GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_comptr_));
        }

        auto Bind(Graphics &graphics) noexcept -> void override
        {
            constexpr UINT offset = 0U;
            GetDeviceContext(graphics)->IASetVertexBuffers(0U, 1U, vertex_buffer_comptr_.GetAddressOf(), &stride, &offset);
        }

    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_comptr_;
        UINT                                 stride;
    };
} // namespace windows_dirtex11
#endif //VERTEX_BUFFER_H
