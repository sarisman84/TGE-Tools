#include <stdafx.h>
#include "GraphicsEngine.h"
#include <DX11Framework.h>
#include <ForwardRenderer.h>
#include <Win32Window.h>

#include <json.h>

#include <vector>
#include <fstream>

GraphicsEngine::GraphicsEngine() {
	_forward_renderer	= std::shared_ptr<ForwardRenderer>(new ForwardRenderer());
	_framework			= std::shared_ptr<DX11Framework>(new DX11Framework());
	_window_handler		= std::shared_ptr<WindowHandler>(new WindowHandler());
}

//void GraphicsEngine::add_model(const char* model_path) {
//	_scene.AddModel(&_model_factory->create_instance(model_path));
//}

GraphicsEngine::~GraphicsEngine() {
}

bool GraphicsEngine::init() {
	
	if(!_window_handler->Init(Settings::window_data))
	{
		return false;
	}

	if(!_framework->Init(_window_handler))
	{
		return false;
	}

	if(!_forward_renderer->Init())
	{
		return false;
	}

	return true;
}

void GraphicsEngine::begin_frame() {	
	_framework->BeginFrame(Settings::window_data.clear_color);
}

void GraphicsEngine::end_frame() {
	_framework->EndFrame();
}

void GraphicsEngine::render_frame() {
	_forward_renderer->Render(_scene.active_camera(), _scene.CullModels());
}
