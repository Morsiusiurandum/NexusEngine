#include "App.h"
#include "Window.h"

auto CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) -> int
{

    // start the program and catch the exception
	try
	{
		return App{}.Update();
	}
	catch (const NexusException& exception)
	{
		MessageBoxA(nullptr, exception.what(), exception.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& exception)
	{
		MessageBoxA(nullptr, exception.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}