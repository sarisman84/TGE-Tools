#include "ModelProperties.h"

#include <Engine.h>

#include <imgui.h>

#include <CommandManager.h>
#include <Commands/TransformCommand.h>
#include <Selection.h>

#include <filesystem>

ModelProperties::ModelProperties(std::vector<ModelInstance*> &aModelList) : myModelList(aModelList) {

}

void ModelProperties::Draw() {

	ImGui::Begin("Properties"); {
		ModelInstance* mi = Selection::GetSelection();
		if (mi != nullptr) {
			if (ImGui::CollapsingHeader(mi->GetModel()->GetPath(), ImGuiTreeNodeFlags_DefaultOpen)) {
				Transform t = mi->GetTransform();
				auto pos = t.GetPosition();

				if (ImGui::DragFloat3("Translation: ", pos.data(), 0.01f)) {
					mi->SetLocation(pos);
				}
				if (ImGui::IsItemActivated()) {
					myStartTransform.reset(new Transform(mi->GetTransform()));
				}
				else if (ImGui::IsItemDeactivatedAfterEdit()) {
					CommandManager::DoCommand(std::make_unique<TransformCommand>(mi, *myStartTransform.get(), mi->CopyTransform()));
				}

				ImGui::Image((ImTextureID)mi->GetModel()->GetModelData()->texture, ImVec2(32, 32));

				std::filesystem::path texture_path = Settings::paths["game_assets"] + "/Textures";
				
				if (ImGui::BeginCombo("##combo", "foobar")) {
					for (auto const& item : std::filesystem::directory_iterator(texture_path)) {
						std::string filename = item.path().filename().string();
						bool is_selected = (filename.c_str() == mi->GetModel()->GetPath());
						if (ImGui::Selectable(filename.c_str(), is_selected)) {
							mi->GetModel()->set_texture(item.path().filename().wstring(), Settings::paths["game_assets"]);
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
			}
		}		
	}
	ImGui::End();
}

