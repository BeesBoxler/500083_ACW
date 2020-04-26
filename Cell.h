#pragma once

#include "CellGroup.h"
#include <ostream>
#include <iostream>
#include <bitset>

class Cell
{
public:
	Cell();
	Cell(const Cell&) = default;
	~Cell();

	explicit Cell(int val);
	

	void updatePossibleValues();
	bool tryUpdateValue();


	//friend std::ostream& operator<<(std::ostream& os, const Cell* const cell);

	void setCellGroup(const int i, const CellGroup* const cg) {
		groups[i] = cg;
	}

	void setValue(const int i) {
		value = i;
	}

	int getValue() const {
		return value;
	}

	bool getPossibleValue(const int i) {
		lookups++;
		return possibleValues[i];
	}

	int getLookupCount() const {
		return lookups;
	}

	Cell& operator=(const Cell&) = default;

private:
	const CellGroup* groups[3] = {};
	bool possibleValues[9] = {true,true,true,
							  true,true,true,
							  true,true,true};
	int value;
	int lookups = 0;
};