#pragma once
#include <Windows.h>
#include <Core/EngineSettings.h>

extern LRESULT CALLBACK WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

class WindowHandler
{
public:
	WindowHandler();
	virtual ~WindowHandler();

	bool Init(Settings::WindowData someWindowData);

	FORCEINLINE HWND GetWindowHandle()
	{
		return myWindowHandle;
	}
	FORCEINLINE float GetWidth()
	{
		return myWidth;
	}
	FORCEINLINE float GetHeight()
	{
		return myHeight;
	}

private:
	HWND myWindowHandle;
	float myWidth;
	float myHeight;
};

