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

class state {
public:
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
						board[y][x] = 1;
					}
					if (y == 6 || y == 7) {
						board[y][x] = 0;
					}
				}
			}
		};

		state(const state &pre)
		{
			board = new int*[8];
			for (int y = 0; y < 8; y++) {
				board[y] = new int[8];
				for (int x = 0; x < 8; x++) {
				board[y][x]=pre.board[y][x];
				}
			}
		};
		
		~state() {
			remove(this);
		};		
		void remove(state* cur){
			if(cur==NULL)
				return;

			for(int i=0;i<cur->next_states.size();i++)
			{
				remove(cur->next_states[i]);
			}
			// cout<<"removing board"<<endl;

			// print_board(cur);
			for (int y = 0; y < 8; y++) {
					delete [] cur->board[y] ;
			// cout<<"removing pointer"+to_string(y)<<endl;

			}
			delete [] cur->board;
		};


			void print_board(state* node)
		{
			for(int y=0;y<8;y++)
			{
				for(int x=0;x<8;x++)
				{
					if(node->board[y][x]==2)
					cout<<' ';	
					else
						cout<<node->board[y][x];
				}
				cout<<endl;
			}
			cout<<endl;
		}

		vector<state*> next_states;

	};

class chess {

public:

	chess() {
		cout << "constructing initial state" << endl;
		root = new state();
		cout<<"root is "<<endl;
		print_board(root);

	};
	state* root;
	void init(state * start);
	void tree_construction(state * curr_state, int depth, int player, int offensive);
	void construct_helper(state * curr, int player, int forward);
	void create_state(state * curr, int prev_y, int prev_x, int new_y, int new_x, int player);
	int minimax(state * root_node, int max_or_min);

	// traverse tree, calculating values for all states/nodes
	state* alpha_prune(state * root_node);
	void make_decision(state*& current,state * next);
	// return 0 means game not finished, else finished
	// 
	// int make_decision(state* cur, boolean offensive, boolean defensive);

	// offensive is 0, defensive is 1, white player is 0,black is 1
	void node_eval(state * leaf_node,int offensive,int player)
	{
		if(offensive==0)
		{
			int opponent_left=0;
			for(int y=0;y<8;y++)
		{
			for(int x=0;x<8;x++)
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
			for(int y=0;y<8;y++)
		{
			for(int x=0;x<8;x++)
			{
				if(leaf_node->board[y][x]==1-player)
					self_left++;
			}
		}
			leaf_node->value=self_left;
		}

		if(leaf_node->value!=0)
			{
				cout<<"leaf_node value is : "<<leaf_node->value<<endl;
				cout<<"player is"<<player<<endl;
				cout<<"the state is :"<<endl;
				print_board(leaf_node);
			}
		for(int y=0;y<8;y++)
		{
			for(int x=0;x<8;x++)
			{
				//if opponent next move can make you dead, this should be avoided
				// if white(0), oppenent move down+1, if black move up,opponent -1
				if(leaf_node->board[y][x]==1-player&&player!=2&&((y+1-2*player)>8||(y+1-2*player)<0))
					{
						// cout<<"reached end"<<endl;
						leaf_node->value=-1000000;
					}

				if(leaf_node->board[y][x]==player&&player!=2&&((y-1+2*player)>8||(y-1+2*player)<0))
					{
						// cout<<"reached end"<<endl;
						leaf_node->value=1000000;
					}
			}
		}
		// cout<<endl;
	};

private:
	void construct(int depth,state);
	int Min_Val(state* node,int alpha,int beta);
	int Max_Val(state* node,int alpha,int beta);

	// return 1 means opponent wins
	// return 2 means player wins
	int gg(state* leaf_node,int player)
	{
		for(int y=0;y<8;y++)
		{
			for(int x=0;x<8;x++)
			{
				//if opponent next move can make you dead, this should be avoided
				// if white(0), oppenent move down+1, if black move up,opponent -1
				if(leaf_node->board[y][x]==1-player&&player!=2&&((y+1-2*player)>8||(y+1-2*player)<0))
					{
						return 1;
					}

				if(leaf_node->board[y][x]==player&&player!=2&&((y-1+2*player)>8||(y-1+2*player)<0))
					{
						return 2;
					}
			}
		}
		return 0;
	}
	void print_board(state* node)
	{
		for(int y=0;y<8;y++)
		{
			for(int x=0;x<8;x++)
			{
				if(node->board[y][x]==2)
				cout<<' ';	
				else
					cout<<node->board[y][x];
			}
			cout<<endl;
		}
		cout<<endl;
	}
};
#endif

