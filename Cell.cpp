#include "Cell.h"


Cell::Cell() {
	this->value = 0;
}

Cell::Cell(int val) {
	this->value = val;
}

bool Cell::tryUpdateValue() {
	if (this->value != 0) return false;
	int index = -1;
	for (int i = 0; i < 9; i++) {
		if (this->possibleValues[i])
			if (index == -1)
				index = i;
			else
				return false;
	}
	this->value = index + 1 ;
	return true;
}

void Cell::updatePossibleValues() {
	if (this->value != 0) return;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			int v = groups[i]->cells[j]->value;
			if (v == 0) continue;
			possibleValues[v-1] = false;
		}
	}

}

void Cell::setCellGroup(const int i, const CellGroup* cg) {
	groups[i] = cg;
}

void Cell::setValue(const int i) {
	value = i;
}

int Cell::getValue() const{
	return value;
}