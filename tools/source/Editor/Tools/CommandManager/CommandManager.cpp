#include "CommandManager.h"

#include "AbstractCommand.h"

std::stack<AbstractCommand*> CommandManager::_undo_stack;
std::stack<AbstractCommand*> CommandManager::_redo_stack;

void CommandManager::DoCommand(AbstractCommand *command) {
	// @todo: <info>
	//		Hur var det nu?
	//		Vi vill pusha kommandot till undo-stacken, exekvera det och tömma redo-stacken
	//		(det är inte meningsfullt att behålla redo-stacken när ett nytt kommando exekverat, för den blir inaktuell då)
}

void CommandManager::Undo() {
	// @todo: <info>
	//		Och här då, undo, hur var det?
	//		Vi vill anropa undo på det senast tillagda kommandot
	//		så vill vi ta bort det från undo-stacken och lägga det på redo-stacken, makes sense?
	//
	//		En grej att komma ihåg här, är att vi kommer få problem om vi inte har något på undo-stacken och försöker köra ändå, så kom ihåg att
	//		Hantera om undo-stacken är tom!
}

void CommandManager::Redo() {
	// @todo: <info>
	//		Redo är ju bara undo... men tvärt om ;)
}