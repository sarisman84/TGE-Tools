#pragma once
#include "SceneHierarchy.h"

#include <Engine.h>

#include <imgui.h>
#include <ImGuizmo.h>

#include "Selection.h"

#include <CommandManager.h>
#include "TransformCommand.h"
#include "SelectionCommand.h"
#include <assert.h>


void InspectModel(
	std::vector<ModelInstance*> someModels,
	ModelInstance* anInstance,
	const int anIndex,
	std::string someExtraData = std::string()
)
{
	assert(anInstance != nullptr && "Missing model instance!");


	const bool is_selected = (Selection::GetSelection() == anInstance);
	std::string id = anInstance->GetModel()->GetPath();
	id += "_" + std::to_string(anIndex);
	if (!someExtraData.empty())
		id += someExtraData;

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* load = ImGui::AcceptDragDropPayload("Transform"))
		{
			IM_ASSERT(load->DataSize == sizeof(int));
			int dragN = *(const int*)load->Data;


			ModelInstance* child = someModels[dragN];

			anInstance->GetTransform().AddChild(&child->GetTransform());

			//someModels.erase(std::remove(someModels.begin(), someModels.end(), child), someModels.end());

		}

		ImGui::EndDragDropTarget();
	}

	if (anInstance->GetTransform().GetChildren().size() > 0)
	{
		int childIndex = 0;
		for (auto& child : anInstance->GetTransform().GetChildren())
		{
			auto ins = child->GetOwner<ModelInstance>();
			ImGui::Indent();
			InspectModel(someModels, ins, ins->GetSceneIndex(), "[C: " + std::to_string(childIndex) + "]");
			ImGui::Unindent();
		}
		return;
	}
	




	if (anInstance->GetTransform().HasParent()) return;
	if (ImGui::Selectable(id.c_str(), is_selected))
	{
		CommandManager::DoCommand(std::make_unique<SelectionCommand>(anInstance));
	}
	

	



}

void ScenenHierarchy::Draw() {
	{
		ImGui::Begin("Scene List");
		{
			if (ImGui::BeginListBox("", ImGui::GetContentRegionAvail()))
			{
				auto instances = myScene->SceneModels();
				if (Selection::GetSelection() == nullptr)
				{
					Selection::SetSelection(instances[0]);
				}

				auto cpy = instances;
				for (int n = 0; n < cpy.size(); n++)
				{
					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
					{
						ImGui::SetDragDropPayload("Transform", &n, sizeof(int));


						ImGui::EndDragDropSource();
					}


					ModelInstance* mi = cpy[n];

					InspectModel(cpy, mi, n);





				}
				ImGui::EndListBox();
			} ImGui::End();
		}
	}
}
