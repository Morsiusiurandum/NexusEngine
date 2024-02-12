#include "App.h"

App::App()
	: window_(800, 600, CHAR2LPCWSTR("Start Window"))
{
}

auto App::Awake() -> int
{
	MSG msg;
	BOOL msgResult;
	while ((msgResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		Update();
	}

	if (msgResult == -1)
	{
		throw NEXUS_LAST_EXCEPT();
	}

	return static_cast<int>(msg.wParam);
}

void App::Update()
{
	if (window_.keyboard.KeyIsPressed(VK_MENU))
	{
		MessageBoxA(nullptr, "Hello World!", "Alt was pressed!", MB_OK);
	}
}