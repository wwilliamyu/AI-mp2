#include "chess.h"

using namespace std;


void chess::init(state * start) {
	tree_construction(start, 3, 0, 0);
}

void chess::tree_construction(state * curr, int depth, int player, int offensive) {

	// given current state

	// player = 0 if white,
	// player = 1 if black

	// if reached leaf nodes, we are done
	if (depth == 0) {
		node_eval(curr, offensive, player);
		return;
	}
	cout << "BOB ROSS" << endl;
	int forward;
	if (player == 0) { // white player goes up
		forward = -1;
	}
	if (player == 1) { // black player goes down
		forward = 1;
	}
	cout << "BOB ROSS 1" << endl;
	construct_helper(curr, player, forward);

	// for each of the next states, run recursive function on them
	for (int a = 0; a < curr->next_states.size(); a++) {
		int new_player;
		if (player == 1) {
			new_player = 0;
		}
		else {
			new_player = 1;
		}
		tree_construction(curr->next_states[a], depth - 1, new_player, offensive);
	}
}

void chess::construct_helper(state * curr, int player, int forward) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			// for each piece, judge 3 possible moves
			if (curr->board[y][x] == player
				&& y + forward >= 0
				&& y + forward < 8
				&& x - 1 >= 0
				&& x + 1 <= 8) {
				// FORWARD
				if (curr->board[y+forward][x] == 2) { // empty
					create_state(curr, y, x, y+forward, x, player);
				} // else cannot create move forward, so do not create state

				// LEFT DIAG
				if (curr->board[y+forward][x-1] == 2) { 
					// empty
					create_state(curr, y, x, y+forward, x-1, player);
				}
				if (curr->board[y+forward][x-1] != player) { 
					// enemy piece
					create_state(curr, y, x, y+forward, x-1, player);
				}
				// else cannot move left diag, there is ally piece


				// RIGHT DIAG
				if (curr->board[y+forward][x+1] == 2) {
					// empty
					create_state(curr, y, x, y+forward, x+1, player);
				}
				if (curr->board[y+forward][x+1] != player) {
					// enemy piece
					create_state(curr, y, x, y+forward, x+1, player);
				}
				// else cannot move right diag, there is ally piece
			}
		}
	}
}

state* chess::alpha_prune(state * root_node){
	int v=Max_Val(root_node,std::numeric_limits<int>::min(),std::numeric_limits<int>::max());
	for(int i=0;i<root_node->next_states.size();i++)
	{
		if(v==root_node->next_states[i]->value)
			return root_node->next_states[i];
	}
	return NULL;
}

int chess::Min_Val(state * node,int alpha,int beta) {
	if(node->next_states.size()==0)
		return node->value;

	int v=std::numeric_limits<int>::max();
	for(int i=0;i<node->next_states.size();i++)
	{
		v=min(v,Max_Val(node->next_states[i],alpha,beta));
		if(v<=alpha)
		{
			node->value=v;
			return v;
		}
		beta=min(beta,v);
	}
	return v;
}

int chess::Max_Val(state* node,int alpha,int beta){
	if(node->next_states.size()==0)
		return node->value;
	int v=std::numeric_limits<int>::min();
	for(int i=0;i<node->next_states.size();i++)
	{
		v=max(v,Min_Val(node->next_states[i],alpha,beta));
		if(v>=beta)
		{
			node->value=v;
			return v;
		}
		beta=min(beta,v);
	}
	return v;
}


void chess::create_state(state * curr, int prev_y, int prev_x, int new_y, int new_x, int player) {
	state new_curr(*curr);
	state * temp = &new_curr;
	temp->board[prev_y][prev_x] = 2; // empty
	temp->board[new_y][new_x] = player; // white piece to left diag
	curr->next_states.push_back(temp);
	print_board(temp);
	delete temp;
}

void chess::make_decision(state* &current,state* next){
	state renewed(*next);
	delete current;
	current=&renewed;	
}
void chess::print_tree(state * root) {
	if (root->next_states.empty()) {
		cout << "========" << endl;
		for (int i = 0; i < 8; i++) {
			cout << '|' << endl;
			for (int j = 0; j < 8; j++) {
				if (root->board[i][j] == 0) {
					cout << 'w';
				}
				if (root->board[i][j] == 1) {
					cout << 'b';
				}
				if (root->board[i][j] == 2) {
					cout << ' ';
				}

			}
			cout << '|' << endl;
		}
		cout << "========" << endl;
		return;
	}

	cout << "========" << endl;
	for (int i = 0; i < 8; i++) {
		cout << '|' << endl;
		for (int j = 0; j < 8; j++) {
			if (root->board[i][j] == 0) {
				cout << 'w';
			}
			if (root->board[i][j] == 1) {
				cout << 'b';
			}
			if (root->board[i][j] == 2) {
				cout << ' ';
			}

		}
		cout << '|' << endl;
	}

	for (int a = 0; a < root->next_states.size(); a++) {
		print_tree(root->next_states[a]);
	}
}
