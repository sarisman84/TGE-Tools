#pragma once

#include <memory>
#include <array>

#include <Scene/Scene.h>

class DX11Framework;
class ForwardRenderer;
class WindowHandler;

class GraphicsEngine {	
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool init();
	Scene *get_scene() { return &_scene; }

	void begin_frame();
	void end_frame();
	void render_frame();

	__forceinline std::shared_ptr<WindowHandler> get_window_handler() const { return _window_handler; }
	__forceinline std::shared_ptr<DX11Framework> get_framework() { return _framework; }

	//__forceinline std::array<float, 4> get_clear_color() const { return _clear_color; }
	//void set_clear_color(std::array<float, 4>& color) { _clear_color = std::move(color); }

private:
	std::shared_ptr<WindowHandler> _window_handler;
	std::shared_ptr<DX11Framework> _framework;
	std::shared_ptr<ForwardRenderer> _forward_renderer;
	
	Scene _scene;
};

