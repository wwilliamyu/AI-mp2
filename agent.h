#ifndef _AGENT_H_
#define _AGENT_H_

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

class agent {

	public:
		void make_move();
		void minimax();
		void alphabeta();
};

#endif