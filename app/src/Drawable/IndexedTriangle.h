#ifndef INDEXED_TRIANGLE_H
#define INDEXED_TRIANGLE_H

#include <vector>

#include <DirectXMath.h>

template<class T>
class IndexedTriangle
{
public:
    IndexedTriangle() = default;
    IndexedTriangle(std::vector<T> vertex_in, std::vector<uint16_t> index_in)
        : vertex(std::move(vertex_in)),
          index(std::move(index_in))
    {
        assert(vertex.size() > 2);
        assert(index.size() % 3 == 0);
    }

    void Transform(DirectX::FXMMATRIX matrix)
    {
        for (auto &v: vertex)
        {
            const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&v.pos);
            DirectX::XMStoreFloat3(
                &v.pos,
                DirectX::XMVector3Transform(pos, matrix));
        }
    }
    // asserts face-independent vertices w/ normals cleared to zero
    void SetNormalsIndependentFlat() //noexcept( !IS_DEBUG)
    {
        using namespace DirectX;

        assert(index.size() % 3 == 0 && !index.empty());
        for (size_t i = 0; i < index.size(); i += 3)
        {
            auto &v0 = vertex[index[i]];
            auto &v1 = vertex[index[i + 1]];
            auto &v2 = vertex[index[i + 2]];

         
            const auto p0 = XMLoadFloat3( &v0.pos );
            const auto p1 = XMLoadFloat3( &v1.pos );
            const auto p2 = XMLoadFloat3( &v2.pos );
            
            const auto n = XMVector3Normalize( XMVector3Cross( (p1 - p0),(p2 - p0) ) );
			
            XMStoreFloat3( &v0.n,n );
            XMStoreFloat3( &v1.n,n );
            XMStoreFloat3( &v2.n,n );
        }
    }

public:
    std::vector<T>        vertex;
    std::vector<uint16_t> index;
};

#endif //INDEXED_TRIANGLE_H
