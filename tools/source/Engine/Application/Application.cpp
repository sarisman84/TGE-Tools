#include <stdafx.h>

#include "Application.h"
#include "GraphicsEngine/GraphicsEngine.h"

#include <Windows.h>


Application::Application() 
{
	myGraphicsEngine = std::shared_ptr<GraphicsEngine>(new GraphicsEngine());
	myGraphicsEngine->init();
}
Application::~Application() {}

void Application::BeginFrame() {
	myGraphicsEngine->begin_frame();
}

void Application::Render() {
	myGraphicsEngine->render_frame();
}

void Application::EndFrame() {
	myGraphicsEngine->end_frame();
}

void Application::Run() 
{
	bool bShouldRun = true;
	while (bShouldRun)
	{	
		MSG msg = { 0 };

		while (bShouldRun)
		{
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
				{
					bShouldRun = false;
				}
			}

			BeginFrame();
			Render();
			EndFrame();
		}
	}
}