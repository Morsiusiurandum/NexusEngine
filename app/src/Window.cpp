#include "Window.h"

Window::Exception::Exception(int line, const char* file, HRESULT hResult) noexcept
	: NexusException(line, file), hResult(hResult)
{
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* message_buffer = nullptr;
	// windows will allocate memory for err string and make our pointer point to it
	const DWORD format_message_length = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		((message_buffer)), 0, nullptr);

	// 0 string length returned indicates a failure
	if (format_message_length == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string error_string = message_buffer;
	// free windows buffer
	LocalFree(message_buffer);
	return error_string;
}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code]" << GetErrorCode() << std::endl
		<< "[Description]" << GetErrorString() << std::endl;
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Nexus Windows Exception";
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hResult;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hResult);
}

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	: hInst(GetModuleHandle(nullptr))
{

	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = CHAR2LPCWSTR(GetName());
	wc.hIconSm = nullptr;
	//register a window
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(reinterpret_cast<LPCWSTR>(wndClassName), GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Window::Window(int width, int height, const WCHAR* name)
{
	RECT window_rect;
	window_rect.left = 100;
	window_rect.right = width + window_rect.left;
	window_rect.top = 100;
	window_rect.bottom = height + window_rect.top;
	DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
	if (FAILED(AdjustWindowRect(&window_rect, window_style, FALSE)))
	{
		throw NEXUS_LAST_EXCEPT();
	}

	//creat window and get the instance
	hWnd = CreateWindow(
		CHAR2LPCWSTR(WindowClass::GetName()),
		name,
		window_style, CW_USEDEFAULT, CW_USEDEFAULT,
		window_rect.right - window_rect.left, window_rect.bottom - window_rect.top,
		nullptr, nullptr,
		WindowClass::GetInstance(), this);

	if (hWnd == nullptr) throw NEXUS_LAST_EXCEPT();

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	//weather is in no-client
	if (msg == WM_NCCREATE)
	{
		const auto* const pCreate = reinterpret_cast<const CREATESTRUCT* const>(lParam);
		auto* const pWnd = static_cast<Window* const>(pCreate->lpCreateParams);

		//store the ptr in user data
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
		//use thunk to deal with messages
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&Window::HandleMsgThunk);
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	auto* const pWnd = reinterpret_cast<Window* const>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
