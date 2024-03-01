#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <NexusMacro.h>
#include <d3d11.h>

#include "Exception/GraphicsException.h"

class Graphics
{
public:
    /**
     * \brief Default constructor
     * \param window current window pointer
     */
    explicit Graphics(HWND window);

    Graphics(const GraphicsException &) = delete;

    ~Graphics();

    auto operator=(const Graphics &) -> Graphics & = delete;

    auto EndFrame() -> void;

    auto ClearBuffer(float r, float g, float b) noexcept -> void;

private:
    ID3D11Device           *device_             = nullptr;
    IDXGISwapChain         *swap_chain_         = nullptr;
    ID3D11DeviceContext    *device_context_     = nullptr;
    ID3D11RenderTargetView *render_target_view_ = nullptr;
};

#endif // GRAPHICS_H
