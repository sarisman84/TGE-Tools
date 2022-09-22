#pragma once

#include <memory>
#include <stack>

class AbstractCommand;

// @todo: <info>
//		CommandManager �r r�tt enkel och framf�rallt �r allt statiskt, s� den �r v�ldigt l�tt att anv�nda!
//		I grund och botten h�ller den tv� listor, en undo-kommandon och en med redo-kommandon
//		Hur den b�r anv�nda hoppas jag var r�tt tydligt i f�rel�sningen.
//
//		F�r sj�lva funktionalliteten skall ni implementera i .cpp-filen :)

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
