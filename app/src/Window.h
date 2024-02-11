#ifndef NEXUS_WINDOW_H
#define NEXUS_WINDOW_H

#pragma once

#include "IO/Keyboard.h"
#include "IO/Mouse.h"
#include "NexusException.h"
#include "NexusMacro.h"

class Window
{
 public:
	class Exception : public NexusException
	{
	 public:
		Exception(int line, const char* file, HRESULT hResult) noexcept;

		auto what() const noexcept -> const char* override;

		auto GetType() const noexcept -> const char* override;

		auto GetErrorCode() const noexcept -> HRESULT;

		auto GetErrorString() const noexcept -> std::string;

		static auto TranslateErrorCode(HRESULT hResult) noexcept -> std::string;

	 private:
		HRESULT hResult;
	};

 private:
	class WindowClass
	{
	 public:
		static auto GetName() noexcept -> const char*;

		static auto GetInstance() noexcept -> HINSTANCE;

		WindowClass(const WindowClass&) = delete;

		auto operator=(const WindowClass&) -> WindowClass& = delete;

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

	auto operator=(const Window&) -> Window& = delete;

 private:
	static auto CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

	static auto CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

	auto HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

 public:
	Keyboard keyboard;

	Mouse mouse;

 private:
	int width{}, height{};

	HWND hWnd;
};

//helper macro
#define NEXUS_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define NEXUS_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())

#endif//NEXUS_WINDOW_H
