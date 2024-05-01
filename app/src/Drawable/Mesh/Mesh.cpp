#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertex_in, std::vector<uint16_t> index_in): vertex(std::move(vertex_in)), index(std::move(index_in))
{
    assert(vertex.size() > 2);
    assert(index.size() % 3 == 0);
}

void Mesh::UpdateTransform(DirectX::FXMMATRIX &transform)
{
    for (auto &[pos, n]: vertex)
    {
        const auto old_pos = XMLoadFloat3(&pos);
        const auto new_pos = XMVector3Transform(old_pos, transform);
        XMStoreFloat3(&pos, new_pos);
    }
}

void Mesh::SetNormalsIndependentFlat() noexcept(!false)
{
    using namespace DirectX;

    assert(index.size() % 3 == 0 && !index.empty());
    for (size_t i = 0; i < index.size(); i += 3)
    {
        auto &v0 = vertex[index[i]];
        auto &v1 = vertex[index[i + 1]];
        auto &v2 = vertex[index[i + 2]];

        const auto p0 = XMLoadFloat3(&v0.pos);
        const auto p1 = XMLoadFloat3(&v1.pos);
        const auto p2 = XMLoadFloat3(&v2.pos);

        const auto n = XMVector3Normalize(XMVector3Cross(p1 - p0, p2 - p0));

        XMStoreFloat3(&v0.n, n);
        XMStoreFloat3(&v1.n, n);
        XMStoreFloat3(&v2.n, n);
    }
}
