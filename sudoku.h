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
		string wordString;
};

class backtrack {

};

bool fillSudoku( sudokuCell* sudokuGrid[9][9], vector<word*> words);

bool isAvailable( sudokuCell* sudokuGrid[9][9], int row, int col, char curChar);