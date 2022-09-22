#include <stdafx.h>
#include "EngineSettings.h"

#include <fstream>
#include <json.h>

#include <unordered_map>

namespace Settings {	
	std::unordered_map<std::string, std::string> paths;
	Settings::WindowData window_data;
}

bool Settings::load_config_files() {
	load_engine_settings();
	load_window_data();
	return true;
}

void Settings::load_engine_settings(const char* path) {
	std::string engineSettingsPath = "../EngineSettings/engine-settings.json";
	std::ifstream engine_ifs(engineSettingsPath);

	std::string engineSettingsString(
		(std::istreambuf_iterator<char>(engine_ifs)),
		(std::istreambuf_iterator<char>())
	);
	engine_ifs.close();
	json::jobject engineSettings = json::jobject::parse(engineSettingsString);

	Settings::paths["engine_resources_path"] = engineSettings["engine_resources_path"].as_string();
	Settings::paths["engine_assets"] = Settings::paths["engine_resources_path"] + "/Assets";
	Settings::paths["shaders"] = Settings::paths["engine_assets"] + "/Shaders";
	
	Settings::paths["game_resources_path"] = engineSettings["game_resources_path"].as_string();
	Settings::paths["game_assets"] = Settings::paths["game_resources_path"] + "/Assets";

	Settings::paths["window_settings"] = engineSettings["engine_resources_path"].as_string() + engineSettings["window_settings"].as_string();
}

void Settings::load_window_data(const char *path) {
	std::ifstream windowSettings_ifs(Settings::paths["window_settings"]);

	std::string input(
		(std::istreambuf_iterator<char>(windowSettings_ifs)),
		(std::istreambuf_iterator<char>())
	);
	windowSettings_ifs.close();

	json::jobject result = json::jobject::parse(input);

	auto rect = result["rect"].as_object();
	
	Settings::window_data.h = rect["h"];
	Settings::window_data.w = rect["w"];
	Settings::window_data.x = rect["x"];
	Settings::window_data.y = rect["y"];

	auto color = result["clear_color"].as_object();
	Settings::window_data.clear_color[0] = color["r"];
	Settings::window_data.clear_color[1] = color["g"];
	Settings::window_data.clear_color[2] = color["b"];
	Settings::window_data.clear_color[3] = color["a"];

	std::string s = result["title"].as_string();
	//std::wstring stemp = std::wstring(s.begin(), s.end());
	Settings::window_data.title = s.c_str();
}