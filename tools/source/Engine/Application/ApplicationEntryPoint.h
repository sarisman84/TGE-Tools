#pragma once
#include <Core/EngineSettings.h>

extern Application* CreateApplication();

//#ifdef PLATFORM_WINDOWS
#include <Windows.h>

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, char*, int /*nShowCmd*/) {
	Settings::load_config_files();
	auto app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}

//#endif // PLATFORM_WINDOWS
