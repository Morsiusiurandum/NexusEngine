/*
 * Copyright (c) Morsiusiurandum. 2023-2024. All rights reserved.
 *
 */

#include "App.h"
#include "platform/windows/Window.h"

#ifdef _WIN32

auto CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) -> int
{
    // start the program and catch the exception
    try
    {
        return App{}.Awake();
    }
    catch (const Exception &exception)
    {
        MessageBoxExW(nullptr, CStringW(exception.what()), CStringW(exception.GetType()), MB_OK | MB_ICONEXCLAMATION, 0);
    }
    catch (const std::exception &exception)
    {
        MessageBoxExA(nullptr, exception.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION, 0);
    }
    catch (...)
    {
        MessageBoxExA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION, 0);
    }

    return -1;
}
#else

auto main(int argc, char *argv[]) -> int
{
    printf_s("Unsupported platforms!");
}

#endif
