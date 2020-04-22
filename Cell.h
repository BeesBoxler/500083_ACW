#pragma once

#include "CellGroup.h";
#include <ostream>
#include <iostream>

class Cell
{
public:
	Cell();
	~Cell();

	Cell(int val);
	
	int value;
	CellGroup* groups[3] = {};

	void updatePossibleValues();
	bool tryUpdateValue();

	friend std::ostream& operator<<(std::ostream& os, Cell &cell) {
		os << cell.value;
		os << "=> {";
		for (int j = 0; j < 9; j++) {
			if (cell.possibleValues[j])
				os << j + 1 << ",";
		}
		os << "\b}";
		return os;
	}

private:
	bool possibleValues[9] = {true,true,true,
							  true,true,true,
							  true,true,true};
};