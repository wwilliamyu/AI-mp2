#include "chess.h"

using namespace std;


void chess::init(state * start) {

	int player=0;//white starts first
	char input;	
	while(1)
	{
		cout<<"play is "<<player<<" ; 0 is white, 1 is black"<<endl;
	tree_construction(start, 3, player, 0);
	// make_decision(start,start->next_states[0]);
	make_decision(start,alpha_prune(start));
	if(gg(start,player)>0)
	{
		cout<<"game ends";
		break;
	}
	player=1-player;
	cin>>input;

	}

}

void chess::tree_construction(state * curr, int depth, int player, int offensive) {

	// given current state

	// player = 0 if white,
	// player = 1 if black

	// if reached leaf nodes, we are done
	if (depth < 0) {
		node_eval(curr, offensive, player);
		// cout<<to_string(curr->value)<<endl;
		return;
	}
	// cout << "BOB ROSS" << endl;
	int forward;
	if (player == 0) { // white player goes up
		forward = -1;
	}
	if (player == 1) { // black player goes down
		forward = 1;
	}
	// cout << "BOB ROSS 1" << endl;
	construct_helper(curr, player, forward);

	// for each of the next states, run recursive function on them
	for (int a = 0; a < curr->next_states.size(); a++) {
		if(depth==3)
		{
		// cout<<"constructing tree level of "+to_string(depth)<<endl;	
		// print_board(curr);			
		}
		//switch player
		tree_construction(curr->next_states[a], depth - 1, 1-player, offensive);
	}
}

void chess::construct_helper(state * curr, int player, int forward) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			// for each piece, judge 3 possible moves


			if (curr->board[y][x] == player
				&& y + forward >= 0
				&& y + forward < 8) {
				// FORWARD
				if (curr->board[y+forward][x] !=player) { // empty
					// cout<<"moving forward"<<endl;
					create_state(curr, y, x, y+forward, x, player);
				} // else cannot create move forward, so do not create state
				// // LEFT DIAG
				// if (x-1>0 && curr->board[y+forward][x-1] != player) { 
				// // 	// enemy piece
				// 	// cout<<"moving left"<<endl;
				// 	create_state(curr, y, x, y+forward, x-1, player);
				// }
				// // else cannot move left diag, there is ally piece
				// // RIGHT DIAG
				// if (x+1<8&&curr->board[y+forward][x+1] != player) {
				// // 	// enemy piece
				// 	// cout<<"moving right"<<endl;
				// 	create_state(curr, y, x, y+forward, x+1, player);
				// }
				// // else cannot move right diag, there is ally piece
			}

		}
	}
}

state* chess::alpha_prune(state * root_node){
	cout<<"start alpha prune"<<endl;
	int v=Max_Val(root_node,std::numeric_limits<int>::min(),std::numeric_limits<int>::max());
	cout<<"the v is "<<v<<endl;

	for(int i=0;i<root_node->next_states.size();i++)
	{
		if(v==root_node->next_states[i]->value)
		{
			// print_board(root_node);
			cout<<"the next state index is"<<to_string(i)<<endl;
			return root_node->next_states[i];
		}
	}
	return NULL;
}

int chess::Min_Val(state * node,int alpha,int beta) {
	if(node->next_states.size()==0)
		{
			// cout<<"the leaf node with Min agent is"<< node->value<<endl;
			return node->value;
		}

	int v=std::numeric_limits<int>::max();
	for(int i=0;i<node->next_states.size();i++)
	{
		v=min(v,Max_Val(node->next_states[i],alpha,beta));
		node->value=v;
		if(v<=alpha)
		{
			return v;
		}
		beta=min(beta,v);
	}
	return v;
}

int chess::Max_Val(state* node,int alpha,int beta){
	if(node->next_states.size()==0)
		{
			// cout<<"the leaf node with Max agent is"<< node->value<<endl;
			return node->value;
		}
	int v=std::numeric_limits<int>::min();
	for(int i=0;i<node->next_states.size();i++)
	{
		v=max(v,Min_Val(node->next_states[i],alpha,beta));
		node->value=v;
		if(v>=beta)
		{
			return v;
		}
		beta=min(beta,v);
	}
	return v;
}


void chess::create_state(state * curr, int prev_y, int prev_x, int new_y, int new_x, int player) {
	state * temp = new state(*curr);
	temp->board[prev_y][prev_x] = 2; // empty
	temp->board[new_y][new_x] = player; // white piece to left diag
	curr->next_states.push_back(temp);
	// print_board(temp);
}

void chess::make_decision(state* &current,state* next){
	state* temp=current;
	cout<<"changing the state from"<<endl;
	print_board(current);
	cout<<"to become"<<endl;
	current=new state(*next);	
	print_board(current);
	delete temp;
}

state * chess::minimax(state * root_node, int max_or_min) {
	// already have tree, with leaf nodes that have values in them
	
	// beginning root node must be max
	// max = 1, min = 0

  	// if leaf node, return leaf node's value
  	if (root_node->next_states.empty()) {
  		return root_node;
  	}
  	if (max_or_min == 1) {
  		int best_value = -2147483647;
  		state * best_node;
  		for (int i = 0; i < root_node->next_states.size(); i++) {
  			state * v = minimax(root_node->next_states[i], 0); // next is min
  			best_value = max(best_value, v->value);
  			if (best_value == v->value) {
  				best_node = v;
  			}
  		}
  		return best_node;
  	}
  	if (max_or_min == 0) {
  		int best_value = 2147483647;
  		state * best_node;
  		for (int j = 0; j < root_node->next_states.size(); j++) {
  			state * v = minimax(root_node->next_states[j], 1); // next is max
  			best_value = min(best_value, v->value);
  			if (best_value == v->value) {
  				best_node = v;
  			}
  		}
  		return best_node;
  	}
  	// will return minimax value of root_node
  	return 0;
}