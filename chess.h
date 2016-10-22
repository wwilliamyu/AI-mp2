#ifndef _CHESS_H_
#define _CHESS_H_
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

const int boardsize = 8;



class chess
{
public:
	chess(){
		cout<<"constructing state"<<endl;
		// state first_state;
		// current_state=first_state;
	};

	struct state {
	int** maze;
	int value;

	state() {

		maze = new int*[16];
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				// if maze[y][x]=0, then black, else white, 2 means nothing
				maze[y][x]=2;
				if (y == 0 || y == 1) {
					maze[y][x] = 0;
				}
				if (y == 14 || y == 15) {
					maze[y][x] = 1;
				}
			}
		}
		
	}

	~state(){
		for(int y=0;y<16;y++)
		{
			delete maze[y];	
		}
		delete maze;
	}
	std::vector<state> next_states;

};
	// state root_node;
	void tree_construction();
	// return 0 means game not finished, else finished
	int make_decision(state cur);
private:
	void construct(int depth,state);

};
#endif

