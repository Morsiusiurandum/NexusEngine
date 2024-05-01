#ifndef DRAWING_H
#define DRAWING_H
#include "../../Component/MeshRenderer.h"

class Drawing : public MeshRenderer<Drawing>
{
public:
    Drawing(
        Graphics                              &graphics,
        std::mt19937                          &rng,
        std::uniform_real_distribution<float> &adist,
        std::uniform_real_distribution<float> &ddist,
        std::uniform_real_distribution<float> &odist,
        std::uniform_real_distribution<float> &rdist);

    auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override;
};
#endif //DRAWING_H
