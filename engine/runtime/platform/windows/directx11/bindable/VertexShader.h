/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 */

#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
    VertexShader(Graphics &gfx, const std::wstring &path);

    void Bind(Graphics &gfx) noexcept override;
    auto GetBytecode() const noexcept -> ID3DBlob *;

protected:
    Microsoft::WRL::ComPtr<ID3DBlob>           blob_com_ptr;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_com_ptr;
};

#endif //VERTEX_SHADER_H
