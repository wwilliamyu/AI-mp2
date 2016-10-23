#include "sudoku.h"

bool isAvailable( sudokuCell* sudokuGrid[9][9], int row, int col, char curChar) {
	int rowStart = 	row /3 * 3;
	int colStart = col/3 * 3;
	if (curChar == '_')
		return true;
	for (int i = 0; i<9; i++) {
		// cout << sudokuGrid[row][i]->value << endl;
		if (sudokuGrid[row][i]->value == curChar && i != col) return false;
		// cout << sudokuGrid[i][col]->value << endl;
		if (sudokuGrid[i][col]->value == curChar && i != row) return false;
		// cout << sudokuGrid[rowStart + i%3][colStart + i/3]->value << endl;
		if (sudokuGrid[rowStart + i%3][colStart + i/3]->value == curChar 
			&& (rowStart + i%3 != row && colStart + i/3 != col)) return false;
	}
	return true;
}

bool fillSudoku (sudokuCell* sudokuGrid[9][9], vector<word*> words, csp* CSP) {
	// cout << "enter recursion" <<endl;
	Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier yellow(Color::FG_YELLOW);

    bool allFilled = true;
    if (words.empty()) {
    	for (int i = 0; i < 9; i++)
    		for (int j=0; j<9; j++)
    			if (sudokuGrid[i][j]->value == '_')
    				allFilled = false;
		if (allFilled) {
			cout << yellow << "The Word Sudoku is ALL filled!" << def << endl;
			return true;
		}
    }
		
	// cout << "number of words in the current recursion is "<< blue <<words.size() <<def <<endl;
	vector<word*> mcvVector = findMCV(sudokuGrid,words); //MCV is at the back
	// for (int i =0; i<mcvVector.size(); i++)
	// 	cout << yellow << mcvVector[i]->wordString << def <<endl;
	// cout << "number of mcv in the current recursion is "<< blue <<mcvVector.size() <<def <<endl;
	vector<lcv> lcvVector;
	lcvVector = findLCV(sudokuGrid, words, mcvVector.back()); //LCV is at the back too
	// for (int i = 0; i < lcvVector.size(); i++)
		// cout << "least constraining value is ["<< lcvVector[i].x <<"," << lcvVector[i].y << "] "<< lcvVector[i].totalNumValAvailable << " orientation=" << lcvVector[i].orientation<< endl;
	//now that we have the most constrained variable and the least constraining value, let's try to assign it and recurse

	word * curMCV;
	bool result;

	if (mcvVector.size() == 0) {
		// cout << "no available variables at all" << endl;
			return false;		
	}
	curMCV= mcvVector.back();
	mcvVector.pop_back();
	// cout << "curMCV is "<< blue <<curMCV->wordString << def << endl;
	if (lcvVector.size() == 0) {
		// cout << "no available values at all" << endl;
		return false;
	}
	do {
		lcv curLCV;
		curLCV = lcvVector.back();
		lcvVector.pop_back();
		// cout << "curLCV is ["<<  green << curLCV.x <<"," << curLCV.y << def<< "] " << curLCV.totalNumValAvailable << " orientation=" << curLCV.orientation<< endl;
		curMCV->startX = curLCV.x;
		curMCV->startY = curLCV.y;
		curMCV->orientation = curLCV.orientation;

		
		if (curMCV->orientation == 'h') {
			//fill the grid
			string temp;
			for (int curCharIdx=0; curCharIdx < curMCV->wordString.size(); curCharIdx++) {
				temp.push_back(sudokuGrid[curMCV->startX][curMCV->startY+curCharIdx]->value);
				sudokuGrid[curMCV->startX][curMCV->startY+curCharIdx]->value = curMCV->wordString[curCharIdx];
			}
			// cout << red << "temp is " << temp  << def << endl;
			// cout << blue;
			// for (int i=0; i<9; i++) {
			// 	for (int j=0; j<9; j++) {
			// 		cout << sudokuGrid[i][j]->value;			
			// 	}
			// 	cout << endl;
			// }
			// cout << def<< endl;
			// recurse
			result = fillSudoku(sudokuGrid, mcvVector, CSP);
			if (result == true) {
				CSP->lcvAssignment.push_back(curLCV);
				CSP->mcvAssignment.push_back(curMCV);
				CSP->nodeExpanded++;
				return true;
			}
			//reset
			for (int curCharIdx=0; curCharIdx < curMCV->wordString.size(); curCharIdx++)
				sudokuGrid[curMCV->startX][curMCV->startY+curCharIdx]->value = temp[curCharIdx];
			// mcvVector.insert(mcvVector.begin(), curMCV);
		} else {
			//fill the grid
			string temp;
			for (int curCharIdx=0; curCharIdx < curMCV->wordString.size(); curCharIdx++) {
				temp.push_back(sudokuGrid[curMCV->startX+curCharIdx][curMCV->startY]->value);
				sudokuGrid[curMCV->startX+curCharIdx][curMCV->startY]->value = curMCV->wordString[curCharIdx];
			}
			// cout << red << "temp is " << temp  << def << endl;
			// recurse
			// cout << blue;
			// for (int i=0; i<9; i++) {
			// 	for (int j=0; j<9; j++) {
			// 		cout << sudokuGrid[i][j]->value;			
			// 	}
			// 	cout << endl;
			// }
			// cout << def<< endl;
			result = fillSudoku(sudokuGrid, mcvVector, CSP);
			if (result == true) {
				CSP->lcvAssignment.push_back(curLCV);
				CSP->mcvAssignment.push_back(curMCV);
				CSP->nodeExpanded++;
				return true;
			}
			//reset
			for (int curCharIdx=0; curCharIdx < curMCV->wordString.size(); curCharIdx++)
				sudokuGrid[curMCV->startX+curCharIdx][curMCV->startY]->value = temp[curCharIdx];	
			// mcvVector.insert(mcvVector.begin(), curMCV);
		}
		// cout << red << curMCV->wordString << " at [" << curLCV.x <<","<<curLCV.y <<"] orientation=" <<curLCV.orientation << " doesn't work!" << def <<endl;
	} while (lcvVector.size() != 0);
	// cout << "all lcv failed" << endl;
	CSP->nodeExpanded++;
	return false;

}

