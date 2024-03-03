#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <NexusMacro.h>
#include <array>
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>

#include "Exception/GraphicsException.h"

#define GRAPHICS_EXCEPTION(hr)  \
    if (hr != SEVERITY_SUCCESS) \
    throw GraphicsException(__LINE__, __FILE__, hr)

class Graphics
{
public:
    /**
     * \brief Default constructor
     * \param window current window pointer
     */
    explicit Graphics(HWND window);

    Graphics(const GraphicsException &) = delete;

    ~Graphics() = default;

    auto operator=(const Graphics &) -> Graphics & = delete;

    auto EndFrame() -> void;

    auto ClearBuffer(float r, float g, float b) noexcept -> void;

    auto Draw(float a) -> void;

private:
    Microsoft::WRL::ComPtr<ID3D11Device>           device;
    Microsoft::WRL::ComPtr<IDXGISwapChain>         swap_chain;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>    device_context;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
};

#endif // GRAPHICS_H
