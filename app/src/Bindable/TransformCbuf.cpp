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
