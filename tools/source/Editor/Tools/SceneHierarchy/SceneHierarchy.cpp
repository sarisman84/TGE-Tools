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





void InspectElement(const int anIndex, std::vector<ModelInstance*> someInstances)
{
	auto element = someInstances[anIndex];


	const bool is_selected = (Selection::GetSelection() == element);
	if (ImGui::Selectable(element->GetID().c_str(), is_selected))
	{
		CommandManager::DoCommand(std::make_unique<SelectionCommand>(element));
	}

	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		ImGui::SetDragDropPayload("PARENT", &anIndex, sizeof(int));


		ImGui::EndDragDropSource();
	}


	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* load = ImGui::AcceptDragDropPayload("PARENT"))
		{
			IM_ASSERT(load->DataSize == sizeof(int));
			int dragN = *(const int*)load->Data;

			//dragN = Math::Clamp(dragN - 1, 0, static_cast<int>(someInstances.size() - 1));
			ModelInstance* child = someInstances[dragN];

			child->SetParent(element);


		}

		ImGui::EndDragDropTarget();

	}

	auto children = element->GetChildren();
	for (auto& child : children)
	{
		auto it  = std::find(someInstances.begin(), someInstances.end(), child);
		if (it == someInstances.end()) continue;

		ImGui::Indent();
		InspectElement(it - someInstances.begin(), someInstances);
		ImGui::Unindent();
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



				for (int n = 0; n < instances.size(); n++)
				{
					auto element = instances[n];

					if (element->GetParent()) continue;

					


					InspectElement(n, instances);

					


					
					

				}
				ImGui::EndListBox();
			} ImGui::End();
		}
	}
}
