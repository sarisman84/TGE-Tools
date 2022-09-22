#include "TextureCommand.h"
#include <Engine.h>

#include <Models/ModelInstance.h>
#include <Models/Model.h>

TextureCommand::TextureCommand(
	ModelInstance* anInstance,
	std::wstring aCurrentTexture,
	std::wstring aNewTexture,
	std::string& aTextureName) :

	myModelInstance(anInstance),
	myOriginalTexture(aCurrentTexture),
	myNewTexture(aNewTexture),
	myTextureName(aTextureName)

{
}

bool TextureCommand::Execute()
{
	if (!myModelInstance) return false;

	myModelInstance->GetModel()->set_texture(myNewTexture, Settings::paths["game_assets"]);
	myTextureName = std::string(myNewTexture.begin(), myNewTexture.end());

	return true;
}

bool TextureCommand::Undo()
{
	if (!myModelInstance) return false;

	myModelInstance->GetModel()->set_texture(myOriginalTexture, Settings::paths["game_assets"]);
	myTextureName = std::string(myOriginalTexture.begin(), myOriginalTexture.end());

	return true;
}
