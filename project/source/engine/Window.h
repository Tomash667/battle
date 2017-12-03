#pragma once

typedef void* Handle;

class Window
{
public:
	enum Mode
	{
		Windowed,
		FullscreenWindowed,
		Fullscreen
	};

	typedef void* Handle;

	Window(const Int2& size = Int2(1024, 768), Mode mode = Windowed);
	~Window();

	void Init();
	bool Tick();

	Handle GetHandle() { return hwnd; }

	void SetTitle(cstring title);

private:
	void RegisterClass();
	void AdjustSize();
	void Create();
	void Center();
	IntPointer HandleEvents(uint msg, UIntPointer lParam, IntPointer wParam);

	string title;
	Mode mode;
	Int2 size, real_size;
	Handle hwnd;
};
