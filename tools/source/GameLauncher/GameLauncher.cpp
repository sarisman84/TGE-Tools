#include <Game.h>

#include <Engine.h>
#include <Application/ApplicationEntryPoint.h>

#include <memory>
#include <string>

class GameLauncher : public Application {
public:
	GameLauncher() : Application() {
		_game = std::unique_ptr<Game>(new Game(myGraphicsEngine->get_scene()));
	}

	~GameLauncher() {}

	void BeginFrame() {
		::Application::BeginFrame();
		_game->update();
	}

	void Render() {
		::Application::Render();
	}

	void EndFrame() {
		::Application::EndFrame();
	}

private:
	std::unique_ptr<Game> _game;
};

Application* CreateApplication() {
	return new GameLauncher();
}

LRESULT CALLBACK WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	static WindowHandler* windowHandler = nullptr;

	if (uMsg == WM_DESTROY || uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
	}
	else if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* createdStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		windowHandler = static_cast<WindowHandler*>(createdStruct->lpCreateParams);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}