#include "Sampler.h"

Sampler::Sampler(Graphics &graphics)
{
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter             = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;

    GRAPHICS_EXCEPTION(GetDevice(graphics)->CreateSamplerState(&samplerDesc, &sampler_com_ptr));
}

void Sampler::Bind(Graphics &graphics) noexcept
{
    GetDeviceContext(graphics)->PSSetSamplers(0U, 1U, sampler_com_ptr.GetAddressOf());
}
