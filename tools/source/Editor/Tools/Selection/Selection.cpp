#include "Selection.h"

ModelInstance *Selection::mySelection;

void Selection::SetSelection(ModelInstance* aNewSelection) {
	mySelection = aNewSelection;
}