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
	//		Så, vad skall vi göra här? tips är att vi gör typ redan det som behövs i ModelProperties.cpp när vi uppdaterar positioner ;)
	return false;
}

bool PositionCommand::Undo() {
	// @todo: <info>
	//		..och tja, om vi listat ut vad vi skall göra när vi exekverar, så vill vi helt enkelt göra tvärt om när vi ångrar
	//		himla fiffigt att vi sparade undan den där extra vector3an med startpositionen ;)
	return false;
}