/**
* helper function to sort a mcv vector by numValAvailable
* the one with smallest value will be to the back
*/
bool sortMostConstrained (const word* lhs, const word * rhs) {
	return lhs->numValAvailable > rhs->numValAvailable;
}

/**
* funtion to find the most constrained variable
* choose the variable with the fewest legal values - fewest cell to assign
* minimum remaining values (MRV) heuristic
* returns a vector of words and the MCV is at the back of the vector
*/
vector<word*> findMCV(sudokuCell* sudokuGrid[9][9], vector<word*> words) {
	//sort the vector by the number of available cells * orientation to assign
	//try all the cells and record the number available to be assigned
	for ( int curWordIdx = 0; curWordIdx <words.size(); curWordIdx++) {
		word * curWord = words[curWordIdx];
		for (int i=0; i<9; i++)
			for (int j=0; j<9; j++) 
				curWord->availableCell[i][j] = 'n';
		for (int i=0; i<9; i++)
			for (int j=0; j<9; j++) {
				// cout <<"checking h v from" << i << ' ' << j << endl;
				//horizontal
				// cout << "h" <<endl;
				if (j+curWord->wordString.size()-1 < 9) {
					int curCharIdx;
					for (curCharIdx = 0; curCharIdx < curWord->wordString.size(); curCharIdx++) {
						if ( (sudokuGrid[i][j+curCharIdx]->value != '_' &&
							sudokuGrid[i][j+curCharIdx]->value != curWord->wordString[curCharIdx]) ||
							!isAvailable(sudokuGrid, i, j+curCharIdx, curWord->wordString[curCharIdx])){
							break;
						}
					}
					if (curCharIdx == curWord->wordString.size()) { //if the whole word can fit horizontally from sudokuGrid[i][j]
						curWord->numValAvailable++;
						curWord->availableCell[i][j] = 'h';
						
					}
				}
				//vertical	
				// cout << "v" <<endl;
				if (i+curWord->wordString.size()-1 < 9) {
					int curCharIdx;
					for (curCharIdx = 0; curCharIdx < curWord->wordString.size(); curCharIdx++) {
						if ( (sudokuGrid[i+curCharIdx][j]->value != '_' &&
							sudokuGrid[i+curCharIdx][j]->value != curWord->wordString[curCharIdx]) ||
							!isAvailable(sudokuGrid, i+curCharIdx, j, curWord->wordString[curCharIdx])) {
							break;
						}
					}
					if (curCharIdx == curWord->wordString.size()){ //if the whole word can fit vertically from sudokuGrid[i][j]
						// cout << "increment count !!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
						curWord->numValAvailable++;
						curWord->availableCell[i][j] = curWord->availableCell[i][j] == 'h' ? 'b' : 'v';
					}
				}
			}
		// cout << curWord->wordString << "->numValAvailable = " << curWord->numValAvailable << endl;
	}
	//find the most constrained variable
	vector<word*> mcvVector;
	for ( int curWordIdx = 0; curWordIdx < words.size(); curWordIdx++) {
		mcvVector.push_back(words[curWordIdx]);
	}
	sort(mcvVector.begin(), mcvVector.end(), sortMostConstrained);
	//clean the numValAvailable value;
	for ( int curWordIdx = 0; curWordIdx < words.size(); curWordIdx++) {
		words[curWordIdx]->numValAvailable = 0;
	}

	return mcvVector;
}

