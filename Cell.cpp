#include "Cell.h"


Cell::Cell(): value(0) {}

Cell::~Cell()
{
	for (int i = 0; i < 3; i++) {
		groups[i] = nullptr;
	}
}

Cell::Cell(int const val): value(val) {}

bool Cell::tryUpdateValue() {
	if (this->value != 0) return false;
	int index = -1;
	for (int i = 0; i < 9; i++) {
		if (this->getPossibleValue(i))
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
	int v;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			v = groups[i]->getCell(j)->value;
			if (v == 0) continue;
			possibleValues[v-1] = false;
		}
	}

}

std::ostream& operator<<(std::ostream& os, const Cell* const cell) {
	os << cell->value;
	os << "=> {";
	for (int j = 0; j < 9; j++) {
		if (cell->possibleValues[j])
			os << j + 1 << ",";
	}
	os << "\b}";
	return os;
}
