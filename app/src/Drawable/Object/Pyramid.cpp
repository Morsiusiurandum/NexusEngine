#include "Pyramid.h"
#include "../Mesh/Cone.h"
#include "BindableBase.h"

Pyramid::Pyramid( Graphics& gfx,
                 std::mt19937& rng,
                 std::uniform_real_distribution<float>& adist,
                 std::uniform_real_distribution<float>& ddist,
                 std::uniform_real_distribution<float>& odist,
                 std::uniform_real_distribution<float>& rdist )
    : MeshRenderer(gfx, rng, adist, ddist, odist, rdist)
       
{
    namespace dx = DirectX;

    if( !IsStaticInitialized() )
    {
        struct Vertex
        {
            dx::XMFLOAT3 pos;
            struct
            {
                unsigned char r;
                unsigned char g;
                unsigned char b;
                unsigned char a;
            } color;
        };
        auto model = Cone::MakeTesselated<Vertex>( 4 );
        // set vertex colors for mesh
        model.vertex[0].color = { 255,255,0 };
        model.vertex[1].color = { 255,255,0 };
        model.vertex[2].color = { 255,255,0 };
        model.vertex[3].color = { 255,255,0 };
        model.vertex[4].color = { 255,255,80 };
        model.vertex[5].color = { 255,10,0 };
        // deform mesh linearly
        model.Transform( dx::XMMatrixScaling( 1.0f,1.0f,0.7f ) );

        AddStaticBind( std::make_unique<VertexBuffer>( gfx,model.vertex ) );

        auto pvs = std::make_unique<VertexShader>( gfx,L"shader/ColorBlenderVS.cso" );
        auto pvsbc = pvs->GetBytecode();
        AddStaticBind( std::move( pvs ) );

        AddStaticBind( std::make_unique<PixelShader>( gfx,L"shader/ColorBlenderPS.cso" ) );

        AddStaticIndexBuffer( std::make_unique<IndexBuffer>( gfx,model.index ) );

        const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
                { "Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
        };
        AddStaticBind( std::make_unique<InputLayout>( gfx,ied,pvsbc ) );

        AddStaticBind( std::make_unique<Topology>( gfx,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
    }
    else
    {
        SetIndexFromStatic();
    }

    AddBind( std::make_unique<TransformCbuf>( gfx,*this ) );
}

 

auto Pyramid::GetTransformXM() const noexcept -> DirectX::XMMATRIX
{
    return MeshRenderer::GetTransformXM();
}