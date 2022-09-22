#include "SelectionCommand.h"

#include "Selection.h"

SelectionCommand::SelectionCommand(ModelInstance *aNewSelection) {
	myPreviousSelection = Selection::GetSelection();
	myNewSelection = aNewSelection;
}

SelectionCommand::~SelectionCommand() {

}

bool SelectionCommand::Exectue() {
	Selection::SetSelection(myNewSelection);
	return true;
}

bool SelectionCommand::Undo() {
	Selection::SetSelection(myPreviousSelection);
	return true;
}