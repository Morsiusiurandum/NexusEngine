/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include "Bindable.h"

class PixelShader : public Bindable
{
public:
    PixelShader(Graphics &gfx, const std::wstring &path);
    void Bind(Graphics &gfx) noexcept override;

protected:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_com_ptr;
};
#endif //PIXEL_SHADER_H
