#pragma once
#include "AbstractCommand.h"

#include <Models/ModelInstance.h>
#include <Math/Vector3.h>

// @todo: <info>
//		Här är en konkret implementation av AbstractCommand!
//		Något väldigt intressant att lägga märke till här, är att vi inte är så låst av interfacet, det stället bara krav att vi implementerar
//		de funktioner som är pure virtual. Gör vi det så kan vi göra lite som vi vill i övrigt.
//		Typiskt sett är inte ett kommando vidare användbart om vi inte har state (i.e. den data vi behöver för att utföra eller ångra kommandot)
//
//		Så PositionCommand tar in en ModelInstance och två Vector3 med position innan och efter kommandot, det är för att vi enkelt skall kunna
//		både ångra, men även återapplicera kommandot. Eventuellt kanske man inte behöver två vector3, utan bara en med deltat. Men jag kände att uppgiften
//		Ville gärna växa, och jag ansåg att det är värt lite extra minne om det blir enklare att förstå :)
//
//		Interfacet här är klart, men i .cpp-filen finns det lite att göra! :D

class PositionCommand : public AbstractCommand {
public:
	PositionCommand(
		ModelInstance* model_instance, 
		Vector3f from, Vector3f to
	);
	~PositionCommand() override;

	bool Execute() override;
	bool Undo() override;

private:
	ModelInstance* _model_instance;
	const Vector3f _from;
	const Vector3f _to;
};