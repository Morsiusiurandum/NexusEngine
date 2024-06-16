#ifndef NEXUS_EXCEPTION_H
#define NEXUS_EXCEPTION_H

#include "NexusMacro.h"
#include <atlstr.h>
#include <exception>
#include <sstream>
#include <string>

class Exception : public std::exception
{
public:
    Exception(int line, const char *file) noexcept;

    auto what() const noexcept -> const char * override;
    
    auto GetLine() const noexcept -> int;

    auto GetFile() const noexcept -> const std::string &;

    auto GetOriginString() const noexcept -> std::string;

    virtual auto GetType() const noexcept -> const char *;

private:
    int line;

    std::string file;

protected:
    mutable std::string whatBuffer;
};

#endif //NEXUS_EXCEPTION_H
