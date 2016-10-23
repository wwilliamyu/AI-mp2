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
#define DEBUG
using namespace std;

const int boardsize = 8;



class chess {

public:

	chess() {
		cout << "constructing state" << endl;
		state first_state;
		// current_state=first_state;
	};

	struct state {
		int ** board;
		int value;

		state() {
			board = new int*[8];
			for (int y = 0; y < 8; y++) {
				board[y] = new int[8];
				for (int x = 0; x < 8; x++) {
					// if board[y][x]=0, then white, else black, 2 means nothing
					board[y][x] = 2;
					if (y == 0 || y == 1) {
						board[y][x] = 0;
					}
					if (y == 6 || y == 7) {
						board[y][x] = 1;
					}
				}
			}
		};


	/*
	#ifdef DEBUG
		for(int y=0;y<16;y++)
		{
			for(int x=0;x<16;x++)
			{
				if(board[y][x]==2)
				cout<<' ';
				else
					cout<<board[y][x];
			}
			cout<<endl;
		}
	#endif
	*/

		~state() {
			for (int y = 0; y < 8; y++)
			{
				delete board[y];	
			}
			delete board;
		};

		vector<state*> next_states;

	};


	// state root_node;
	void tree_construction(chess::state * curr_state, int depth, int player);
	void construct_helper(chess::state * curr, int player, int forward);
	void create_state(chess::state * curr, int prev_y, int prev_x, int new_y, int new_x, int player);

	// traverse tree, calculating values for all states/nodes
	void calculate_minimax(chess::state * root_node);
	void alpha_prune(chess::state * root_node);
	// return 0 means game not finished, else finished
	// 
	// int make_decision(state* cur, boolean offensive, boolean defensive);

	// offensive is 0, defensive is 1, white player is 0,black is 1
	void node_eval(chess::state * leaf_node,int offensive,int player)
	{

		if(offensive==0)
		{
			int opponent_left=0;
			for(int y=0;y<16;y++)
		{
			for(int x=0;x<16;x++)
			{
				if(leaf_node->board[y][x]==1-player)
					opponent_left++;
			}
		}

			leaf_node->value=16-opponent_left;
		}
		else
		{
			int self_left=0;
			for(int y=0;y<16;y++)
		{
			for(int x=0;x<16;x++)
			{
				if(leaf_node->board[y][x]==1-player)
					self_left++;
			}
		}
			leaf_node->value=self_left;

		}
	};

private:
	void construct(int depth,state);
	int Min_Val(chess::state* node,int alpha,int beta);
	int Max_Val(chess::state* node,int alpha,int beta);
};
#endif

