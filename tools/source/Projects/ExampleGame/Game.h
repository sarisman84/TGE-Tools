#pragma once

class Scene;

class Game {
public:
	Game(Scene *scene);

	void update();
	Scene* scene() { return _scene; }

private:
	Scene* _scene;
};