#pragma once

#include <Engine.h>

class AbstractCommand {
public:
	virtual bool Exectue() = 0;
	virtual bool Undo() = 0;
	virtual ~AbstractCommand() {};
};