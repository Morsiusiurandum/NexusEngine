/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef MESH_CONE_H
#define MESH_CONE_H

#include "IndexedTriangle.h"
#include "NexusMath.h"
#include <DirectXMath.h>

class Cone
{
public:
    static IndexedTriangle GetMesh(int longDiv = 24)
    {

        assert(longDiv >= 3);

        const auto  base           = DirectX::XMVectorSet(1.0f, 0.0f, -1.0f, 0.0f);
        const float longitudeAngle = 2.0f * PI / longDiv;

        // base vertices
        std::vector<windows_dirtex11::vertex> vertices;
        for (int iLong = 0; iLong < longDiv; iLong++)
        {
            vertices.emplace_back();
            auto v = DirectX::XMVector3Transform(
                base,
                DirectX::XMMatrixRotationZ(longitudeAngle * iLong));
            DirectX::XMStoreFloat3(&vertices.back().pos, v);
        }
        // the center
        vertices.emplace_back();
        vertices.back().pos = {0.0f, 0.0f, -1.0f};
        const auto iCenter  = static_cast<unsigned short>(vertices.size() - 1);
        // the tip :darkness:
        vertices.emplace_back();
        vertices.back().pos = {0.0f, 0.0f, 1.0f};
        const auto iTip     = static_cast<unsigned short>(vertices.size() - 1);

        // base indices
        std::vector<unsigned short> indices;
        for (unsigned short iLong = 0; iLong < longDiv; iLong++)
        {
            indices.push_back(iCenter);
            indices.push_back((iLong + 1) % longDiv);
            indices.push_back(iLong);
        }

        // cone indices
        for (unsigned short iLong = 0; iLong < longDiv; iLong++)
        {
            indices.push_back(iLong);
            indices.push_back((iLong + 1) % longDiv);
            indices.push_back(iTip);
        }

        return {std::move(vertices), std::move(indices)};
    }
};
#endif
