#pragma once
#include "SceneHierarchy.h"

#include <Engine.h>

#include <imgui.h>
#include <ImGuizmo.h>

#include "Selection.h"

#include <CommandManager.h>
#include "TransformCommand.h"
#include "SelectionCommand.h"

void ScenenHierarchy::Draw() {
    {
        ImGui::Begin("Scene List"); {
            if (ImGui::BeginListBox("", ImGui::GetContentRegionAvail())) {
                auto instances = myScene->SceneModels();
                if (Selection::GetSelection() == nullptr) {
                    Selection::SetSelection(instances[0]);
                }

                for (int n = 0; n < instances.size(); n++) {
                    ModelInstance* mi = instances[n];

                    const bool is_selected = (Selection::GetSelection() == mi);
                    std::string id = mi->GetModel()->GetPath();
                    id += "_" + std::to_string(n);
                    if (ImGui::Selectable(id.c_str(), is_selected)) {
                        CommandManager::DoCommand(std::make_unique<SelectionCommand>(mi));
                    }
                }
                ImGui::EndListBox();
            } ImGui::End();
        }
    }
}
