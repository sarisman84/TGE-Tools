#include "CommandManager.h"

#include "AbstractCommand.h"

std::stack<AbstractCommand*> CommandManager::_undo_stack;
std::stack<AbstractCommand*> CommandManager::_redo_stack;

void CommandManager::DoCommand(AbstractCommand *command) {
	// @todo: <info>
	//		Hur var det nu?
	//		Vi vill pusha kommandot till undo-stacken, exekvera det och t�mma redo-stacken
	//		(det �r inte meningsfullt att beh�lla redo-stacken n�r ett nytt kommando exekverat, f�r den blir inaktuell d�)
}

void CommandManager::Undo() {
	// @todo: <info>
	//		Och h�r d�, undo, hur var det?
	//		Vi vill anropa undo p� det senast tillagda kommandot
	//		s� vill vi ta bort det fr�n undo-stacken och l�gga det p� redo-stacken, makes sense?
	//
	//		En grej att komma ih�g h�r, �r att vi kommer f� problem om vi inte har n�got p� undo-stacken och f�rs�ker k�ra �nd�, s� kom ih�g att
	//		Hantera om undo-stacken �r tom!
}

void CommandManager::Redo() {
	// @todo: <info>
	//		Redo �r ju bara undo... men tv�rt om ;)
}