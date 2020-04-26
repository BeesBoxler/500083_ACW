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
	//cleanUp();
}

void SudokuPuzzle::cleanUp() {
	for (int i = 0; i < 81; i++) {
		delete cells[i];
	}
}



void SudokuPuzzle::solve(const char filenameIn[]) {
	const int runs = 1;
	unsigned long  times[runs];
	unsigned long  fastestTime, slowestTime;
	unsigned long long average = 0;
	int loops = 0, candidateLookups = 0, solvedCells, zeroCells = 0;
	bool stale = false, updatedThisRound, updated;

	for (int n = 0; n < runs; n++) {
		// Read puzzle from text file
		readPuzzle(filenameIn);

		// Get start time
		const auto startTime = std::chrono::high_resolution_clock::now();
		while (!solved() & !stale) {
			loops++;
			updatedThisRound = false;
			for (int i = 0; i < 81; i++) {
				cells[i]->updatePossibleValues();
				updated = cells[i]->tryUpdateValue();
				updatedThisRound = updated | updatedThisRound;
			}
			stale = !updatedThisRound;
		}
		if (runs == 1)
			for (int i = 0; i < 81; i++) {
				candidateLookups += cells[i]->getLookupCount();
			}
		// Get end time
		const auto endTime = std::chrono::high_resolution_clock::now();
		const auto duration = (endTime - startTime).count();
		// Sample timing output in nanoseconds
		times[n] = duration;
		if (runs == 1)
			std::cout << *this;
		for (int i = 0; i < 81; i++)
			if (cells[i]->getValue() == 0)
				zeroCells++;
		solvedCells = 81 - givenCells - zeroCells;
		givenCells = 0;
		cleanUp();
	}

	fastestTime = ULONG_MAX;
	slowestTime = 0;
	for (int i = 0; i < runs; i++) {
		if (times[i] < fastestTime)
			fastestTime = times[i];
		else if (times[i] > slowestTime)
			slowestTime = times[i];
		average += times[i];
	}
	average = average / runs;

	std::cout << endl;
	if (runs == 1) {
		std::cout << "Number of candidate Lookups: " << candidateLookups << endl;
		std::cout << "Number of loops: " << loops << endl;

	}
	else {
		std::cout << "Number of runs: " << runs << endl;
		std::cout << "Average Time: " << average << endl;
		std::cout << "Fastest Time: " << fastestTime << endl;
		std::cout << "Slowest Time: " << slowestTime << endl;
	}
	std::cout << "Number of Solved Cells: " << solvedCells << endl;
	std::cout << endl;


}


void SudokuPuzzle::readPuzzle(const char filenameIn[]) {
	// Add code to read in a puzzle from the text file and store within the SudokuPuzzle object

	std::ifstream file(filenameIn);
	if (file.good()) {
		int in;
		for (int i = 0; i < 81; i++) {
			file >> in;
			Cell* const c = new Cell(in);
			if (in != 0) incrementGivenCells();
			cells[i] = c;
			const int rowIndex = i / 9;
			const int colIndex = i % 9;
			const int blockIndex = CellGroup::GetBlockNumber(colIndex, rowIndex);
			const int blockSpaceIndex = colIndex % 3 + rowIndex % 3 * 3;

			c->setCellGroup(0, rows[rowIndex]);
			c->setCellGroup(1, cols[colIndex]);
			c->setCellGroup(2, blocks[blockIndex]);

			rows[rowIndex]->setCell(colIndex, c);
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


