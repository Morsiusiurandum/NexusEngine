/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Bindable.h"

class Texture : public Bindable
{
public:
    Texture(Graphics &graphics, const class Surface &s);
    void Bind(Graphics &graphics) noexcept override;

protected:
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resources_view_com_ptr;
};

#endif //TEXTURE_H
