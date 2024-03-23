#ifndef BOX_H
#define BOX_H

#include "MeshRenderer.h"

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
        DirectX::XMFLOAT3                      material);

    explicit Box(Graphics &graphics);
    
    [[nodiscard]] auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override;

private:
    // model transform
    DirectX::XMFLOAT3X3 mt;
};
#endif //BOX_H
