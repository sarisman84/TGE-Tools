#include "Game.h"

#include <Engine.h>

Game::Game(Scene *scene) : _scene(scene) {
	float x = 1.2f;
	for (int i = 0; i < 4; i++) {
		auto cube = _scene->create_model_instance("cube");
		cube->SetLocation({ (x * (i - 1.5f)), 3.5f, 0.0f });
	}
	for (int i = 0; i < 3; i++) {
		auto cube = _scene->create_model_instance("cube");
		cube->SetLocation({ (x * (i - 1.0f)), 2.3f, 0.0f });
	}
	for (int i = 0; i < 2; i++) {
		auto cube = _scene->create_model_instance("cube");
		cube->SetLocation({ (x * (i-0.5f)), x, 0.0f });
	}
	auto cube = _scene->create_model_instance("cube");
	cube->SetLocation({ 0, 0, 0.0f });
}

void Game::update() {
}