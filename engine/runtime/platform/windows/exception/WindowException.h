#ifndef WINDOW_EXCEPTION_H
#define WINDOW_EXCEPTION_H


#include "Exception.h"
class WindowException : public Exception
{
public:
    WindowException(int line, const char *file, HRESULT hResult) noexcept;

    auto what() const noexcept -> const char * override;
    
    static auto TranslateErrorCode(HRESULT hResult) noexcept -> std::string;
private:
    auto GetType() const noexcept -> const char * override;

    auto GetErrorCode() const noexcept -> HRESULT;

    auto GetErrorString() const noexcept -> std::string;
    
private:
    HRESULT hr;
};


#endif //WINDOW_EXCEPTION_H
