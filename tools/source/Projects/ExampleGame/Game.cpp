#include "Game.h"

#include <Engine.h>

Game::Game(Scene *scene) : _scene(scene) {
	auto cube1 = _scene->create_model_instance("cube");
	auto cube2 = _scene->create_model_instance("cube");

	cube1->SetLocation({ 1.0f, 1.0f, 0.0f });
}

void Game::update() {
}