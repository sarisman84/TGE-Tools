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



/*
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





	if (ImGui::Selectable(id.c_str(), is_selected))
	{
		CommandManager::DoCommand(std::make_unique<SelectionCommand>(anInstance));
	}
*/


//std::vector<SceneElement> ConstructElements(const Scene* aScene)
//{
//	std::vector<SceneElement> result;
//	auto instances = &aScene->SceneModels();
//	for (size_t i = 0; i < instances->size(); i++)
//	{
//		
//
//		result.emplace_back(i, id, instances);
//	}
//
//	return result;
//}

void InspectElement(const int anIndex, std::vector<ModelInstance*> someInstances)
{
	auto element = someInstances[anIndex];
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		ImGui::SetDragDropPayload("Transform", &anIndex, sizeof(int));


		ImGui::EndDragDropSource();
	}

	const bool is_selected = (Selection::GetSelection() == element);
	if (ImGui::Selectable(element->GetID().c_str(), is_selected))
	{
		CommandManager::DoCommand(std::make_unique<SelectionCommand>(element));
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* load = ImGui::AcceptDragDropPayload("Transform"))
		{
			IM_ASSERT(load->DataSize == sizeof(int));
			int dragN = *(const int*)load->Data;

			dragN = Math::Clamp(dragN - 1, 0, static_cast<int>(someInstances.size() - 1));
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
