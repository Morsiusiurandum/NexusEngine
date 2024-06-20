/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#ifndef  INPUT_LAYOUT_H 
#define INPUT_LAYOUT_H

#include "Bindable.h"
#include <vector>

class InputLayout : public Bindable
{
public:
    InputLayout( Graphics& gfx,
                const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
                ID3DBlob* pVertexShaderBytecode );
    void Bind( Graphics& gfx ) noexcept override;
protected:
    Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

#endif //INPUT_LAYOUT_H
