#include "VertexBuffer.h"
 
auto VertexBuffer::Bind(Graphics &graphics) noexcept -> void
{
    const  UINT offset = 0U;
    GetDeviceContext(graphics)->IASetVertexBuffers(0U, 1U, vertex_buffer.GetAddressOf(), &stride, &offset);
}
