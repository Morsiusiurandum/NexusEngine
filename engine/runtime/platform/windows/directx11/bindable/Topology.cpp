/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "Topology.h"

Topology::Topology(Graphics &graphics, D3D11_PRIMITIVE_TOPOLOGY type)
    : type(type)
{
}

auto Topology::Bind(Graphics &graphics) noexcept -> void
{
    GetDeviceContext(graphics)->IASetPrimitiveTopology(type);
}
