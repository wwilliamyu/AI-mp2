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
};

/** 
* Main function
* args[1] = part 1 or 2
* for Sudoku:
* 	args[2] = grid file path
* 	args[3] = word bank
* for game of breakthrough
*/
int main(int argc, char** args) {
	if (args[1][0] == 's') {
		if (argc != 4) {
			cout << "Wrong input format. Expected ./mp2 sudoku [gridfile] [wordbank]"<<endl;
			return 1;
		}
		ifstream gridfile(args[2]);
		ifstream wordbank(args[3]);
		vector < vector<sudokuCell*> > sudokuGrid;
		string line;
		int row = 0;
		while (getline(gridfile, line)) {
			if (line.size() == 1)
				continue;
			vector<sudokuCell*> curLine;
			for (int col = 0; col < 9; col++) {
				sudokuCell * curCell = new sudokuCell;
				curCell->x = col;
				curCell->y = row;
				curCell->value = line[col];
				curLine.push_back(curCell);
			}
			row++;
			sudokuGrid.push_back(curLine);
			cout << curLine.size()<<endl;
		}
		for (int i =0; i<9; i++) {
			for(int j = 0; j<9; j++) {
				cout << sudokuGrid[i][j]->value;
			}
			cout << endl;
		}
		
	} else {

	}
	return 0;
}