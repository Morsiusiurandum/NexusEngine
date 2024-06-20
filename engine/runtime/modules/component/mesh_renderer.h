/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <random>

#include "../../core/Drawable/Drawable.h"
#include "Transform.h"

template<class T>
class MeshRenderer : public DrawableBase
{
public:
    MeshRenderer(Graphics                              &gfx,
                 std::mt19937                          &rng,
                 std::uniform_real_distribution<float> &adist,
                 std::uniform_real_distribution<float> &ddist,
                 std::uniform_real_distribution<float> &odist,
                 std::uniform_real_distribution<float> &rdist)
        : r(rdist(rng)),
          theta(adist(rng)),
          phi(adist(rng)),
          chi(adist(rng)),
          droll(ddist(rng)),
          dpitch(ddist(rng)),
          dyaw(ddist(rng)),
          dtheta(odist(rng)),
          dphi(odist(rng)),
          dchi(odist(rng)),
          transform()
    {
    }

    explicit MeshRenderer(const Graphics &)
        : r(0), theta(0), phi(0), chi(0), droll(0), dpitch(0), dyaw(0), dtheta(0), dphi(0), dchi(0), transform()
    {
    }

    void Update(const float dt) noexcept override
    {
        roll += droll * dt;
        pitch += dpitch * dt;
        yaw += dyaw * dt;
        theta += dtheta * dt;
        phi += dphi * dt;
        chi += dchi * dt;
    }

    [[nodiscard]] auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override
    {

        return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)   //转动
               * DirectX::XMMatrixTranslation(r, 0.0f, 0.0f)             //移动
               * DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi); //转到
    }

protected:
    static auto IsStaticInitialized() noexcept -> bool
    {
        return !staticBinds.empty();
    }

    static void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG)
    {
        assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
        staticBinds.push_back(std::move(bind));
    }

    void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer) noexcept(!IS_DEBUG)
    {
        assert("Attempting to add index buffer a second time" && index_buffer_ptr == nullptr);
        index_buffer_ptr = index_buffer.get();
        staticBinds.push_back(std::move(index_buffer));
    }

    void SetIndexFromStatic() noexcept(!IS_DEBUG)
    {
        assert("Attempting to add index buffer a second time" && index_buffer_ptr == nullptr);
        for (const auto &b: staticBinds)
        {
            if (const auto p = dynamic_cast<IndexBuffer *>(b.get()))
            {
                index_buffer_ptr = p;
                return;
            }
        }
        assert("Failed to find index buffer in static binds" && index_buffer_ptr != nullptr);
    }

private:
    [[nodiscard]] auto GetStaticBinds() const noexcept -> const std::vector<std::unique_ptr<Bindable>> & override
    {
        return staticBinds;
    }

    static std::vector<std::unique_ptr<Bindable>> staticBinds;

    // positional
    float r;
    float roll  = 0.0f;
    float pitch = 0.0f;
    float yaw   = 0.0f;
    float theta;
    float phi;
    float chi;
    // speed (delta/s)
    float droll;
    float dpitch;
    float dyaw;
    float dtheta;
    float dphi;
    float dchi;

public:
    Transform transform;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> MeshRenderer<T>::staticBinds;

#endif
