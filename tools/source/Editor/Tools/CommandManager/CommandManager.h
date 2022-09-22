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
	template<typename GenericCommand, typename... CommandArgs>
	static void DoCommand(CommandArgs&&... someCommandArgs);



	static void Undo();
	static void Redo();

private:
	static std::stack<std::shared_ptr<AbstractCommand>> _undo_stack;
	static std::stack<std::shared_ptr<AbstractCommand>> _redo_stack;
};

template<typename GenericCommand, typename ...CommandArgs>
inline void CommandManager::DoCommand(CommandArgs && ...someCommandArgs)
{
	
	_undo_stack.push(std::make_shared<GenericCommand>(std::forward<CommandArgs>(someCommandArgs)...));
	_undo_stack.top()->Execute();
	while (!_redo_stack.empty())
	{
		_redo_stack.pop();
	}
}
