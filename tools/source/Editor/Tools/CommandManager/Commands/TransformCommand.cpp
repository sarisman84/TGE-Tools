#include "TransformCommand.h"

#include <Math/Transform.h>
//#include <ModelInstance.h>
//#include <Math/Vector3.h>

TransformCommand::TransformCommand(ModelInstance *aModelInstance, const Transform aFrom, const Transform aTo) 
	: myModelInstance(aModelInstance)
	, myFrom(aFrom)
	, myTo(aTo)
{

}

TransformCommand::~TransformCommand() {

}

bool TransformCommand::Exectue() {
	myModelInstance->SetTransform(myTo);
	return true;
}

bool TransformCommand::Undo() {
	myModelInstance->SetTransform(myFrom);
	return false;
}