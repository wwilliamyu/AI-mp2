#include "sudoku.h"

bool fillSudoku(sudokuCell* sudokuGrid[9][9], vector<word*> words) {
	// cout << "the grid to be filled looks like this: "<<endl;
	// 	for (int i =0; i<9; i++) {
	// 		for(int j = 0; j<9; j++) {
	// 			cout << sudokuGrid[i][j]->value;
	// 		}
	// 		cout << endl;
	// 	}
	// cout << "the word bank: " <<endl;
	// for (int i = 0; i<words.size(); i++)
	// 	cout << words[i]->wordString << endl;
	recursiveBacktracking(sudokuGrid, words);
 	return false;
}

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

bool recursiveBacktracking (sudokuCell* sudokuGrid[9][9], vector<word*> words) {
	word * mcv = findMCV(sudokuGrid,words);
	cout << mcv->wordString << endl;
	// for (int i = 0; i < 9; i++)
	// 	for (int j = 0; j < 9; j++){
	// 		if (mcv->availableCell[i][j] != 'n')
	// 			cout << i  << " " << j << " " << mcv->availableCell[i][j] << " " << sudokuGrid[i][j]->value<< endl;
	// 	}
	lcv lcv = findLCV(sudokuGrid, words, mcv);
	cout << "least constraining value is ["<< lcv.x <<"," << lcv.y << "] "<< lcv.totalNumValAvailable << endl;
	//now that we have the most constrained variable, let's find its least constraining value


	return true;

}

/**
* funtion to find the most constrained variable
* choose the variable with the fewest legal values - fewest cell to assign
* minimum remaining values (MRV) heuristic
*/
word * findMCV(sudokuCell* sudokuGrid[9][9], vector<word*> words) {
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
						// cout << "increment count !!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
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
		cout << curWord->wordString << "->numValAvailable = " << curWord->numValAvailable << endl;
	}
	//find the most constrained variable
	word * mcv = words[0];
	for ( int curWordIdx = 0; curWordIdx < words.size(); curWordIdx++) {
		if (mcv->numValAvailable > words[curWordIdx]->numValAvailable){
			mcv = words[curWordIdx];			
		}
	}
	//clean the numValAvailable value;
	for ( int curWordIdx = 0; curWordIdx < words.size(); curWordIdx++) {
		words[curWordIdx]->numValAvailable = 0;
	}

	return mcv;
}

/**
* funtion to find the least constraining value
* choose the value/cell (x,y) that rules out the fewest values in the remaining variables
* first choose a value, then calculate the total numValAvailable then return the one with the largest value of numValAvailable
*/
lcv findLCV(sudokuCell* sudokuGrid[9][9], vector<word*> words, word * mcv) {
	cout << "--------------------find LCV-------------------" <<endl;
	vector <lcv> lcvVector;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++){
			if (mcv->availableCell[i][j] != 'n') {
				// cout << i  << " " << j << " " << mcv->availableCell[i][j] << " " << sudokuGrid[i][j]->value<< endl;
				if (mcv->availableCell[i][j] == 'h') {
					cout << "find lcv horizontal" <<endl;
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
					//call the helper
					for (int i =0; i<9; i++) {
						for(int j = 0; j<9; j++) {
							cout << sudokuGrid[i][j]->value;
						}
						cout << endl;
					}
					curlcv.totalNumValAvailable = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					cout << "curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i][j+curCharIdx]->value = temp[curCharIdx];
					//for all posible lcv, push to the vector
					lcvVector.push_back(curlcv);
				}
				if (mcv->availableCell[i][j] == 'v') {
					cout << "find lcv vertical" <<endl;
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
					//call the helper
					for (int i =0; i<9; i++) {
						for(int j = 0; j<9; j++) {
							cout << sudokuGrid[i][j]->value;
						}
						cout << endl;
					}
					curlcv.totalNumValAvailable = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					cout << "curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i+curCharIdx][j]->value = temp[curCharIdx];
					//for all posible lcv, push to the vector
					lcvVector.push_back(curlcv);
				}
				if (mcv->availableCell[i][j] == 'b') {
					cout << "FIND LCV BOTH" <<endl;
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
					//call the helper
					for (int i =0; i<9; i++) {
						for(int j = 0; j<9; j++) {
							cout << sudokuGrid[i][j]->value;
						}
						cout << endl;
					}
					curlcv.totalNumValAvailable = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					cout << "horizontal curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
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
					//call the helper
					for (int i =0; i<9; i++) {
						for(int j = 0; j<9; j++) {
							cout << sudokuGrid[i][j]->value;
						}
						cout << endl;
					}
					int numAvailable_temp = findLCV_numAvailable (sudokuGrid, words, mcv->wordString);
					if (numAvailable_temp < curlcv.totalNumValAvailable) {
						curlcv.totalNumValAvailable = numAvailable_temp;
						curlcv.orientation = 'v';
					}
					cout << "vertical numAvailable_temp=" << numAvailable_temp << endl;
					//clear those values
					for (int curCharIdx=0; curCharIdx < mcv->wordString.size(); curCharIdx++)
						sudokuGrid[i+curCharIdx][j]->value = temp[curCharIdx];
					cout << "both curlcv.totalNumValAvailable=" << curlcv.totalNumValAvailable << endl;
					//for all posible lcv, push to the vector
					lcvVector.push_back(curlcv);
				}
				cout << endl;
			}
		}
	lcv leastConstrainingValue = lcvVector[0];
	for (int i=0; i < lcvVector.size() ; i++) {
		cout << "lcvVector[" << i << "] x=" <<lcvVector[i].x <<" y=" << lcvVector[i].y << " totalNumValAvailable=" << lcvVector[i].totalNumValAvailable <<endl;		
		if (lcvVector[i].totalNumValAvailable < leastConstrainingValue.totalNumValAvailable)
			leastConstrainingValue = lcvVector[i];
	}
	return leastConstrainingValue;
}

int findLCV_numAvailable (sudokuCell* sudokuGrid[9][9], vector<word*> words, string wordString) {
	int totalNumValAvailable = 0;
	for ( int curWordIdx = 0; curWordIdx <words.size(); curWordIdx++) {
		word * curWord = words[curWordIdx];
		// cout << "curWord=" << curWord->wordString << endl;
		if (curWord->wordString == wordString) //we only want other strings
			continue;
		// cout << "wordString=" <<wordString <<endl;
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
						totalNumValAvailable++;
					}
				}
			}
	}
	return totalNumValAvailable;
}