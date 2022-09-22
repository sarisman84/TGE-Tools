#include <Game.h>

#include <Engine.h>
#include <Application/ApplicationEntryPoint.h>

#include <Tools/ExampleTool/ExampleTool.h>
#include <Tools/ModelProperties/ModelProperties.h>

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#include <filesystem>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ToolsLauncher : public Application {
public:
	ToolsLauncher() : Application()	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(myGraphicsEngine->get_window_handler()->GetWindowHandle());
		ImGui_ImplDX11_Init(myGraphicsEngine->get_framework()->GetDevice(), myGraphicsEngine->get_framework()->GetContext());

		DragAcceptFiles(myGraphicsEngine->get_window_handler()->GetWindowHandle(), TRUE);

		_game = std::unique_ptr<Game>(new Game(myGraphicsEngine->get_scene()));

		myExampleTool = std::unique_ptr<ExampleTool>(new ExampleTool(myGraphicsEngine));
		_model_properties = std::unique_ptr<ModelProperties>(new ModelProperties(myGraphicsEngine->get_scene()->get_model_list()));
	}
	~ToolsLauncher() {}

	void BeginFrame() {
		::Application::BeginFrame();
		_game->update();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void Render() {
		::Application::Render();

		myExampleTool->Draw();
		_model_properties->Draw();
		
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void EndFrame() {
		::Application::EndFrame();
	}

private:
	std::unique_ptr<ExampleTool> myExampleTool;
	std::unique_ptr<ModelProperties> _model_properties;
	std::unique_ptr<Game> _game;
};

Application* CreateApplication() {
	return new ToolsLauncher();
}

LRESULT CALLBACK WinProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

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
	else if (uMsg == WM_DROPFILES) {
		HDROP drop = (HDROP)wParam;
		UINT num_paths = DragQueryFileW(drop, 0xFFFFFFFF, 0, 512);

		wchar_t* filename = nullptr;
		UINT max_filename_len = 0;

		// @todo - uppgift 3 <U03-pt1-n01>:
		// Lägg märke till att vi använder Settings-namespacet för att hantera saker som pathes 
		// Jag skulle inte säga att Game-Assets hanteras jättebra just nu, men det är en rätt stabil struktur och helt ok början.
		// Värt att nämna är också användandet av std::filesystem::path
		// Jag rekommenderar att kolla in std::filesystem, det hjälper med allt från att luska ut paths till att kopiera filer!
		// Det är dock rätt nytt och C++17 krävs för att ha en full implementation.
		std::filesystem::path asset_dir = Settings::paths["game_assets"];
		asset_dir += "/Textures/";
		asset_dir.auto_format();

		for (UINT i = 0; i < num_paths; ++i) {
			UINT filename_len = DragQueryFileW(drop, i, nullptr, 512) + 1;
			if (filename_len > max_filename_len) {
				max_filename_len = filename_len;
				wchar_t *tmp = (wchar_t*)realloc(filename, max_filename_len * sizeof(*filename));
				if (tmp != nullptr) {
					filename = tmp;
				}
			}
			DragQueryFileW(drop, i, filename, filename_len);

			// @todo - uppgift 3: <U03-pt1-n02>
			// Jag hoppas att ni fått tillräckligt för att lista ut det här :) fråga mig om det känns som nått saknas.
			// Egentligen är det bara ett par saker här:
			//		1. vi behöver kontrollera om filen redan finns
			//			- Om den finns behöver det hanteras
			//				- Antingen kopierar vi den inte
			//				- Eller så behöver vi döpa om den, eller ta bort den gamla innan vi skriver den nya, för skriva över kan vara lite kinkigt!
			//		2. Om filen inte är en .dds så bör vi inte kopiera den (det finns andra assets vi kunde vara intresserad av såklart, men för uppgiften vill jag bara ha .dds)
			//		3. Om ovanstående krav uppfyllts så kan vi kopiera filen som vi droppade
			//
			//		Tips:
			//			1. Det mesta går att lösa med std::filesystem
			//			2. std::filesystem::path har massa utility-funktioner för att reda ut allt ni behöver, till och med filkopieringen! ^^
			//			3. Använd DEBUGGERN! sätt breakpoints och undersök vad som händer, vad som finns i värden. I enkelhet vill ni veta
			//				path till den/de droppade filen/erna. Sen vill ni tala om vart den skall kopieras till, så det är väldigt viktigt
			//				att kunna se vad variabler har för värden i sig.
			//
			//	Nu är det dags att lägga till koden som saknas här:
			//	DoStuff();

		}
		free(filename);
		DragFinish(drop);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}