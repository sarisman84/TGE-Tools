#include "PositionCommand.h"

PositionCommand::PositionCommand(ModelInstance *model_instance, Vector3f from, Vector3f to) 
	: _model_instance(model_instance)
	, _from(from)
	, _to(to)
{

}

PositionCommand::~PositionCommand() {

}

bool PositionCommand::Exectue() {
	// @todo: <info>
	//		S�, vad skall vi g�ra h�r? tips �r att vi g�r typ redan det som beh�vs i ModelProperties.cpp n�r vi uppdaterar positioner ;)
	return false;
}

bool PositionCommand::Undo() {
	// @todo: <info>
	//		..och tja, om vi listat ut vad vi skall g�ra n�r vi exekverar, s� vill vi helt enkelt g�ra tv�rt om n�r vi �ngrar
	//		himla fiffigt att vi sparade undan den d�r extra vector3an med startpositionen ;)
	return false;
}