#pragma once

class Cell;
class CellGroup
{
public:
	CellGroup() {};
	CellGroup(const CellGroup&) = default;
	~CellGroup();

	static int GetBlockNumber(const int, const int);

	void setCell(const int i, Cell* const v) {
		cells[i] = v;
	}
	Cell* getCell(int i) const {
		return cells[i];
	}

	CellGroup& operator=(const CellGroup&) = default;

private:
	Cell* cells[9] = {};
};

