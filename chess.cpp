#include "chess.h"

using namespace std;

void tree_construction(state curr, int depth, int player) {

	// given current state

	// player = 0 if white,
	// player = 1 if black

	// if reached leaf nodes, we are done
	if (depth == 0) {
		return;
	}

	if (player == 0) {
		// white pieces only

		// iterate through board, if it's white piece, then investigate

		for (int i = 0; i < 8, i++) {
			for (int j = 0; j < 8; j++) {
				// for each white piece, judge 3 possible moves
				if (board[y][x] == 0) {
					// check cell directly up
					if (board[y-1][x] == 2) {
						// can move forward
						state temp = curr;
						temp.board[y][x] = 2; // empty now
						temp.board[y-1][x] = 0; // white piece forward

						curr.next_states.push_back(temp); // add to next level

						// create state
					} // else cannot create move forward, so do not create state

					// check cell left diagonal
					if (board[y-1][x-1] == 0) {
						// left diag is white
						// cannot move
					}
					else if (board[y-1][x-1] == 1) {
						// left diag is black
						// capture, and move
					}
					else /* empty */ {
						// left diag is empty
						// move
					}

					// check cell right diagonal
					if (board[y-1][x+1] == 0) {

					}
					else if (board[y-1][x+1] == 0) {

					}
					else {

					}
					// NOTE : when create state, vector.push_back to vector next_states of curr_state
					// can go forward

				}
			}
		}
	}

	if (player == 1) {
		// black pieces only

		// iterate through board, if it's black piece, then investigate
	}

	// for each of the next states, run recursive function on them
	for (int a = 0; a < curr.next_states.size(); a++) {

		tree_construction(curr.next_states[a], depth - 1, );
	}
}


