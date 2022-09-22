#include "PositionCommand.h"

PositionCommand::PositionCommand(ModelInstance* model_instance, Vector3f from, Vector3f to)
	: _model_instance(model_instance)
	, _from(from)
	, _to(to)
{

}

PositionCommand::~PositionCommand() {

}

bool PositionCommand::Execute() {

	if (!_model_instance) return false;
		_model_instance->SetLocation(_to);

	// @todo: <info>
	//		S�, vad skall vi g�ra h�r? tips �r att vi g�r typ redan det som beh�vs i ModelProperties.cpp n�r vi uppdaterar positioner ;)
	return true;
}

bool PositionCommand::Undo() {
	// @todo: <info>
	//		..och tja, om vi listat ut vad vi skall g�ra n�r vi exekverar, s� vill vi helt enkelt g�ra tv�rt om n�r vi �ngrar
	//		himla fiffigt att vi sparade undan den d�r extra vector3an med startpositionen ;)

	if (!_model_instance) return false;
	_model_instance->SetLocation(_from);

	return true;
}