bool sortleastConstraining (const lcv lhs, const lcv rhs) {
	return lhs.totalNumValAvailable < rhs.totalNumValAvailable;
}

/**
* funtion to find the least constraining value
* choose the value/cell (x,y) that rules out the fewest values in the remaining variables
* first choose a value, then calculate the total numValAvailable then return a vector of lcvs 
* the lcv with largest value of numValAvailable is at the back
*/
vector<lcv> findLCV(sudokuCell* sudokuGrid[9][9], vector<word*> words, word * mcv) {
	// cout << "--------------------find LCV-------------------" <<endl;
	vector <lcv> lcvVector;
	if (words.size() == 0) 
		return lcvVector;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++){
			if (mcv->availableCell[i][j] != 'n') {
				// cout << i  << " " << j << " " << mcv->availableCell[i][j] << " " << sudokuGrid[i][j]->value<< endl;
				if (mcv->availableCell[i][j] == 'h') {
					// cout << "find lcv horizontal" <<endl;
					lcv curlcv;
					curlcv.x = i;
					curlcv.y = j;
					curlcv.orientation = 'h';
					//fill the grid
					string temp;
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++) {
						temp.push_back(sudokuGrid[i][j+curCharIdx]->value);
						sudokuGrid[i][j+curCharIdx]->value = mcv->wordString[curCharIdx];
					}
					// //call the helper
					// for (int i =0; i<9; i++) {
					// 	for(int j = 0; j<9; j++) {
					// 		cout << sudokuGrid[i][j]->value;
					// 	}
					// 	cout << endl;
					// }
					curlcv.totalNumValAvailable = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					// cout << "curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i][j+curCharIdx]->value = temp[curCharIdx];
					//for all posible lcv, push to the vector
					lcvVector.push_back(curlcv);
				}
				if (mcv->availableCell[i][j] == 'v') {
					// cout << "find lcv vertical" <<endl;
					lcv curlcv;
					curlcv.x = i;
					curlcv.y = j;
					curlcv.orientation = 'v';
					//fill the grid
					string temp;
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++) {
						temp.push_back(sudokuGrid[i+curCharIdx][j]->value);
						sudokuGrid[i+curCharIdx][j]->value = mcv->wordString[curCharIdx];
					}
					// //call the helper
					// for (int i =0; i<9; i++) {
					// 	for(int j = 0; j<9; j++) {
					// 		cout << sudokuGrid[i][j]->value;
					// 	}
					// 	cout << endl;
					// }
					curlcv.totalNumValAvailable = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					// cout << "curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i+curCharIdx][j]->value = temp[curCharIdx];
					//for all posible lcv, push to the vector
					lcvVector.push_back(curlcv);
				}
				if (mcv->availableCell[i][j] == 'b') {
					// cout << "FIND LCV BOTH" <<endl;
					lcv curlcv;
					curlcv.x = i;
					curlcv.y = j;
					string temp;

					//first horizontal
					curlcv.orientation = 'h';
					//fill the grid
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++) {
						temp.push_back(sudokuGrid[i][j+curCharIdx]->value);
						sudokuGrid[i][j+curCharIdx]->value = mcv->wordString[curCharIdx];
					}
					// //call the helper
					// for (int i =0; i<9; i++) {
					// 	for(int j = 0; j<9; j++) {
					// 		cout << sudokuGrid[i][j]->value;
					// 	}
					// 	cout << endl;
					// }
					curlcv.totalNumValAvailable = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					// cout << "horizontal curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i][j+curCharIdx]->value = temp[curCharIdx];
					temp = "";

					//then vertical
					//fill the grid
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++) {
						temp.push_back(sudokuGrid[i+curCharIdx][j]->value);
						sudokuGrid[i+curCharIdx][j]->value = mcv->wordString[curCharIdx];
					}
					// //call the helper
					// for (int i =0; i<9; i++) {
					// 	for(int j = 0; j<9; j++) {
					// 		cout << sudokuGrid[i][j]->value;
					// 	}
					// 	cout << endl;
					// }
					int numAvailable_temp = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					if (numAvailable_temp > curlcv.totalNumValAvailable) {
						curlcv.totalNumValAvailable = numAvailable_temp;
						curlcv.orientation = 'v';
					}
					// cout << "vertical numAvailable_temp=" << numAvailable_temp << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i+curCharIdx][j]->value = temp[curCharIdx];
					// cout << "both curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//for all posible lcv, push to the vector
					lcvVector.push_back(curlcv);
				}
				// cout << endl;
			}
		}
	// sort(mcvVector.begin(), mcvVector.end(), sortMostConstrained);
	sort(lcvVector.begin(), lcvVector.end(), sortleastConstraining); 
	// lcv leastConstrainingValue = lcvVector[0];
	// for (int i=0; i < lcvVector.size() ; i++) {
	// 	cout << "lcvVector[" << i << "] x=" <<lcvVector[i].x <<" y=" << lcvVector[i].y << " totalNumValAvailable=" << lcvVector[i].totalNumValAvailable << " orientation=" << lcvVector[i].orientation<<endl;		
	// 	if (lcvVector[i].totalNumValAvailable < leastConstrainingValue.totalNumValAvailable)
	// 		leastConstrainingValue = lcvVector[i];
	// }
	return lcvVector;
}

