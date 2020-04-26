#include "CellGroup.h"
#include "Cell.h"

CellGroup::~CellGroup()
{
	std::cout << "Deleting Cellgroup" << std::endl;
	for (int i = 0; i < 9; i++) {
		cells[i] = nullptr;
	}
}

int CellGroup::GetBlockNumber(const int col, const int row) {
	const int blockRow = row / 3;
	const int blockCol = col / 3;
	return blockRow * 3 + blockCol;
}