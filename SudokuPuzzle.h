#pragma once
#include "Cell.h";
#include "CellGroup.h";


class SudokuPuzzle {
public:
	SudokuPuzzle();
	~SudokuPuzzle();

	void solve (const char filenameIn[]);

	bool solved() const;

	friend std::ostream& operator<<(std::ostream& os, const SudokuPuzzle p) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				os << p.rows[i]->cells[j]->getValue() << " ";
			}
			os << "\b" << std::endl;
		}
		return os;
	}

private:
	CellGroup* rows[9];
	CellGroup* cols[9];
	CellGroup* blocks[9];

	Cell* cells[81] = {};

	void output() const;

	void readPuzzle(const char filenameIn[]);

};