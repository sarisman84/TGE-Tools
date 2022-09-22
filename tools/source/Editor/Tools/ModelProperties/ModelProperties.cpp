#include "ModelProperties.h"

#include <filesystem>

#include <Engine.h>

#include <imgui.h>
#include <Math/Vector3.h>
#include <Models/ModelInstance.h>
#include <Models/Model.h>

#include <CommandManager.h>
#include <Commands/PositionCommand.h>

ModelProperties::ModelProperties(std::vector<ModelInstance*> &model_list) : _model_list(model_list) {

}

void ModelProperties::Draw() {

	// @todo - uppgift3 <U03-pt2-n01>
	// H�r h�nder en hel massa!
	// Men vi s�tter upp ett ImGui-f�nster, i det l�gger vi en undo-knapp och en redo-knapp. Allt de g�r �r att s�ga �t CommandManager att utf�ra.
	// Sen s�tter vi upp inst�llningar f�r varje ModelInstance i scenen. Vi loopar helt enkelt igenom dem och s�tter upp tv� inst�llningsbara v�rden
	//		Location:
	//			Vi kan �ndra v�rden och se uppdateringen "live", men l�gg m�rke till att inget kommando skapas innan vi avslutat editeringen.
	//			Det �r f�r att annars s� skapas kommandon f�r ALL uppdatering, och det g�r undo/redo r�tt oanv�ndbar. S� vi genomf�r bara kommandot n�r 
	//			vi �ndrat f�rdigt.
	//		Texture:
	//			Den h�r �r inte skriven alls, och det beh�ver ni g�ra :)
	//			Interface finns redan, och implementationen kommer vara v�ldigt lik "PositionCommand", l�t oss kalla den "TextureCommand"
	//			S� ni kommer beh�va skapa filer f�r "TextureCommand", (personligen tycker jag om att l�gga till filer utanf�r VS, men det b�r g� �ven i VS s�
	//			s� l�nge ni ser till att filerna hamnar i r�tt mappar. F�r jag har struktur �ven p� filsystemet och inte bara allt i en mapp och filter, f�r jag
	//			vill att ni skall se en struktur som �r n�got mer robust �n vad VS erbjuder "out of the box").
	//			Anyhow.. Jag tror inte det skall vara f�r sv�rt att f� till kommandot, 
	//			OBS!! lite oavsett hur ni l�gger till filerna rekommenderar jag att genererar om projekten, det kan ni g�ra n�stan hur ofta ni vill!
	//				Men att g�ra det n�r man �ndrat n�tt i projektet (lagt till filer till exempel) �r f�rmodligen inte fel :)
	//
	//		Sammanfattning:
	//			Ni beh�ver implementera det som saknas f�r Location, tomma implementationer finns redan, och ni b�r till och med f� kommandon redan (som inte g�r n�tt)
	//			Ni beh�ver implementera hela TextureCommand sj�lva, men fr�ga om det beh�vs!

	ImGui::Begin("Models"); {
		// @todo: <info> CommandManager h�ller koll p� alla kommandon som utf�rs! Den �r statisk s� v�ldigt smidig att anv�nda, och kommer att g� att anv�nda �ven i andra
		// verktyg. Funktionalliteten i Undo() och Redo() beh�ver ni implementera, titta i CommandManager.cpp s� st�r det mer d�r :)
		if (ImGui::Button("Undo")) {
			CommandManager::Undo();
		}
		else if (ImGui::Button("Redo")) {
			CommandManager::Redo();
		}

		for (int i=0; i<_model_list.size(); i++) {
			ImGui::PushID(i);
			std::string s = "object_" + std::to_string(i);
			if (ImGui::CollapsingHeader(s.c_str())) {
				ModelInstance* mi = _model_list[i];
				Transform t = mi->GetTransform();
				auto pos = t.GetPosition();
				std::string label = i + "Translation: ";

				if (ImGui::DragFloat3("Translation: ", pos.data(), 0.01f)) {
					mi->SetLocation(pos);
				}
				if (ImGui::IsItemActivated()) {
					// @todo: <info> Om vi precis b�rjat editera den h�r framen, s� vill vi komma ih�g vart vi var, det �r f�r att det �r d�r vi kommer vara
					// innan vi utf�rde v�rt kommando, vi vill inte g�ra kommandon f�r varje uppdatering, d� blir det mycket sm� steg i v�r undo/redo!
					_start_position = mi->GetTransform().GetPosition();
				} else if (ImGui::IsItemDeactivatedAfterEdit()) {
					// @todo: <info> 
					//		N�r vi slutat editera (just den h�r kontrollen kan vi dra i, s� n�r vi inte l�ngre drar i den...)
					//		Ja d� �r det l�ge att skicka v�rt kommando. Den observante l�saren ser att h�r l�cker jag minne!
					//		Hur kunde jag enkelt l�st det? Fundera s� svarar jag lite senare ;)
					CommandManager::DoCommand(new PositionCommand(mi, _start_position, pos));
				}

				// @todo: <info>
				//		H�r h�nder det en del, f�rst och fr�mst, s� h�mtar vi ut aktiv textur fr�n modellen, och bara ritar ut den i interfacet
				//		Mer kul �n anv�ndbart, men det finns en hel del vi kan g�ra med det.
				ImGui::Image((ImTextureID)mi->GetModel()->GetModelData()->texture, ImVec2(32, 32));
				
				// @todo: <info>
				//		Sen plockar vi ut v�r game_assets path och itererar �ver alla filer (vilket b�r vara bara .dds).
				//		Jag kontrollerar inte h�r om det �r .ddser, men att g�ra det b�r vara enkelt med hj�lp av std::filesystem::path! om man vill ^^
				std::filesystem::path texture_path = Settings::paths["game_assets"] + "/Textures";
				static std::vector<std::string> current_items(_model_list.size());
				
				// @todo: <info>
				//		Anledningen att vi plockar ut filnamnen, �r att l�gga dem i en Combo (drop-down) s� att vi kan lista filerna, och d� blir det lite roligare
				//		n�r vi l�st pt.1 och kan droppa in nya filer. D� vi bara listar alla filer h�r b�r uppdateringen synas omg�ende.
				//		Liten brasklapp h�r dock, f�r det kanske inte �r super-effektivt att polla filsystemet varje frame! Men jag ans�g att f�r uppgiften var det
				//		b�ttre att "enkelt" kunna se. Typiskt sett skulle en b�ttre l�sninge vara att h�lla fil-listan och bara uppdatera den n�r vi droppar
				//		en fil. S� f�r vi en l�sning mot filsystemet n�r vi droppar, och inte en varje frame :) Men just nu pollar den varje frame!
				//		(p.s. det �r inte upp till er att l�sa det, ni f�r s�klart, men det �r INTE ett krav i uppgiften!)
				//
				//		Vidare, s� beh�ver textur-bytet spawna ett TextureCommand som g�r det �t oss, just nu finns inte det, och h�r �r det just det som �r 
				//		uppgiften. Impelemnetera ett s�dant kommando och l�gg till det p� r�tt s�tt.
				std::string current_item = current_items[i];
				if (ImGui::BeginCombo("##combo", current_item.c_str())) {
					for (auto const& item : std::filesystem::directory_iterator(texture_path)) {
						std::string filename = item.path().filename().string();
						bool is_selected = (filename.c_str() == current_item);
						if (ImGui::Selectable(filename.c_str(), is_selected)) {
							current_items[i] = filename.c_str();
							mi->GetModel()->set_texture(item.path().filename().wstring(), Settings::paths["game_assets"]);
						}
						if (is_selected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}				
			}
			ImGui::PopID();
		}
		
	} ImGui::End();

	
}

