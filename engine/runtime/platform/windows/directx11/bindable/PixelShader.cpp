/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "PixelShader.h"
#include <d3dcompiler.h>
 

PixelShader::PixelShader(Graphics &gfx, const std::wstring &path)
{

    Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
    GRAPHICS_EXCEPTION(D3DReadFileToBlob(path.c_str(), &pBlob));
    GRAPHICS_EXCEPTION(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pixel_shader_com_ptr));
}

void PixelShader::Bind(Graphics &gfx) noexcept
{
    GetDeviceContext(gfx)->PSSetShader(pixel_shader_com_ptr.Get(), nullptr, 0u);
}