int findLCV_numAvailable (sudokuCell* sudokuGrid[9][9], vector<word*> words, string wordString) {
	int totalNumValAvailable = 0;
	for ( int curWordIdx = 0; curWordIdx <words.size(); curWordIdx++) {
		word * curWord = words[curWordIdx];
		if (curWord->wordString == wordString) //we only want other strings 
			continue;
		for (int i=0; i<9; i++)
			for (int j=0; j<9; j++) 
				curWord->lcvAvailableCell[i][j] = 'n';

		for (int i=0; i<9; i++)
			for (int j=0; j<9; j++) {
				if (j+curWord->wordString.size()-1 < 9) {
					int curCharIdx;
					for (curCharIdx = 0; curCharIdx < curWord->wordString.size(); curCharIdx++) {
						if ( (sudokuGrid[i][j+curCharIdx]->value != '_' &&
							sudokuGrid[i][j+curCharIdx]->value != curWord->wordString[curCharIdx]) ||
							!isAvailable(sudokuGrid, i, j+curCharIdx, curWord->wordString[curCharIdx])){
							break;
						}
					}
					if (curCharIdx == curWord->wordString.size()) { //if the whole word can fit horizontally from sudokuGrid[i][j]
						totalNumValAvailable++;
						
					}
				}
				//vertical	
				if (i+curWord->wordString.size()-1 < 9) {
					int curCharIdx;
					for (curCharIdx = 0; curCharIdx < curWord->wordString.size(); curCharIdx++) {
						if ( (sudokuGrid[i+curCharIdx][j]->value != '_' &&
							sudokuGrid[i+curCharIdx][j]->value != curWord->wordString[curCharIdx]) ||
							!isAvailable(sudokuGrid, i+curCharIdx, j, curWord->wordString[curCharIdx])) {
							break;
						}
					}
					if (curCharIdx == curWord->wordString.size()){ //if the whole word can fit vertically from sudokuGrid[i][j]
						totalNumValAvailable++;
					}
				}
			}
	}
	return totalNumValAvailable;
}