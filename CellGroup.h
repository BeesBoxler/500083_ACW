#pragma once

class Cell;
class CellGroup
{
public:

	Cell* cells[9] = {};

	bool isValid();

	static int GetBlockNumber(int col, int row);

};

