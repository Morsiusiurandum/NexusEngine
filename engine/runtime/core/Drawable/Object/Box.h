/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef BOX_H
#define BOX_H

#include "../../../modules/component/mesh_renderer.h"
#include "../../mesh/Cube.h"
#include "BindableBase.h"
#include <DirectXMath.h>

class Box final : public MeshRenderer<Box>
{
public:
    Box(Graphics &                             gfx,
        std::mt19937 &                         rng,
        std::uniform_real_distribution<float> &adist,
        std::uniform_real_distribution<float> &ddist,
        std::uniform_real_distribution<float> &odist,
        std::uniform_real_distribution<float> &rdist,
        std::uniform_real_distribution<float> &bdist,
        DirectX::XMFLOAT3                      material)
        : MeshRenderer(gfx, rng, adist, ddist, odist, rdist)
    {
        namespace dx = DirectX;

        if (!IsStaticInitialized())
        {
            struct Vertex
            {
                dx::XMFLOAT3 pos;
                dx::XMFLOAT3 n;
            };

            auto model = Cube::MakeIndependent();
            model.SetNormalsIndependentFlat();

            AddStaticBind(std::make_unique<vertex_buffer>(gfx, model.vertex));

            auto pvs   = std::make_unique<VertexShader>(gfx, L"shader/VertexShader.cso");
            auto pvsbc = pvs->GetBytecode();
            AddStaticBind(std::move(pvs));

            AddStaticBind(std::make_unique<PixelShader>(gfx, L"shader/PixelShader.cso"));

            AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.index));

            struct ConstantBuffer2
            {
                struct
                {
                    float r;
                    float g;
                    float b;
                    float a;
                } face_colors[6];
            };
            const ConstantBuffer2 cb2 =
            {
                {
                    {1.0f, 0.0f, 1.0f},
                    {1.0f, 0.0f, 0.0f},
                    {0.0f, 1.0f, 0.0f},
                    {0.0f, 0.0f, 1.0f},
                    {1.0f, 1.0f, 0.0f},
                    {0.0f, 1.0f, 1.0f},
                }
            };
            AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2> >(gfx, cb2));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                //   {"Normal",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };
            AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

            AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        }
        else
        {
            SetIndexFromStatic();
        }

        AddBind(std::make_unique<TransformCbuf>(gfx, *this));

        // model deformation transform (per instance, not stored as bind)
        XMStoreFloat3x3(
            &mt,
            dx::XMMatrixScaling(1.0f, 1.0f, bdist(rng)));
    }

    explicit Box(Graphics &graphics)
        : MeshRenderer(graphics), mt()
    {
        if (!IsStaticInitialized())
        {
            struct Vertex
            {
                DirectX::XMFLOAT3 pos;
                DirectX::XMFLOAT3 n;
            };

            auto model = Cube::MakeIndependent();
            model.SetNormalsIndependentFlat();

            AddStaticBind(std::make_unique<vertex_buffer>(graphics, model.vertex));

            auto pvs   = std::make_unique<VertexShader>(graphics, L"shader/VertexShader.cso");
            auto pvsbc = pvs->GetBytecode();
            AddStaticBind(std::move(pvs));

            AddStaticBind(std::make_unique<PixelShader>(graphics, L"shader/PixelShader.cso"));

            AddStaticIndexBuffer(std::make_unique<IndexBuffer>(graphics, model.index));

            struct ConstantBuffer2
            {
                struct
                {
                    float r;
                    float g;
                    float b;
                    float a;
                } face_colors[6];
            };
            const ConstantBuffer2 cb2 =
            {
                {
                    {1.0f, 0.0f, 1.0f},
                    {1.0f, 0.0f, 0.0f},
                    {0.0f, 1.0f, 0.0f},
                    {0.0f, 0.0f, 1.0f},
                    {1.0f, 1.0f, 0.0f},
                    {0.0f, 1.0f, 1.0f},
                }
            };
            AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2> >(graphics, cb2));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                //   {"Normal",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };
            AddStaticBind(std::make_unique<InputLayout>(graphics, ied, pvsbc));

            AddStaticBind(std::make_unique<Topology>(graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        }
        else
        {
            SetIndexFromStatic();
        }

        AddBind(std::make_unique<TransformCbuf>(graphics, *this));

        std::mt19937                   rng{std::random_device{}()};
        std::uniform_real_distribution bdist{0.4f, 3.0f};

        auto [x, y, z] = transform.scale;
        // model deformation transform (per instance, not stored as bind)
        XMStoreFloat3x3(
            &mt,
            DirectX::XMMatrixScaling(x, y, bdist(rng)));
    }

    [[nodiscard]] auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override
    {

        return XMLoadFloat3x3(&mt)
               * DirectX::XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z) //移动
               * DirectX::XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
    }

private:
    // model transform
    DirectX::XMFLOAT3X3 mt{};
};
#endif //BOX_H
