#pragma once

#include <memory>
#include <ToolsInterface/ToolsInterface.h>

class Scene;
struct Transform;




class ScenenHierarchy : public ToolsInterface
{
public:
	ScenenHierarchy(Scene* aScene) : myScene(aScene) {}

	virtual void Draw() override;

private:
	const Scene* myScene;
	std::unique_ptr<Transform> myStartTransform;
};
