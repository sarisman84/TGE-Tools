#include "CommandManager.h"

#include "AbstractCommand.h"
#include <memory>


std::stack<std::shared_ptr<AbstractCommand>> CommandManager::_undo_stack;
std::stack<std::shared_ptr<AbstractCommand>> CommandManager::_redo_stack;



void CommandManager::Undo() {
	// @todo: <info>
	//		Och här då, undo, hur var det?
	//		Vi vill anropa undo på det senast tillagda kommandot
	//		så vill vi ta bort det från undo-stacken och lägga det på redo-stacken, makes sense?
	//
	//		En grej att komma ihåg här, är att vi kommer få problem om vi inte har något på undo-stacken och försöker köra ändå, så kom ihåg att
	//		Hantera om undo-stacken är tom!


	if (_undo_stack.empty()) return;
	_undo_stack.top()->Undo();
	_redo_stack.push(_undo_stack.top());
	_undo_stack.pop();
}

void CommandManager::Redo() {
	// @todo: <info>
	//		Redo är ju bara undo... men tvärt om ;)


	if (_redo_stack.empty()) return;

	
	

	_redo_stack.top()->Execute();
	_undo_stack.push(_redo_stack.top());
	_redo_stack.pop();
}