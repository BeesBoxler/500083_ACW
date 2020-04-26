#include "SudokuPuzzle.h"

int main(int const argc, char **) {
	SudokuPuzzle puzzle;


	std::cout << "Solving Puzzle 1" << std::endl;
	puzzle.solve("sudoku_puzzle.txt"); 
	std::cout << "Solving Puzzle 2" << std::endl;
	puzzle.solve("sudoku_puzzle2.txt"); 
	std::cout << "Solving Puzzle 3" << std::endl;
	puzzle.solve("sudoku_puzzle3.txt"); 
	std::cout << "Solving Puzzle 4" << std::endl;
	puzzle.solve("sudoku_puzzle4.txt"); 
	std::cout << "Solving Puzzle 5" << std::endl;
	puzzle.solve("sudoku_puzzle5.txt"); 

	return 0;
}
