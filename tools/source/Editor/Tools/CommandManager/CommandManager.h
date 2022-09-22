#pragma once

#include <memory>
#include <stack>

class AbstractCommand;

// @todo: <info>
//		CommandManager är rätt enkel och framförallt är allt statiskt, så den är väldigt lätt att använda!
//		I grund och botten håller den två listor, en undo-kommandon och en med redo-kommandon
//		Hur den bör använda hoppas jag var rätt tydligt i föreläsningen.
//
//		För själva funktionalliteten skall ni implementera i .cpp-filen :)

class CommandManager {
public:
	static void DoCommand(AbstractCommand* command);
	static void Undo();
	static void Redo();

private:
	static std::stack<AbstractCommand*> _undo_stack;
	static std::stack<AbstractCommand *> _redo_stack;
};