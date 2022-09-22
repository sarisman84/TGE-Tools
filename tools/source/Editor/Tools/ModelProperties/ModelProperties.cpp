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
	// Här händer en hel massa!
	// Men vi sätter upp ett ImGui-fönster, i det lägger vi en undo-knapp och en redo-knapp. Allt de gör är att säga åt CommandManager att utföra.
	// Sen sätter vi upp inställningar för varje ModelInstance i scenen. Vi loopar helt enkelt igenom dem och sätter upp två inställningsbara värden
	//		Location:
	//			Vi kan ändra värden och se uppdateringen "live", men lägg märke till att inget kommando skapas innan vi avslutat editeringen.
	//			Det är för att annars så skapas kommandon för ALL uppdatering, och det gör undo/redo rätt oanvändbar. Så vi genomför bara kommandot när 
	//			vi ändrat färdigt.
	//		Texture:
	//			Den här är inte skriven alls, och det behöver ni göra :)
	//			Interface finns redan, och implementationen kommer vara väldigt lik "PositionCommand", låt oss kalla den "TextureCommand"
	//			Så ni kommer behöva skapa filer för "TextureCommand", (personligen tycker jag om att lägga till filer utanför VS, men det bör gå även i VS så
	//			så länge ni ser till att filerna hamnar i rätt mappar. För jag har struktur även på filsystemet och inte bara allt i en mapp och filter, för jag
	//			vill att ni skall se en struktur som är något mer robust än vad VS erbjuder "out of the box").
	//			Anyhow.. Jag tror inte det skall vara för svårt att få till kommandot, 
	//			OBS!! lite oavsett hur ni lägger till filerna rekommenderar jag att genererar om projekten, det kan ni göra nästan hur ofta ni vill!
	//				Men att göra det när man ändrat nått i projektet (lagt till filer till exempel) är förmodligen inte fel :)
	//
	//		Sammanfattning:
	//			Ni behöver implementera det som saknas för Location, tomma implementationer finns redan, och ni bör till och med få kommandon redan (som inte gör nått)
	//			Ni behöver implementera hela TextureCommand själva, men fråga om det behövs!

	ImGui::Begin("Models"); {
		// @todo: <info> CommandManager håller koll på alla kommandon som utförs! Den är statisk så väldigt smidig att använda, och kommer att gå att använda även i andra
		// verktyg. Funktionalliteten i Undo() och Redo() behöver ni implementera, titta i CommandManager.cpp så står det mer där :)
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
					// @todo: <info> Om vi precis börjat editera den här framen, så vill vi komma ihåg vart vi var, det är för att det är där vi kommer vara
					// innan vi utförde vårt kommando, vi vill inte göra kommandon för varje uppdatering, då blir det mycket små steg i vår undo/redo!
					_start_position = mi->GetTransform().GetPosition();
				} else if (ImGui::IsItemDeactivatedAfterEdit()) {
					// @todo: <info> 
					//		När vi slutat editera (just den här kontrollen kan vi dra i, så när vi inte längre drar i den...)
					//		Ja då är det läge att skicka vårt kommando. Den observante läsaren ser att här läcker jag minne!
					//		Hur kunde jag enkelt löst det? Fundera så svarar jag lite senare ;)
					CommandManager::DoCommand(new PositionCommand(mi, _start_position, pos));
				}

				// @todo: <info>
				//		Här händer det en del, först och främst, så hämtar vi ut aktiv textur från modellen, och bara ritar ut den i interfacet
				//		Mer kul än användbart, men det finns en hel del vi kan göra med det.
				ImGui::Image((ImTextureID)mi->GetModel()->GetModelData()->texture, ImVec2(32, 32));
				
				// @todo: <info>
				//		Sen plockar vi ut vår game_assets path och itererar över alla filer (vilket bör vara bara .dds).
				//		Jag kontrollerar inte här om det är .ddser, men att göra det bör vara enkelt med hjälp av std::filesystem::path! om man vill ^^
				std::filesystem::path texture_path = Settings::paths["game_assets"] + "/Textures";
				static std::vector<std::string> current_items(_model_list.size());
				
				// @todo: <info>
				//		Anledningen att vi plockar ut filnamnen, är att lägga dem i en Combo (drop-down) så att vi kan lista filerna, och då blir det lite roligare
				//		när vi löst pt.1 och kan droppa in nya filer. Då vi bara listar alla filer här bör uppdateringen synas omgående.
				//		Liten brasklapp här dock, för det kanske inte är super-effektivt att polla filsystemet varje frame! Men jag ansåg att för uppgiften var det
				//		bättre att "enkelt" kunna se. Typiskt sett skulle en bättre lösninge vara att hålla fil-listan och bara uppdatera den när vi droppar
				//		en fil. Så får vi en läsning mot filsystemet när vi droppar, och inte en varje frame :) Men just nu pollar den varje frame!
				//		(p.s. det är inte upp till er att lösa det, ni får såklart, men det är INTE ett krav i uppgiften!)
				//
				//		Vidare, så behöver textur-bytet spawna ett TextureCommand som gör det åt oss, just nu finns inte det, och här är det just det som är 
				//		uppgiften. Impelemnetera ett sådant kommando och lägg till det på rätt sätt.
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

