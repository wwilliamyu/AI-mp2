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
struct piece {
	int x=0;
	int y=0;
	char color;
};

struct state {
	std::vector<piece*> v;
	int value=0;
};
class chess
{
public:
	chess();
	~chess();
	std::vector<state> states;	
	void initialize();
	void tree_construction;

	// return 0 means game not finished, else finished
	int make_decision();

};

