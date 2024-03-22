#ifndef PYRAMID_H
#define PYRAMID_H

#include "Object.h"
#include <random>

class Pyramid : public Object<Pyramid>
{
public:
    Pyramid(Graphics &gfx, std::mt19937 &rng,
            std::uniform_real_distribution<float> &adist,
            std::uniform_real_distribution<float> &ddist,
            std::uniform_real_distribution<float> &odist,
            std::uniform_real_distribution<float> &rdist);
    auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override;
};
#endif //PYRAMID_H
