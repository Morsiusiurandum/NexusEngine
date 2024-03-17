#ifndef NEXUS_WINDOW_H
#define NEXUS_WINDOW_H

#include <memory>

#include "NexusIO.h"
#include "NexusMacro.h"

#include "../Exception/WindowException.h"
#include "../Graphics.h"
#include "../Utils/Timer.h"

//helper macro
#define NEXUS_EXCEPT(hr) WindowException(__LINE__, __FILE__, hr)
#define NEXUS_LAST_EXCEPT() WindowException(__LINE__, __FILE__, GetLastError())

class Window
{
private:
    class WindowClass
    {
    public:
        static auto GetName() noexcept -> const WCHAR *;

        static auto GetInstance() noexcept -> HINSTANCE;

        WindowClass(const WindowClass &) = delete;

        auto operator=(const WindowClass &) -> WindowClass & = delete;

    private:
        WindowClass() noexcept;

        ~WindowClass();

        static constexpr const CHAR *wndClassName = "Nexus Direct3D Engine";

        static WindowClass wndClass;

        HINSTANCE hInst;
    };

public:
    Window(int width, int height, const WCHAR *name);

    ~Window();

    Window(const Window &) = delete;

    auto operator=(const Window &) -> Window & = delete;

    [[nodiscard]] auto ProcessMessage() noexcept -> std::optional<int>;

    [[nodiscard]] auto GetGraphics() const -> Graphics &;

private:
    [[nodiscard]] auto HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    static auto CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

    static auto CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

public:
    Keyboard keyboard;

    Mouse mouse;

private:
    int width{}, height{};

    HWND h_wnd;

    std::unique_ptr<Graphics> graphics_ptr;
};

#endif //NEXUS_WINDOW_H
