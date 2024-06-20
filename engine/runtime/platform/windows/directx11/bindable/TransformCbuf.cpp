/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics &gfx, const DrawableBase &parent)
    : vcbuf(gfx),
      parent(parent)
{
}

void TransformCbuf::Bind(Graphics &gfx) noexcept
{
    vcbuf.Update(gfx, XMMatrixTranspose(parent.GetTransformXM() * gfx.GetCamera() *gfx.GetProjection()));
    vcbuf.Bind(gfx);
}
