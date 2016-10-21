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

const int boardsize=8;
struct state {
	std::vector<std::vector<int>> maze;
	int value;
};
class chess
{
public:
	chess(){
		state first_state;
		y=0;
		for(int x=0;x<16;x++)
		{
			piece newone=
		}
		y=1;
		y=14;
		y=15;
	};

	~chess();
	std::vector<state> states;	
	void initialize();
	void tree_construction();

	// return 0 means game not finished, else finished
	int make_decision();

};

