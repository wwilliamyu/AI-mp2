#ifndef _STATE_H_
#define _STATE_H_

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

class state {

	public:
		vector< vector<int> > board;

		vector< vector<int> > get_board() {
			return board;
		}

		state() {

			// construct board
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					if (y == 0 || y == 1) {
						board[y][x] = 2; // black piece
					}
					else if (y == 6 || y == 7) {
						board[y][x] = 1; // white piece
					}
					else {
						board[y][x] = 0; // empty
					}
				}
			}
		}
};

#endif