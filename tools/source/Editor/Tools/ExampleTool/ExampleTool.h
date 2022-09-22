#pragma once

#include <ToolsInterface/ToolsInterface.h>

#include <memory>
#include <functional>
#include <wtypes.h>

//#include <Engine.h>
class GraphicsEngine;

class ExampleTool : public ToolsInterface {
public:
	ExampleTool(std::shared_ptr<GraphicsEngine> aFramework);

	virtual void Draw();



private:
	std::shared_ptr<GraphicsEngine> myGraphicsEngine;

};