#pragma once
#ifndef CONTROL_H_
#define CONTROL_H_

#include "board.h"
#include "utils.h"

class Control {

private:

	Board *board;		// store the game-board
	int size;

public:

	// constructor
	Control();
	// destructor
	~Control();

	void startGame();

};



#endif