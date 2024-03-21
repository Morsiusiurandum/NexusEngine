#ifndef OBJECT_H
#define OBJECT_H

#include "Drawable.h"
#include <random>

template<class T>
class Object : public Drawable<T>
{
public:
    Object(Graphics &gfx, std::mt19937 &rng,
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
          dchi(odist(rng))
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

    [[nodiscard]] DirectX::XMMATRIX GetTransformXM() const noexcept override
    {
        namespace dx = DirectX;
        return dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * dx::XMMatrixTranslation(r, 0.0f, 0.0f) * dx::XMMatrixRotationRollPitchYaw(theta, phi, chi);
    }

private:
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
};
#endif //OBJECT_H
