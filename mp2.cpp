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
#include <chrono> // C++11
#include "sudoku.h"
#include "chess.h"
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
	

	if (args[1][0]=='c')
	{
		cout<<"starting the chess game"<<endl;

		chess game;
		
		game.init(game.root);
	}

	if (argc != 4 && args[1][0] == 's') {
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
		Color::Modifier red(Color::FG_RED);
		Color::Modifier def(Color::FG_DEFAULT);
    	Color::Modifier blue(Color::FG_BLUE);
    	Color::Modifier green(Color::FG_GREEN);
    	Color::Modifier yellow(Color::FG_YELLOW);

	    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now() ;
	    cout << typeid(start).name() << endl;
		cout << red << "--------------------start to fill the sudoku!!---------------------" << def <<endl;
		csp * solution = new csp;
		solution->nodeExpanded = 0;
		fillSudoku(sudokuGrid, words, solution);	
		cout << blue;
		for (int i=0; i<9; i++) {
			for (int j=0; j<9; j++) {
				cout << sudokuGrid[i][j]->value;			
			}
			cout << endl;
		}
		cout << def;
		cout << yellow;
		for (int i =solution->mcvAssignment.size()-1; i >=0; i--) {
			cout << solution->lcvAssignment[i].orientation << " " << solution->lcvAssignment[i].x << " " << solution->lcvAssignment[i].y << ": " << solution->mcvAssignment[i]->wordString << endl;
		}
		cout << green << "Number of nodes expanded is " << solution->nodeExpanded << endl;
		std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
	    std::cout << "Filling up the sudoku took " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
	              << " milliseconds\n" << def << endl;
	} 
	return 0;
}