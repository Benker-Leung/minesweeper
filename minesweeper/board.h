#pragma once
#ifndef BOARD_H_
#define BOARD_H_

#include "block.h"


class Board {

private:

	Block **block;		// a block pointer storing a 2-Dimension array of blocks
	int size;			// storing size of the board, the total blocks are size*size
	int blocksLeft;		// storing the number of blocks which are not exposed
	int boomNum;		// storing the number of boom, also the total flag which the player have in total, set boomNum be 1/5 of the total blocks
	int flagLeft;		// storing the number of flags where the player can use
	bool gameContinue;	// a bool to store game status, it is false if gameover
	bool win;			// true if win

public:

	// constructor, only create the varible required but not assigning role yet
	Board(int size);
	// destructor, delete all dynamic allocated memories in this class
	~Board();

	// find the number of boom nearby of a particular block, including itself if it is a boom
	int findBoom(int x, int y);

	// assign the Role(boom, empty, number) for the blocks, return true if success
	bool assignRole();

	// flag the block and return true if it can be flagged
	bool flagBlock(int x, int y);

	// expose a block and return true if it can be exposed
	bool exposeBlock(int x, int y);

	// check the game is continue or not, return false if gameover
	bool checkGameContinue();

	// print the game board, send true if print all the block even not exposed
	void printBoard(bool printAll=false);

	// get win or lose
	bool getWin();

	// expose nearby block excepty booms
	void exposeNearby(int x, int y);

};

#endif