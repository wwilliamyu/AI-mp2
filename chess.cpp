#include "chess.h"

using namespace std;

int count = 0;

void chess::init(state * start) {
	int player=0;//white starts first
	while(1)
	{
		cout<<"play is "<<player<<" ; 0 is white, 1 is black"<<endl;
	tree_construction(start, 3, player, 0,player);
	// make_decision(start, Min_Max(start));
	make_decision(start,alpha_prune(start));
if(gg(start,player)>0)
	{
		cout<<"The game has ended." << endl;;
		cout << "Number of nodes expanded: " << ::count <<endl;
		break;
	}
	player=1-player;
	// char input;	
	// cin>>input;
	}

} 


void chess::print_tree(state * node)
{
	for(int i=0;i<node->next_states.size();i++)
	{
		print_tree(node->next_states[i]);
	}
		// if(node->value>0)
		print_board(node);
	return;
}
void chess::tree_construction(state * curr, int depth, int player, int offensive,int agent) {

	// given current state

	// player = 0 if white,
	// player = 1 if black

	// if reached leaf nodes, we are done
	if (depth == 0) {
		// cout<<"value for the leaf node is :"<<to_string(curr->value)<<endl;
		node_eval(curr, offensive, agent);
		return;
	}
	int forward;
	if (player == 0) { // white player goes up
		forward = -1;
	}
	if (player == 1) { // black player goes down
		forward = 1;
	}

	// cout<<"constructing tree level of "+to_string(depth)<<endl;	

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			// for each piece, judge 3 possible moves


			if (curr->board[y][x] == player
				&& y + forward >= 0
				&& y + forward < 8) {
				// FORWARD
				if (curr->board[y+forward][x] ==2) { // empty
					// cout<<"moving forward"<<endl;
					create_state(curr, y, x, y+forward, x, player);					
				} // else cannot create move forward, so do not create state
				// LEFT DIAG
				if (x-1>0 && curr->board[y+forward][x-1] != player) { 

					create_state(curr, y, x, y+forward, x-1, player);
				}
				// else cannot move left diag, there is ally piece
				// RIGHT DIAG
				if (x+1<8&&curr->board[y+forward][x+1] != player) {
					create_state(curr, y, x, y+forward, x+1, player);
				}
				// else cannot move right diag, there is ally piece
			}
			
		}
	}
	for (int a = 0; a < curr->next_states.size(); a++) {
			// print_board(curr->next_states[a]);	
			//switch player
			tree_construction(curr->next_states[a], depth - 1, 1-player, offensive,agent);
	}	
	// print_tree(curr);


		// char a;
	// cin>>a;
	// for each of the next states, run recursive function on them
	// cout<<"the next state size is"<<curr->next_states.size()<<endl;

}

void chess::construct_helper(state * curr, int player, int forward,int agent) {

}

state* chess::alpha_prune(state * root_node){
	// cout<<"start alpha prune"<<endl;
	int v=Max_Val(root_node,std::numeric_limits<int>::min(),std::numeric_limits<int>::max());
	cout<<"the v is "<<v<<endl;
	// cout<<"next_states size is "<<root_node->next_states.size()<<endl;
	int k=0;
	for(int i=0;i<root_node->next_states.size();i++)
	{
		cout<<"theme next state index is"<<to_string(i)<<endl;
		cout<<"the value is "<<root_node->next_states[i]->value<<endl;
		print_board(root_node->next_states[i]);
		if(v==(root_node->next_states[i]->value))
		{
			cout<<"the state value is "<<root_node->next_states[i]->value<<endl;
			print_board(root_node->next_states[i]);
			// print_board(root_node->next_states[i]);
			k=i;
		}
	}
	return root_node->next_states[k];
;
}

int chess::Min_Val(state * node,int alpha,int beta) {
	if(node->next_states.size()==0)
		{
			return node->value;
		}
	int v=std::numeric_limits<int>::max();
	for(int i=0;i<node->next_states.size();i++)
	{
		int max=Max_Val(node->next_states[i],alpha,beta);
		v=v<max? v:max;
		if(v<alpha)
		{
			node->value=v;
			return v;
		}
		beta=min(beta,v);
	}
	node->value=v;
	return v;
}

int chess::Max_Val(state* node,int alpha,int beta){
	if(node->next_states.size()==0)
		{
			return node->value;
		}
	int v=std::numeric_limits<int>::min();
	for(int i=0;i<node->next_states.size();i++)
	{
		int min=Min_Val(node->next_states[i],alpha,beta);
		v=v>min?v:min;
		if(v>beta)
		{
			node->value=v;
			return v;
		}
		alpha=max(alpha,v);
	}
	// string a;
	// cin>>a;
	node->value=v;
	return v;
}


void chess::create_state(state * curr, int prev_y, int prev_x, int new_y, int new_x, int player) {
	state * temp = new state(*curr);
	temp->board[prev_y][prev_x] = 2; // empty
	temp->board[new_y][new_x] = player; // white piece to left diag
	curr->next_states.push_back(temp);
	// cout<<"pushed in the state"<<endl;
	// print_board(curr->next_states[curr->next_states.size()-1]);
	::count++;
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

state* chess::Min_Max(state * root_node){
	// cout<<"start alpha prune"<<endl;
	int v=Max(root_node);
	cout<<"the v is "<<v<<endl;
	// cout<<"next_states size is "<<root_node->next_states.size()<<endl;
	int k=0;
	for(int i=0;i<root_node->next_states.size();i++)
	{
		// cout<<"theme next state index is"<<to_string(i)<<endl;
		// cout<<"the value is "<<root_node->next_states[i]->value<<endl;
		// print_board(root_node->next_states[i]);
		if(v==(root_node->next_states[i]->value))
		{
			// cout<<"the state value is "<<root_node->next_states[i]->value<<endl;
			// print_board(root_node->next_states[i]);
			// print_board(root_node->next_states[i]);
			k=i;
		}
	}
	return root_node->next_states[k];
;
}

int chess::Min(state * node) {
	if(node->next_states.size()==0)
		{
			// cout<<"the leaf node with Min agent is"<< node->value<<endl;
			// print_board(node);
			return node->value;
		}
	int v=std::numeric_limits<int>::max();
	for(int i=0;i<node->next_states.size();i++)
	{
		int max=Max(node->next_states[i]);
		v=v<max? v:max;
	}
	node->value=v;
	return v;
}

int chess::Max(state* node){
	if(node->next_states.size()==0)
		{
			return node->value;
		}
	int v=std::numeric_limits<int>::min();
	for(int i=0;i<node->next_states.size();i++)
	{
		int min=Min(node->next_states[i]);
		v=v>min?v:min;
	}
	node->value=v;
	return v;
}