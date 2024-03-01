#include "Exception.h"

Exception::Exception(int line, const char *file) noexcept
    : line(line), file(file)
{
}

auto Exception::what() const noexcept -> const char *
{
    std::ostringstream oss;
    oss << GetType() << std::endl
        << GetOriginString() << line;
    whatBuffer = oss.str();
    return (whatBuffer.c_str());
}

auto Exception::GetType() const noexcept -> const char *
{
    return "Nexus Exception";
}

auto Exception::GetLine() const noexcept -> int
{
    return line;
}

auto Exception::GetFile() const noexcept -> const std::string &
{
    return file;
}

auto Exception::GetOriginString() const noexcept -> std::string
{
    std::ostringstream oss;
    oss << "[File]" << file << std::endl
        << "[Line]" << line;
    return oss.str();
}
