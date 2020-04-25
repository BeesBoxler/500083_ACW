#include "SudokuPuzzle.h"
#include "Cell.h"
#include "CellGroup.h"
#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;


SudokuPuzzle::SudokuPuzzle() {
	// Add code to initialise the SudokuPuzzle object

	for (int i = 0; i < 9; i++) {
		rows[i] = new CellGroup();
		cols[i] = new CellGroup();
		blocks[i] = new CellGroup();
	}
}

SudokuPuzzle::~SudokuPuzzle()
{
	for (int i = 0; i < 81; i++) {
		cells[i] = nullptr;
	}
}




void SudokuPuzzle::solve(const char filenameIn[]) {
	for (int n = 0; n < 15; n++) {
		// Read puzzle from text file
		readPuzzle(filenameIn);

		// Get start time
		const auto startTime = std::chrono::high_resolution_clock::now();
		while (!solved()) {

			for (int i = 0; i < 81; i++) {
				cells[i]->updatePossibleValues();
				cells[i]->tryUpdateValue();
			}
		}
		// Get end time
		const auto endTime = std::chrono::high_resolution_clock::now();
		const auto duration = (endTime - startTime).count();
		// Sample timing output in nanoseconds
		std::cout << duration << "ns" << std::endl;
	}

	// Output the solved puzzle
	output();
}


void SudokuPuzzle::readPuzzle(const char filenameIn[]) {
	// Add code to read in a puzzle from the text file and store within the SudokuPuzzle object

	std::ifstream file(filenameIn);
	if (file.good()) {
		int in;
		for (int i = 0; i < 81; i++) {
			file >> in;
			Cell* const c = new Cell(in);
			cells[i] = c;
			const int rowIndex = i / 9;
			const int colIndex = i % 9;
			const int blockIndex = CellGroup::GetBlockNumber(colIndex, rowIndex);
			const int blockSpaceIndex = colIndex % 3 + rowIndex % 3 * 3;

			c->setCellGroup(0, rows[rowIndex]);
			c->setCellGroup(1, cols[colIndex]);
			c->setCellGroup(2, blocks[blockIndex]);

			rows[rowIndex]->setCell(colIndex,c);
			cols[colIndex]->setCell(rowIndex, c);
			blocks[blockIndex]->setCell(blockSpaceIndex, c);
		}
	}
}

bool SudokuPuzzle::solved() const {
	for (int i = 0; i < 81; i++) {
		if (cells[i]->getValue() == 0)
			return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const SudokuPuzzle& p) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			os << p.rows[i]->getCell(j)->getValue() << " ";
		}
		os << "\b" << std::endl;
	}
	return os;
}


