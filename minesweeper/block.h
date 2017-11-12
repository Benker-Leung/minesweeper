#pragma once

#ifndef BLOCK_H_
#define BLOCK_H_

class Block {	//hi

private:

	int x;							// x-coordinate, default is -1
	int y;							// y-cooddinate, default is -1
	int role;						// 0 is blank, -1 is boom, number >=1 indicate the boom nearby, default is -2
	bool flagged;					// store the status of the block, flag or not, default is false(not flagged)
	bool exposed;					// sotre the block is exposed or not, default is false(not exposed)


public:

	// constructor
	Block();
	// destructor
	~Block();


	// assign x,y coordinate of block, return true if assign success
	bool assignCoordinate(int x, int y);

	// assign role of the block, (blank,0) (boom,-1) (number >=1 for non-boom and non-empty), return true if assign success
	bool assignRole(int role);

	// set the block is flagged or not, true for flagged
	bool setFlagged(bool flag);

	// set the block is exposed or not, true for exposed
	bool setExposed(bool expose);

	// return the x-coordinate
	int getX();

	// return the y-coordinate
	int getY();

	// return the role, (blank,0) (boom,-1) (number >=1 for non-boom and non-empty)
	int getRole();

	// return the block is flagged or not, true for flagged
	bool getFlagged();

	// return the block is exposed or not, true for exposed
	bool getExposed();

};



#endif