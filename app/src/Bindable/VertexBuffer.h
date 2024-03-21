#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "Bindable.h"
#include <vector>

class VertexBuffer : public Bindable
{
public:
    template<class V>
    VertexBuffer(Graphics &graphics, const std::vector<V> &vertex_vector)
        : stride(sizeof(V))
    {
        D3D11_BUFFER_DESC buffer_desc   = {};
        buffer_desc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
        buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
        buffer_desc.CPUAccessFlags      = 0U;
        buffer_desc.MiscFlags           = 0U;
        buffer_desc.ByteWidth           = vertex_vector.size() * sizeof(V);
        buffer_desc.StructureByteStride = sizeof(V);

        D3D11_SUBRESOURCE_DATA subresource_data = {};
        subresource_data.pSysMem                = vertex_vector.data();

        GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer));
    }

    auto Bind(Graphics &graphics) noexcept -> void override;

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
    UINT                                 stride;
};

#endif //VERTEX_BUFFER_H
