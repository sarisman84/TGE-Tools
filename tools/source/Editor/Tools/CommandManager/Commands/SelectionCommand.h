#pragma once
#include "AbstractCommand.h"

class SelectionCommand : public AbstractCommand {
public:
	SelectionCommand(ModelInstance *aNewSelection);
	~SelectionCommand() override;

	bool Exectue() override;
	bool Undo() override;

private:
	ModelInstance* myNewSelection;
	ModelInstance* myPreviousSelection;
};