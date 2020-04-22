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
		for (int i = 0; i < 81; i++) {
			int in;
			file >> in;
			Cell* c = new Cell(in);
			cells[i] = c;
			int rowIndex = i / 9;
			int colIndex = i % 9;
			int blockIndex = CellGroup::GetBlockNumber(colIndex, rowIndex);
			int blockSpaceIndex = colIndex % 3 + rowIndex % 3 * 3;

			c->groups[0] = rows[rowIndex];
			c->groups[1] = cols[colIndex];
			c->groups[2] = blocks[blockIndex];

			rows[rowIndex]->cells[colIndex] = c;
			cols[colIndex]->cells[rowIndex] = c;
			blocks[blockIndex]->cells[blockSpaceIndex] = c;
		}
	}
}

bool SudokuPuzzle::solved() {
	for (int i = 0; i < 81; i++) {
		if (cells[i]->value == 0)
			return false;
	}
	return true;
}


void SudokuPuzzle::output() const {
	cout << *this;
}