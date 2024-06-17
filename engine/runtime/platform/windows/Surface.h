#ifndef SURFACE_H
#define SURFACE_H

#include "../../utils/Color.h"
#include "Exception/Exception.h"

#include "windows_platform_macro.h"
#include <DirectXMath.h>
#include <DirectXTex.h>
#include <dxgiformat.h>
#include <optional>
#include <string>

class Surface
{

public:
    class InException : public Exception
    {
    public:
        InException(int line, const char *file, std::string note, std::optional<HRESULT> hr = {}) noexcept;
        InException(int line, const char *file, const std::string& filename, const std::string& note, std::optional<HRESULT> hr = {}) noexcept;

        auto what() const noexcept -> const char * override;
        auto GetType() const noexcept -> const char * override;
        auto GetNote() const noexcept -> const std::string &;

    private:
        std::optional<HRESULT> hr;
        std::string            note;
    };

public:
    Surface(unsigned int width, unsigned int height);
    Surface(Surface &&source) noexcept = default;
    Surface(Surface &)                 = delete;
    ~Surface()                         = default;

    auto operator=(Surface &&donor) noexcept -> Surface & = default;
    auto operator=(const Surface &) -> Surface          & = delete;

    void Clear(Color fillValue) noexcept;
    void PutPixel(unsigned int x, unsigned int y, Color c) noexcept(!IS_DEBUG);
    void Save(const std::string &filename) const;

    [[nodiscard]] auto GetPixel(unsigned int x, unsigned int y) const noexcept(!IS_DEBUG) -> Color;
    [[nodiscard]] auto GetWidth() const noexcept -> unsigned int;
    [[nodiscard]] auto GetHeight() const noexcept -> unsigned int;
    [[nodiscard]] auto GetBytePitch() const noexcept -> unsigned int;
    [[nodiscard]] auto GetBufferPtr() noexcept -> Color *;
    [[nodiscard]] auto GetBufferPtr() const noexcept -> const Color *;
    [[nodiscard]] auto GetBufferPtrConst() const noexcept -> const Color *;
    [[nodiscard]] auto AlphaLoaded() const noexcept -> bool;

    static auto LoadFromFile(const std::string &name) -> Surface;

private:
    explicit Surface(DirectX::ScratchImage scratch) noexcept;

private:
    static constexpr DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
    DirectX::ScratchImage        scratch;
};

#endif //SURFACE_H
