#ifndef NEXUS_WINDOW_H
#define NEXUS_WINDOW_H

#pragma once

#include "Keyboard.h"
#include "NexusException.h"
#include "NexusMacro.h"

class Window
{
 public:
	class Exception : public NexusException
	{
	 public:
		Exception(int line, const char* file, HRESULT hResult) noexcept;

		const char* what() const noexcept override;

		const char* GetType() const noexcept override;

		static std::string TranslateErrorCode(HRESULT hResult) noexcept;

		HRESULT GetErrorCode() const noexcept;

		std::string GetErrorString() const noexcept;

	 private:
		HRESULT hResult;
	};

 private:
	class WindowClass
	{
	 public:
		static const char* GetName() noexcept;

		static HINSTANCE GetInstance() noexcept;

		WindowClass(const WindowClass&) = delete;

		WindowClass& operator=(const WindowClass&) = delete;

	 private:
		WindowClass() noexcept;

		~WindowClass();

		static constexpr const char* wndClassName = "Nexus Direct3D Engine";

		static WindowClass wndClass;

		HINSTANCE hInst;
	};

 public:
	Window(int width, int height, const WCHAR* name);

	~Window();

	Window(const Window&) = delete;

	Window& operator=(const Window&) = delete;

 private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

 public:
	Keyboard keyboard;

 private:
	int width{}, height{};

	HWND hWnd;
};

//helper macro
#define NEXUS_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define NEXUS_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())

#endif//NEXUS_WINDOW_H
