#pragma once
#include "AbstractCommand.h"

#include <Models/ModelInstance.h>
#include <Math/Vector3.h>
#include <string>

class TextureCommand : public AbstractCommand
{
public:
	TextureCommand(
		ModelInstance* anInstance,
		std::wstring aCurrentTexture,
		std::wstring aNewTexture,
		std::string& aTextureName
	);
	// Inherited via AbstractCommand
	bool Execute() override;
	bool Undo() override;


private:
	ModelInstance* myModelInstance;
	std::wstring myOriginalTexture;
	std::wstring myNewTexture;
	std::string& myTextureName;
};

