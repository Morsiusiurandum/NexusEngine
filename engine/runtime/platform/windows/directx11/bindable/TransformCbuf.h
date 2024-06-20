/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef TRANSFORM_CBUF_H
#define TRANSFORM_CBUF_H

#include "../core/Drawable/DrawableBase.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>

 
class TransformCbuf : public Bindable
{
public:
    TransformCbuf(Graphics &gfx, const DrawableBase &parent);
    void Bind(Graphics &gfx) noexcept override;

private:
    VertexConstantBuffer<DirectX::XMMATRIX> vcbuf;
    const DrawableBase                     &parent;
};
#endif //TRANSFORM_CBUF_H
