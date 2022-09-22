#include "CommandManager.h"

#include "AbstractCommand.h"

std::stack<std::shared_ptr<AbstractCommand>> CommandManager::myUndoStack;
std::stack<std::shared_ptr<AbstractCommand>> CommandManager::myRedoStack;

void CommandManager::DoCommand(std::shared_ptr<AbstractCommand> aCommand) {
	myUndoStack.push(aCommand);
	myUndoStack.top()->Exectue();

	while (myRedoStack.empty() == false) {
		myRedoStack.pop();
	}
}

void CommandManager::Undo() {
	if (myUndoStack.empty() == false) {
		myUndoStack.top()->Undo();
		myRedoStack.push(myUndoStack.top());
		myUndoStack.pop();
	}
}

void CommandManager::Redo() {
	if (myRedoStack.empty() == false) {
		myRedoStack.top()->Exectue();
		myUndoStack.push(myRedoStack.top());
		myRedoStack.pop();
	}
}