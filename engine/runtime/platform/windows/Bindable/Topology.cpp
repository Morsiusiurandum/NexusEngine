#include "Topology.h"

Topology::Topology(Graphics &graphics, D3D11_PRIMITIVE_TOPOLOGY type)
    : type(type)
{
}

auto Topology::Bind(Graphics &graphics) noexcept -> void
{
    GetDeviceContext(graphics)->IASetPrimitiveTopology(type);
}
