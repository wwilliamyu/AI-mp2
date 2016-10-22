#include "chess.h"

using namespace std;

void tree_construction(state curr, int depth, int player) {

	// given current state

	// player = 0 if white,
	// player = 1 if black

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
						state temp_state = curr;
						temp_state.board[y][x] = 2; // empty now
						temp_state.board[y-1][x] = 0; // white piece forward
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
			// for each white piece, judge 3 possible moves
				// NOTE : when create state, vector.push_back to vector next_states of curr_state
				// can go forward
					// if block above has piece in it, cannot move forward
					// else, create state for move forward

				// can go left diag
					// if block in left diag has white piece, cannot move
					// if block in left diag has black piece, can move & capture create state
					// if block in left diag has nothing, can move -> create state

				// can go right diag
					// if block in right diag has white piece, cannot move
					// if block in right diag has black piece, can move & capture
					// if block in right diag has nothing, can move

	}

	if (player == 1) {
		// black pieces only

		// iterate through board, if it's black piece, then investigate
	}
}
