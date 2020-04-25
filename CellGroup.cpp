#include "CellGroup.h"
#include "Cell.h"

int CellGroup::GetBlockNumber(const int col, const int row) {
	const int blockRow = row / 3;
	const int blockCol = col / 3;
	return blockRow * 3 + blockCol;
}