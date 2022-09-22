#include "Gizmos.h"

#include <imgui.h>
#include <ImGuizmo.h>

#include <Engine.h>
#include <GraphicsEngine/Camera/Camera.h>

#include <CommandManager.h>
#include <TransformCommand.h>
#include <Selection.h>


void Gizmos::Draw() {
    ImGui::Begin("gizmos"); {
        if (ImGui::Button("t") || ImGui::IsKeyPressed('Q')) {
            myGizmoType = ImGuizmo::OPERATION::TRANSLATE;
        }
        ImGui::SameLine();
        if (ImGui::Button("r") || ImGui::IsKeyPressed('W')) {
            myGizmoType = ImGuizmo::OPERATION::ROTATE;
        }
        ImGui::SameLine();
        if (ImGui::Button("s") || ImGui::IsKeyPressed('E')) {
            myGizmoType = ImGuizmo::OPERATION::SCALE;
        }
        ImGui::SameLine();
        if (ImGui::Button("Deselect") || ImGui::IsKeyPressed(27)) {
            myGizmoType = -1;
        }
        float v = mySnap[0];
        if (ImGui::SliderFloat("Snapping", &v, 0.0f, 5.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp)) {
            mySnap[0] = mySnap[1] = mySnap[2] = v;
        }
    } ImGui::End();

    ModelInstance* mi = Selection::GetSelection();
    if (mi != nullptr && myGizmoType != -1) {
        ImGui::SetItemDefaultFocus();

        auto io = ImGui::GetIO();
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

            ImGuizmo::SetRect(0.0f, 0.0f, static_cast<float>(Settings::window_data.w), static_cast<float>(Settings::window_data.h));

            const Camera* camera = myScene->active_camera();
            Matrix4x4f& view = Matrix4x4f::GetFastInverse(camera->GetTransform().GetMatrix());
            Matrix4x4f& proj = camera->get_projection();

            // get instance transform
            Matrix4x4f& transform = Matrix4x4f::Inverse(mi->GetTransform().GetMatrix());

            ImGuizmo::Manipulate(
                view.GetDataPtr(),
                proj.GetDataPtr(),
                (ImGuizmo::OPERATION)myGizmoType,
                ImGuizmo::LOCAL,
                transform.GetDataPtr(), nullptr,
                mySnap
            );
            static bool in_use = false;
            if (ImGuizmo::IsOver() && io.MouseClicked[0]) {
                myStartTransform.reset(new Transform(mi->GetTransform()));
                in_use = true;
            }
            if (in_use == true && io.MouseReleased[0]) {
                in_use = false;
                CommandManager::DoCommand(std::make_unique<TransformCommand>(mi, *myStartTransform.get(), mi->CopyTransform()));
                myStartTransform.release();
            }

            if (ImGuizmo::IsUsing()) {

                Vector3f pos, rot, scale;
                transform.DecomposeMatrix(pos, rot, scale);

                mi->SetRotation(rot);
                mi->SetLocation(pos);
                mi->SetScale(scale);
            }
        }
    }
}