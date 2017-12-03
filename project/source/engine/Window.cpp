#include "Pch.h"
#include "Core.h"
#include "Window.h"

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define STRICT
#include <Windows.h>
#undef CreateWindow
#undef RegisterClass

Window::Window(const Int2& size, Mode mode) : size(size), mode(mode), title("Window")
{

}

Window::~Window()
{

}

void Window::Init()
{
	RegisterClass();
	AdjustSize();
	Create();
	Center();

	ShowWindow((HWND)hwnd, /*options.hidden_window ? SW_HIDE : */SW_SHOWNORMAL);

	
}

bool Window::Tick()
{
	MSG msg = { 0 };
	while(true)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_QUIT)
				return false;
		}
		else
			return true;
	}
}

void Window::RegisterClass()
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		[](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
		{
			if(msg == WM_NCCREATE)
			{
				CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
				Window* window = (Window*)cs->lpCreateParams;
				window->hwnd = hwnd;
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (IntPointer)cs->lpCreateParams);
			}
			else
			{
				Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
				if(window)
				{
					assert(hwnd == (HWND)window->hwnd);
					return window->HandleEvents(msg, wParam, lParam);
				}
			}
			return DefWindowProc(hwnd, msg, wParam, lParam);
		},
		0, 0, GetModuleHandle(nullptr), LoadIcon(GetModuleHandle(nullptr), "Icon"), LoadCursor(nullptr, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH),
		nullptr, "Krystal", nullptr
	};

	if(!RegisterClassEx(&wc))
		throw "Failed to register window class.";
}

void Window::Create()
{
	auto hwnd = CreateWindowEx(0, "Krystal", title.c_str(), (mode == Fullscreen) ? WS_POPUPWINDOW : WS_OVERLAPPEDWINDOW, 0, 0, real_size.x, real_size.y,
		nullptr, nullptr, GetModuleHandle(nullptr), this);
	if(!hwnd)
		throw "Failed to create window.";
	this->hwnd = hwnd;
}

IntPointer Window::HandleEvents(uint msg, UIntPointer lParam, IntPointer wParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc((HWND)hwnd, msg, lParam, wParam);
	}
}

void Window::SetTitle(cstring new_title)
{
	assert(new_title);
	if(hwnd)
		SetWindowText((HWND)hwnd, new_title);
	title = new_title;
}

void Window::AdjustSize()
{
	switch(mode)
	{
	case Windowed:
		{
			Rect rect = Rect::Create(Int2(0, 0), size);
			AdjustWindowRect((RECT*)&rect, WS_OVERLAPPEDWINDOW, false);
			real_size = rect.Size();
		}
		break;
	case FullscreenWindowed:
	case Fullscreen:
		real_size = size;
		break;
	}
}

void Window::Center()
{
	if(mode == Windowed)
	{
		MoveWindow((HWND)hwnd,
			(GetSystemMetrics(SM_CXSCREEN) - real_size.x) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - real_size.y) / 2,
			real_size.x, real_size.y, false);
	}
}
