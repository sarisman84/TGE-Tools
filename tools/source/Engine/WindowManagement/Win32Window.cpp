#include <stdafx.h>

#include "Win32Window.h"
#include <Application.h>

bool WindowHandler::Init(Settings::WindowData someWindowData)
{
	myWidth = static_cast<float> (someWindowData.w);
	myHeight = static_cast<float> (someWindowData.h);

	WNDCLASS windowClass = {};
	windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = WinProc;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = L"tools";
	RegisterClass(&windowClass);

	std::string s = Settings::window_data.title;
	std::wstring stemp = std::wstring(s.begin(), s.end());
	
	myWindowHandle = CreateWindow(
		L"tools",
		stemp.c_str(),
		WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE,
		someWindowData.x,
		someWindowData.y,
		someWindowData.w,
		someWindowData.h,
		nullptr, nullptr, nullptr,
		this
	);

	return true;
}

WindowHandler::WindowHandler()
{
	myWindowHandle = nullptr;
	myWidth = 0;
	myHeight = 0;
}

WindowHandler::~WindowHandler()
{
	myWindowHandle = nullptr;
	myWidth = 0;
	myHeight = 0;
}
