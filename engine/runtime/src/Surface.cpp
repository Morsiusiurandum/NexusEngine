#include "Surface.h"
#include "Exception/WindowException.h"
#include "NexusMacro.h"
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <sstream>

std::wstring ToWide(const std::string &narrow)
{
    wchar_t wide[512];
    mbstowcs_s(nullptr, wide, narrow.c_str(), _TRUNCATE);
    return wide;
}

Surface::Surface(DirectX::ScratchImage scratch) noexcept
    : scratch(std::move(scratch))
{
}

Surface::Surface(unsigned int width, unsigned int height)
{
    HRESULT hr = scratch.Initialize2D(format, width, height, 1u, 1u);
    if (FAILED(hr))
    {
        throw Surface::InException(__LINE__, __FILE__, "Failed to initialize ScratchImage", hr);
    }
}

void Surface::Clear(Color fillValue) noexcept
{
    const auto width   = GetWidth();
    const auto height  = GetHeight();
    auto      &imgData = *scratch.GetImage(0, 0, 0);
    for (size_t y = 0u; y < height; y++)
    {
        auto rowStart = reinterpret_cast<Color *>(imgData.pixels + imgData.rowPitch * y);
        std::fill(rowStart, rowStart + imgData.width, fillValue);
    }
}

void Surface::PutPixel(unsigned int x, unsigned int y, Color c) noexcept(!IS_DEBUG)
{
    assert(x >= 0);
    assert(y >= 0);
    assert(x < GetWidth());
    assert(y < GetHeight());

    auto &imgData = *scratch.GetImage(0, 0, 0);

    reinterpret_cast<Color *>(&imgData.pixels[y * imgData.rowPitch])[x] = c;
}

auto Surface::GetPixel(unsigned int x, unsigned int y) const noexcept(!IS_DEBUG) -> Color
{
    assert(x >= 0);
    assert(y >= 0);
    assert(x < GetWidth());
    assert(y < GetHeight());
    auto &imgData = *scratch.GetImage(0, 0, 0);
    return reinterpret_cast<Color *>(&imgData.pixels[y * imgData.rowPitch])[x];
}

auto Surface::GetWidth() const noexcept -> unsigned int
{
    return static_cast<unsigned int>(scratch.GetMetadata().width);
}

auto Surface::GetHeight() const noexcept -> unsigned int
{
    return static_cast<unsigned int>(scratch.GetMetadata().height);
}

auto Surface::GetBytePitch() const noexcept -> unsigned int
{
    return static_cast<unsigned int>(scratch.GetImage(0, 0, 0)->rowPitch);
}

auto Surface::GetBufferPtr() noexcept -> Color *
{
    return reinterpret_cast<Color *>(scratch.GetPixels());
}

auto Surface::GetBufferPtr() const noexcept -> const Color *
{
    return const_cast<Surface *>(this)->GetBufferPtr();
}

auto Surface::GetBufferPtrConst() const noexcept -> const Color *
{
    return const_cast<Surface *>(this)->GetBufferPtr();
}

auto Surface::LoadFromFile(const std::string &name) -> Surface
{
    DirectX::ScratchImage scratch;

    HRESULT hr = DirectX::LoadFromWICFile(ToWide(name).c_str(), DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, scratch);

    if (FAILED(hr))
    {
        throw Surface::InException(__LINE__, __FILE__, name, "Failed to load image", hr);
    }

    if (scratch.GetImage(0, 0, 0)->format != format)
    {
        DirectX::ScratchImage converted;
        hr = DirectX::Convert(
            *scratch.GetImage(0, 0, 0),
            format,
            DirectX::TEX_FILTER_DEFAULT,
            DirectX::TEX_THRESHOLD_DEFAULT,
            converted);

        if (FAILED(hr))
        {
            throw Surface::InException(__LINE__, __FILE__, name, "Failed to convert image", hr);
        }

        return Surface(std::move(converted));
    }

    return Surface(std::move(scratch));
}

void Surface::Save(const std::string &filename) const
{
    const auto GetCodecID = [](const std::string &filename) {
        const std::filesystem::path path = filename;
        const auto                  ext  = path.extension().string();
        if (ext == ".png")
        {
            return DirectX::WIC_CODEC_PNG;
        }
        else if (ext == ".jpg")
        {
            return DirectX::WIC_CODEC_JPEG;
        }
        else if (ext == ".bmp")
        {
            return DirectX::WIC_CODEC_BMP;
        }
        throw InException(__LINE__, __FILE__, filename, "Image format not supported");
    };

    HRESULT hr = DirectX::SaveToWICFile(
        *scratch.GetImage(0, 0, 0),
        DirectX::WIC_FLAGS_NONE,
        GetWICCodec(GetCodecID(filename)),
        ToWide(filename).c_str());
    if (FAILED(hr))
    {
        throw Surface::InException(__LINE__, __FILE__, filename, "Failed to save image", hr);
    }
}

auto Surface::AlphaLoaded() const noexcept -> bool
{
    return !scratch.IsAlphaAllOpaque();
}

Surface::InException::InException(int line, const char *file, std::string note, std::optional<HRESULT> hr) noexcept
    : Exception(line, file), note("[Note] " + note)
{
    if (hr)
    {
        note = "[Error String] " + WindowException::TranslateErrorCode(*hr) + "\n" + note;
    }
}

Surface::InException::InException(int line, const char *file, const std::string &filename, const std::string &note_in, std::optional<HRESULT> hr) noexcept
    : Exception(line, file)
{
    using namespace std::string_literals;
    note = "[File] "s + filename + "\n"s + "[Note] "s + note_in;

    if (hr)
    {
        note = "[Error String] " + WindowException::TranslateErrorCode(*hr) + note;
    }
}

auto Surface::InException::what() const noexcept -> const char *
{
    std::ostringstream oss;
    oss << Exception::what() << std::endl
        << GetNote();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

auto Surface::InException::GetType() const noexcept -> const char *
{
    return "Surface Exception";
}

auto Surface::InException::GetNote() const noexcept -> const std::string &
{
    return note;
}
