#include <Game.h>

#include <Engine.h>
#include <Application/ApplicationEntryPoint.h>
//#include <GraphicsEngine/Camera/Camera.h>

#include <Tools/ExampleTool/ExampleTool.h>
#include <Tools/SceneHierarchy/SceneHierarchy.h>
#include <Tools/ModelProperties/ModelProperties.h>
#include <Tools/Gizmos/Gizmos.h>

#include <CommandManager.h>

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#include <ImGuizmo.h>

#include <filesystem>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ToolsLauncher : public Application {
public:
	ToolsLauncher() 
		: Application()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(myGraphicsEngine->get_window_handler()->GetWindowHandle());
		ImGui_ImplDX11_Init(myGraphicsEngine->get_framework()->GetDevice(), myGraphicsEngine->get_framework()->GetContext());

		DragAcceptFiles(myGraphicsEngine->get_window_handler()->GetWindowHandle(), TRUE);

		myGame.reset(new Game(myGraphicsEngine->get_scene()));

		myTools.push_back(local<ExampleTool>(new ExampleTool(myGraphicsEngine)));
		myTools.push_back(local<ModelProperties>(new ModelProperties(myGraphicsEngine->get_scene()->get_model_list())));
		myTools.push_back(local<ScenenHierarchy>(new ScenenHierarchy(myGraphicsEngine->get_scene())));
		myTools.push_back(local<Gizmos>(new Gizmos(myGraphicsEngine->get_scene())));
	}
	~ToolsLauncher() {}

	void BeginFrame() {
		::Application::BeginFrame();
		myGame->update();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

		ImGui::BeginGroup(); {
			if (ImGui::Button("Undo") || (ImGui::GetIO().KeyShift == false && ImGui::IsKeyPressed('Z') && ImGui::GetIO().KeyCtrl)) {
				CommandManager::Undo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Redo") || (ImGui::IsKeyPressed('Z') && ImGui::GetIO().KeyCtrl) && ImGui::GetIO().KeyShift) {
				CommandManager::Redo();
			}
		}
		ImGui::EndGroup();
	}

	void Render() {
		::Application::Render();

		for (const auto& tool : myTools) {
			tool->Draw();
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void EndFrame() {
		ImGui::EndFrame();
		::Application::EndFrame();
	}

private:
	std::vector<local<ToolsInterface>> myTools;
	local<Game> myGame;
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

		std::filesystem::path asset_dir = Settings::paths["game_assets"];
		asset_dir += "/Textures/";

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
			std::filesystem::path from_path = filename;
			std::filesystem::path to_path = asset_dir.concat(from_path.filename().string());

			if (std::filesystem::exists(to_path) == false && to_path.filename().extension() == ".dds") {
				std::filesystem::copy_file(from_path, to_path);
			}
		}
		free(filename);
		DragFinish(drop);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}