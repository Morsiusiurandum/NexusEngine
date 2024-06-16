#ifndef GRAPHICS_EXCEPTION_H
#define GRAPHICS_EXCEPTION_H

#include "Exception.h"

class GraphicsException : public Exception
{
public:
    GraphicsException(int line, const char *file, HRESULT hResult) noexcept;

    auto what() const noexcept -> const char * override;

private:
    auto GetType() const noexcept -> const char * override;

    auto GetErrorCode() const noexcept -> HRESULT;

    auto GetErrorString() const noexcept -> std::string;

    static auto TranslateErrorCode(HRESULT hResult) noexcept -> std::string;

private:
    HRESULT hr;
};


#endif //GRAPHICS_EXCEPTION_H
