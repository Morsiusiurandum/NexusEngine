#include "GraphicsException.h"
GraphicsException::GraphicsException(int line, const char *file, HRESULT hResult) noexcept
    : Exception(line, file), hr(hResult)
{
}

auto GraphicsException::what() const noexcept -> const char *
{
    std::ostringstream oss;
    oss << (GetType()) << std::endl
        << "[Error Code]" << GetErrorCode() << std::endl
        << "[Description]" << GetErrorString() << std::endl;
    whatBuffer = oss.str();
    return (whatBuffer.c_str());
}

auto GraphicsException::GetType() const noexcept -> const char *
{
    return "Nexus Graphics Exception";
}

auto GraphicsException::GetErrorCode() const noexcept -> HRESULT
{
    return hr;
}

auto GraphicsException::GetErrorString() const noexcept -> std::string
{
    return TranslateErrorCode(hr);
}

auto GraphicsException::TranslateErrorCode(HRESULT hResult) noexcept -> std::string
{
    WCHAR message_buffer[300];
    // windows will allocate memory for err string and make our pointer point to it
    const DWORD format_message_length = FormatMessageW(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        hResult,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (message_buffer),
        256,
        nullptr);

    // 0 string length returned indicates a failure
    if (format_message_length == 0)
    {
        return "Unidentified error code";
    }

    // copy error string from windows-allocated buffer to std::string
    std::string error_string = static_cast<const char *const>(CStringA(message_buffer));
    return error_string;
}
