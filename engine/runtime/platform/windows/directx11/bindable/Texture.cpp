/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "Texture.h"
#include "../Surface.h"

Texture::Texture(Graphics &graphics, const Surface &s)
{
    // create texture resource
    D3D11_TEXTURE2D_DESC texture_desc = {};
    texture_desc.Width                = s.GetWidth();
    texture_desc.Height               = s.GetHeight();
    texture_desc.MipLevels            = 1;
    texture_desc.ArraySize            = 1;
    texture_desc.Format               = DXGI_FORMAT_B8G8R8A8_UNORM;
    texture_desc.SampleDesc.Count     = 1;
    texture_desc.SampleDesc.Quality   = 0;
    texture_desc.Usage                = D3D11_USAGE_DEFAULT;
    texture_desc.BindFlags            = D3D11_BIND_SHADER_RESOURCE;
    texture_desc.CPUAccessFlags       = 0;
    texture_desc.MiscFlags            = 0;
    D3D11_SUBRESOURCE_DATA sd        = {};
    sd.pSysMem                       = s.GetBufferPtr();
    sd.SysMemPitch                   = s.GetWidth() * sizeof(Color);
    
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_com_ptr;
    GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateTexture2D(&texture_desc, &sd, &texture_com_ptr));

    // create the resource view on the texture
    D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc = {};
    shader_resource_view_desc.Format                          = texture_desc.Format;
    shader_resource_view_desc.ViewDimension                   = D3D11_SRV_DIMENSION_TEXTURE2D;
    shader_resource_view_desc.Texture2D.MostDetailedMip       = 0;
    shader_resource_view_desc.Texture2D.MipLevels             = 1;
    GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateShaderResourceView(
        texture_com_ptr.Get(), &shader_resource_view_desc, &shader_resources_view_com_ptr));
}

void Texture::Bind(Graphics &graphics) noexcept
{
    GetDeviceContext(graphics)->PSSetShaderResources(0U, 1U, shader_resources_view_com_ptr.GetAddressOf());
}
