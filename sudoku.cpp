#include "sudoku.h"

bool fillSudoku(sudokuCell* sudokuGrid[9][9], vector<word*> words) {
	cout << "the grid to be filled looks like this: "<<endl;
		for (int i =0; i<9; i++) {
			for(int j = 0; j<9; j++) {
				cout << sudokuGrid[i][j]->value;
			}
			cout << endl;
		}
	for (int i = 0; i<words.size(); i++)
		cout << words[i]->wordString << endl;
	// if (isAvailable(sudokuGrid, 5, 4, sudokuGrid[5][4]->value))
	// 	cout << "true" << endl;
	// else 
	// 	cout << "false" << endl;
 	return false;
}

bool isAvailable( sudokuCell* sudokuGrid[9][9], int row, int col, char curChar) {
	cout << curChar << endl;
	int rowStart = 	row /3 * 3;
	int colStart = col/3 * 3;
	if (curChar == '_')
		return true;
	for (int i = 0; i<9; i++) {
		// cout << sudokuGrid[row][i]->value << endl;
		if (sudokuGrid[row][i]->value == curChar && i != col) return false;
		// cout << sudokuGrid[i][col]->value << endl;
		if (sudokuGrid[i][col]->value == curChar && i != row) return false;
		// cout << sudokuGrid[rowStart + i%3][colStart + i/3]->value << endl;
		if (sudokuGrid[rowStart + i%3][colStart + i/3]->value == curChar 
			&& rowStart + i%3 != row && colStart + i/3 != col) return false;
	}
	return true;
}

