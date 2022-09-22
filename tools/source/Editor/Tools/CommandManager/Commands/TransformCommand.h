#pragma once
#include "AbstractCommand.h"

class TransformCommand : public AbstractCommand {
public:
	TransformCommand(
		ModelInstance* aModelInstance, 
		const Transform aFrom, const Transform aTo
	);
	~TransformCommand() override;

	bool Exectue() override;
	bool Undo() override;

private:
	ModelInstance* myModelInstance;
	const Transform myFrom;
	const Transform myTo;
};