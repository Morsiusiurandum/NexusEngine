#include "Bindable.h"

auto Bindable::GetDevice(Graphics &graphics) noexcept -> ID3D11Device *
{
        return graphics.device.Get();
}

auto Bindable::GetDeviceContext(Graphics &graphics) noexcept -> ID3D11DeviceContext *
{
    return graphics.device_context.Get();
}
