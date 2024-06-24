/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#include "Mesh.h"

Mesh::Mesh(std::vector<windows_dirtex11::vertex> vertex_in, std::vector<uint16_t> index_in): vertex(std::move(vertex_in)), index(std::move(index_in))
{
    assert(vertex.size() > 2);
    assert(index.size() % 3 == 0);
}

void Mesh::UpdateTransform(DirectX::FXMMATRIX &transform)
{
    for (auto &[pos, n, tex, color]: vertex)
    {
        const auto old_pos = DirectX::XMLoadFloat3(&pos);
        const auto new_pos = XMVector3Transform(old_pos, transform);
        DirectX::XMStoreFloat3(&pos, new_pos);
    }
}

void Mesh::SetNormalsIndependentFlat() noexcept(!false)
{

    assert(index.size() % 3 == 0 && !index.empty());
    for (size_t i = 0; i < index.size(); i += 3)
    {
        auto &v0 = vertex[index[i]];
        auto &v1 = vertex[index[i + 1]];
        auto &v2 = vertex[index[i + 2]];

        const auto p0 = XMLoadFloat3(&v0.pos);
        const auto p1 = XMLoadFloat3(&v1.pos);
        const auto p2 = XMLoadFloat3(&v2.pos);

        const auto v3_1 = DirectX::XMVectorSubtract(p1, p0);
        const auto v3_2 = DirectX::XMVectorSubtract(p2, p0);

        const auto n = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(v3_1, v3_2));

        XMStoreFloat3(&v0.n, n);
        XMStoreFloat3(&v1.n, n);
        XMStoreFloat3(&v2.n, n);
    }
}
