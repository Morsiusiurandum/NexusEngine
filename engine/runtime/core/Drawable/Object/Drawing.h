/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef DRAWING_H
#define DRAWING_H

#include "../../../modules/component/mesh_renderer.h"
#include  "BindableBase.h"
#include "../../../platform/windows/Surface.h"
#include "../../mesh/Plane.h"

/**
 * \brief Use an image as a plane texture.
 */
class Drawing final : public MeshRenderer<Drawing>
{
public:
    Drawing(
        Graphics &                             graphics,
        std::mt19937 &                         rng,
        std::uniform_real_distribution<float> &adist,
        std::uniform_real_distribution<float> &ddist,
        std::uniform_real_distribution<float> &odist,
        std::uniform_real_distribution<float> &rdist)
        : MeshRenderer(graphics, rng, adist, ddist, odist, rdist)
    {

        if (!IsStaticInitialized())
        {
            struct Vertex
            {
                DirectX::XMFLOAT3 pos;
                struct
                {
                    float u;
                    float v;
                } tex;
            };
            auto model          = Plane::Make<Vertex>();
            model.vertex[0].tex = {0.0f, 0.0f};
            model.vertex[1].tex = {1.0f, 0.0f};
            model.vertex[2].tex = {0.0f, 1.0f};
            model.vertex[3].tex = {1.0f, 1.0f};

            AddStaticBind(std::make_unique<Texture>(graphics, Surface::LoadFromFile("Images\\kappa50.png")));

            AddStaticBind(std::make_unique<windows_dirtex11::vertex_buffer>(graphics, model.vertex));

            AddStaticBind(std::make_unique<Sampler>(graphics));

            auto vertex_Shader = std::make_unique<VertexShader>(graphics, L"shader\\TextureVS.cso");
            auto pvsbc         = vertex_Shader->GetBytecode();
            AddStaticBind(std::move(vertex_Shader));

            AddStaticBind(std::make_unique<PixelShader>(graphics, L"shader\\TexturePS.cso"));

            AddStaticIndexBuffer(std::make_unique<IndexBuffer>(graphics, model.index));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            };
            AddStaticBind(std::make_unique<InputLayout>(graphics, ied, pvsbc));

            AddStaticBind(std::make_unique<Topology>(graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        }
        else
        {
            SetIndexFromStatic();
        }

        AddBind(std::make_unique<TransformCbuf>(graphics, *this));
    }

    auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override
    {

        return MeshRenderer::GetTransformXM();
    }
};
#endif //DRAWING_H
