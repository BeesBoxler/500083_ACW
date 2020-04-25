#pragma once

class Cell;
class CellGroup
{
public:
	CellGroup() {};
	~CellGroup();

	Cell* cells[9] = {};
	static int GetBlockNumber(int col, int row);

};

