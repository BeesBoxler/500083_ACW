#include "CellGroup.h"
#include "Cell.h"

int CellGroup::GetBlockNumber(static int col, static int row) {
	int blockRow = row / 3;
	int blockCol = col / 3;
	return blockRow * 3 + blockCol;
}
