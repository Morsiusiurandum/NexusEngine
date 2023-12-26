#ifndef NEXUS_WINDOW_H
#define NEXUS_WINDOW_H

#pragma once

#include "NexusMacro.h"


class Window {
private:
    class WindowClass {
    public:
        static const char *GetName() noexcept;

        static HINSTANCE GetInstance() noexcept;

        WindowClass(const WindowClass &) = delete;

        WindowClass &operator=(const WindowClass &) = delete;

    private:
        WindowClass() noexcept;

        ~WindowClass();

        static constexpr const char *wndClassName = "Nexus Direct3D Engine";

        static WindowClass wndClass;

        HINSTANCE hInst;
    };

public:
    Window(int width, int height, const WCHAR *name) noexcept;

    ~Window();

    Window(const Window &) = delete;

    Window &operator=(const Window &) = delete;

private:
    static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    int width{}, height{};
    HWND hWnd;
};

#endif //NEXUS_WINDOW_H
