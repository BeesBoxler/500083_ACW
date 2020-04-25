#pragma once

#include "Cell.h"
#include "CellGroup.h"


class SudokuPuzzle {
public:
	SudokuPuzzle();
	SudokuPuzzle(const SudokuPuzzle&) = default;
	~SudokuPuzzle();

	void solve (const char filenameIn[]);

	bool solved() const;

	friend std::ostream& operator<<(std::ostream& os, const SudokuPuzzle& p);

	SudokuPuzzle& operator=(const SudokuPuzzle&) = default;

private:
	CellGroup* rows[9];
	CellGroup* cols[9];
	CellGroup* blocks[9];

	Cell* cells[81] = {};

	inline void output() const {
		std::cout << *this;
	}

	void readPuzzle(const char filenameIn[]);

};