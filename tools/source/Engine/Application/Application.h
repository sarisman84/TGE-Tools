#pragma once

#include <Windows.h>
#include <memory>

class GraphicsEngine;

class Application {
public:
	Application();
	~Application();

	void Run();

	virtual void BeginFrame();
	virtual void Render();
	virtual void EndFrame();

protected:
	std::shared_ptr<GraphicsEngine> myGraphicsEngine;
};