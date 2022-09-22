#pragma once

#include <Engine.h>

// @todo: <info>
//		Abstrakt interface, alla kommandon beh�ver implementera det h�r interfacet, f�r CommandManager vill ha AbstractCommand objekt, och om vi implementerar
//		detta interface s� �R vi ett abstrakt kommando, polymorphism.

class AbstractCommand {
public:
	virtual bool Execute() = 0;
	virtual bool Undo() = 0;
	virtual ~AbstractCommand() {};
};