#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "Bindable.h"

class Topology : public Bindable
{
public:
    Topology(Graphics &graphics, D3D11_PRIMITIVE_TOPOLOGY type);
    auto Bind(Graphics &graphics) noexcept -> void override;

private:
    D3D11_PRIMITIVE_TOPOLOGY type;
};

#endif //TOPOLOGY_H
