#pragma once

#include "CellGroup.h";
#include <ostream>
#include <iostream>

class Cell
{
public:
	Cell();
	~Cell();

	explicit Cell(int val);
	

	void updatePossibleValues();
	bool tryUpdateValue();

	friend std::ostream& operator<<(std::ostream& os, static Cell &cell) {
		os << cell.value;
		os << "=> {";
		for (int j = 0; j < 9; j++) {
			if (cell.possibleValues[j])
				os << j + 1 << ",";
		}
		os << "\b}";
		return os;
	}

	void setCellGroup(const int i, const CellGroup* cg);
	void setValue(int i);
	int getValue() const;

private:
	int value;
	const CellGroup* groups[3] = {};
	bool possibleValues[9] = {true,true,true,
							  true,true,true,
							  true,true,true};
};