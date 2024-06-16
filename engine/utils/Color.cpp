#include "Color.h"

auto Color::operator=(Color color) noexcept -> Color &
{
    dword = color.dword;
    return *this;
}

constexpr auto Color::GetR() const noexcept -> unsigned char
{
    return (dword >> 16u) & 0xFFu;
}

constexpr auto Color::GetG() const noexcept -> unsigned char
{
    return (dword >> 8u) & 0xFFu;
}

constexpr auto Color::GetB() const noexcept -> unsigned char
{
    return dword & 0xFFu;
}

constexpr auto Color::GetA() const noexcept -> unsigned char
{
    return dword >> 24u;
}

constexpr Color::Color(unsigned int dw) noexcept
    : dword(dw)
{
}
constexpr Color::Color(unsigned char x, unsigned char r, unsigned char g, unsigned char b) noexcept
    : dword((x << 24u) | (r << 16u) | (g << 8u) | b)
{
}

constexpr Color::Color(unsigned char r, unsigned char g, unsigned char b) noexcept
    : dword((255u << 24u) | (r << 16u) | (g << 8u) | b)
{
}

constexpr Color::Color(Color col, unsigned char x) noexcept
    : Color((x << 24u) | col.dword)
{
}

void Color::SetX(unsigned char x) noexcept
{
    dword = (dword & 0xFFFFFFu) | (x << 24u);
}

void Color::SetA(unsigned char a) noexcept
{
    SetX(a);
}

void Color::SetR(unsigned char r) noexcept
{
    dword = (dword & 0xFF00FFFFU) | (r << 16U);
}

void Color::SetG(unsigned char g) noexcept
{
    dword = (dword & 0xFFFF00FFU) | (g << 8U);
}

void Color::SetB(unsigned char b) noexcept
{
    dword = (dword & 0xFFFFFF00U) | b;
}
