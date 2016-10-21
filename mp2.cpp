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
#include "sudoku.h"

using namespace std;

/** 
* Main function
* args[1] = part 1 or 2
* for Sudoku:
* 	args[2] = grid file path
* 	args[3] = word bank
* for game of breakthrough
*/
int main(int argc, char** args) {
	if (argc != 4) {
			cout << "Wrong input format. Expected ./mp2 [s] [gridfile] [wordbank]"<<endl;
			return 1;
	}
	if (args[1][0] == 's') {
		ifstream gridfile(args[2]);
		ifstream wordbank(args[3]);
		sudokuCell* sudokuGrid[9][9];
		vector < word * > words;
		string line;
		int row = 0;
		while (getline(gridfile, line)) {
			for (int col = 0; col < 9; col++) {
				sudokuCell * curCell = new sudokuCell;
				curCell->x = col;
				curCell->y = row;
				curCell->value = line[col];
				sudokuGrid[row][col] = curCell;
			}
			row++;
		}
		while (getline(wordbank, line)) {
			word * curWord = new word;
			curWord->wordString = line;
			if (curWord->wordString[curWord->wordString.length()-1] == 13)
				curWord->wordString.pop_back();
			transform(curWord->wordString.begin(), curWord->wordString.end(), curWord->wordString.begin(), ::toupper);
			words.push_back(curWord);
		}
		cout << "start to fill the sudoku!!" <<endl;
		fillSudoku(sudokuGrid, words);
	} else {

	}
	return 0;
}