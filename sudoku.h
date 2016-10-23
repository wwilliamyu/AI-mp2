#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

class sudokuCell {
	public:
		char value;
		int x;
		int y;
		int largeCellIdx;
};

class word {
	public:
		int startX;
		int startY;
		char orientation; //'V' for vertical and 'H' for horizontal
		string wordString;
		int numValAvailable; //instantiated when finding the MCV, and cleaned upon found.
		char availableCell [9][9]; // 'v' for vertical, 'h' for horizontal, 'b' for both
		char lcvAvailableCell [9][9]; // 'v' for vertical, 'h' for horizontal, 'b' for both, this is only used when looking for lcv
		word() {
			this->numValAvailable = 0;
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++){
					this->availableCell[i][j] = 'n';
					this->lcvAvailableCell[i][j] = 'n';					
				}
		};
};

class lcv {
	public:
		int x;
		int y;
		char orientation;
		int totalNumValAvailable;
		lcv(): x(9), y(9), orientation('n'), totalNumValAvailable(0) {};
};

class backtrack {

};

bool fillSudoku( sudokuCell* sudokuGrid[9][9], vector<word*> words);

bool isAvailable( sudokuCell* sudokuGrid[9][9], int row, int col, char curChar);

bool recursiveBacktracking (sudokuCell* sudokuGrid[9][9], vector<word*> words);

word * findMCV(sudokuCell* sudokuGrid[9][9], vector<word*> words);

lcv findLCV(sudokuCell* sudokuGrid[9][9], vector<word*> words, word * mcv);

int findLCV_numAvailable (sudokuCell* sudokuGrid[9][9], vector<word*> words, string wordString);

#endif