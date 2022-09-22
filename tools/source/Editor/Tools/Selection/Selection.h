#pragma once

#include <memory>

class ModelInstance;

class Selection {
public:
	static ModelInstance *GetSelection() { return mySelection; }
	static void SetSelection(ModelInstance* anInstance);

private:
	static ModelInstance *mySelection;
};