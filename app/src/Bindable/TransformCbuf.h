#ifndef TRANSFORM_CBUF_H
#define TRANSFORM_CBUF_H

#include "ConstantBuffer.h"
#include "../Drawable/Drawable.h"
#include <DirectXMath.h>

class TransformCbuf : public Bindable
{
public:
    TransformCbuf(Graphics &gfx, const Drawable &parent);
    void Bind(Graphics &gfx) noexcept override;

private:
    VertexConstantBuffer<DirectX::XMMATRIX> vcbuf;
    const Drawable                         &parent;
};
#endif //TRANSFORM_CBUF_H
