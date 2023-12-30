#include "Window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	try
	{
		Window wnd(800, 300, CHAR2LPCWSTR("WTF?"));

		MSG msg;
		BOOL msgResult;
		while ((msgResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msgResult == -1 ? -1 : (int)msg.wParam;
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
}