#pragma once

#include <memory>
#include <ToolsInterface/ToolsInterface.h>

struct Transform;
class Scene;

class Gizmos : public ToolsInterface {
public:
	Gizmos(Scene* aScene) : myScene(aScene) {}

	virtual void Draw() override;

private:
	const Scene* myScene;
	std::unique_ptr<Transform> myStartTransform;

	int myGizmoType = 7;
	float mySnap[3] = { 0.0f, 0.0f, 0.0f };
};
