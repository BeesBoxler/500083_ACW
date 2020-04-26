#include "SudokuPuzzle.h"

int main(int const argc, char **) {
	SudokuPuzzle puzzle;


	std::cout << "Solving Puzzle 1" << std::endl;
	puzzle.solve("sudoku_puzzle.txt"); 

	return 0;
}
