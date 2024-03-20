#ifndef SAMPLER_H
#define SAMPLER_H

#include "Bindable.h"

class Sampler : public Bindable
{
public:
    explicit Sampler(Graphics &graphics);
    void Bind(Graphics &graphics) noexcept override;

protected:
    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_com_ptr;
};

#endif //SAMPLER_H
