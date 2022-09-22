#pragma once

#include <Engine.h>

// @todo: <info>
//		Abstrakt interface, alla kommandon behöver implementera det här interfacet, för CommandManager vill ha AbstractCommand objekt, och om vi implementerar
//		detta interface så ÄR vi ett abstrakt kommando, polymorphism.

class AbstractCommand {
public:
	virtual bool Exectue() = 0;
	virtual bool Undo() = 0;
	virtual ~AbstractCommand() {};
};