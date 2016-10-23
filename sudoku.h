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


namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW 	= 33,
        FG_BLUE     = 36,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

class sudokuCell {
	public:
		char value;
		int x;
		int y;
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

class csp {
	public: 
		vector<word*> mcvAssignment;
		vector<lcv> lcvAssignment;
		int nodeExpanded;
		csp() {
			this->nodeExpanded = 0;
		}
};


bool sortMostConstrained (const word* lhs, const word * rhs);
bool sortleastConstraining (const lcv lhs, const lcv rhs);

bool fillSudoku( sudokuCell* sudokuGrid[9][9], vector<word*> words, csp* CSP);

bool isAvailable( sudokuCell* sudokuGrid[9][9], int row, int col, char curChar);

vector<word*> findMCV(sudokuCell* sudokuGrid[9][9], vector<word*> words);

vector<lcv> findLCV(sudokuCell* sudokuGrid[9][9], vector<word*> words, word * mcv);

int findLCV_numAvailable (sudokuCell* sudokuGrid[9][9], vector<word*> words, string wordString);

#endif