#pragma once
#include "AbstractCommand.h"

#include <Models/ModelInstance.h>
#include <Math/Vector3.h>

// @todo: <info>
//		H�r �r en konkret implementation av AbstractCommand!
//		N�got v�ldigt intressant att l�gga m�rke till h�r, �r att vi inte �r s� l�st av interfacet, det st�llet bara krav att vi implementerar
//		de funktioner som �r pure virtual. G�r vi det s� kan vi g�ra lite som vi vill i �vrigt.
//		Typiskt sett �r inte ett kommando vidare anv�ndbart om vi inte har state (i.e. den data vi beh�ver f�r att utf�ra eller �ngra kommandot)
//
//		S� PositionCommand tar in en ModelInstance och tv� Vector3 med position innan och efter kommandot, det �r f�r att vi enkelt skall kunna
//		b�de �ngra, men �ven �terapplicera kommandot. Eventuellt kanske man inte beh�ver tv� vector3, utan bara en med deltat. Men jag k�nde att uppgiften
//		Ville g�rna v�xa, och jag ans�g att det �r v�rt lite extra minne om det blir enklare att f�rst� :)
//
//		Interfacet h�r �r klart, men i .cpp-filen finns det lite att g�ra! :D

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