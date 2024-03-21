#include "VertexShader.h"
#include <d3dcompiler.h>
 
VertexShader::VertexShader(Graphics &gfx, const std::wstring &path)
{
    GRAPHICS_EXCEPTION(D3DReadFileToBlob(path.c_str(), &blob_com_ptr));
    GRAPHICS_EXCEPTION(GetDevice(gfx)->CreateVertexShader(
        blob_com_ptr->GetBufferPointer(),
        blob_com_ptr->GetBufferSize(),
        nullptr,
        &vertex_shader_com_ptr));
}

void VertexShader::Bind(Graphics &gfx) noexcept
{
    GetDeviceContext(gfx)->VSSetShader(vertex_shader_com_ptr.Get(), nullptr, 0u);
}

auto VertexShader::GetBytecode() const noexcept -> ID3DBlob *
{
    return blob_com_ptr.Get();
}
