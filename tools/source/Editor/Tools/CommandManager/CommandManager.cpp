#include "CommandManager.h"

#include "AbstractCommand.h"
#include <memory>


std::stack<std::shared_ptr<AbstractCommand>> CommandManager::_undo_stack;
std::stack<std::shared_ptr<AbstractCommand>> CommandManager::_redo_stack;



void CommandManager::Undo() {
	// @todo: <info>
	//		Och h�r d�, undo, hur var det?
	//		Vi vill anropa undo p� det senast tillagda kommandot
	//		s� vill vi ta bort det fr�n undo-stacken och l�gga det p� redo-stacken, makes sense?
	//
	//		En grej att komma ih�g h�r, �r att vi kommer f� problem om vi inte har n�got p� undo-stacken och f�rs�ker k�ra �nd�, s� kom ih�g att
	//		Hantera om undo-stacken �r tom!


	if (_undo_stack.empty()) return;
	_undo_stack.top()->Undo();
	_redo_stack.push(_undo_stack.top());
	_undo_stack.pop();
}

void CommandManager::Redo() {
	// @todo: <info>
	//		Redo �r ju bara undo... men tv�rt om ;)


	if (_redo_stack.empty()) return;

	
	

	_redo_stack.top()->Execute();
	_undo_stack.push(_redo_stack.top());
	_redo_stack.pop();
}