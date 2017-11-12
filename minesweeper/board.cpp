#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "utils.h"

Board::Board(int size)
{
	srand(time(NULL));
	this->size = size;
	this->blocksLeft = size * size;
	this->boomNum = size * size / 6;
	this->flagLeft = this->boomNum;
	this->gameContinue = true;
	this->win = false;

	this->block = new Block*[size];
	for (int i = 0; i < size; i++) {
		this->block[i] = new Block[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			block[i][i].assignCoordinate(i, j);
		}
	}
}

Board::~Board()
{
	if (this->block != nullptr) {
		for (int i = 0; i < this->size; i++) {
			if (this->block[i] != nullptr) {
				delete[]this->block[i];
			}
		}
		delete[]this->block;
	}
}

int Board::findBoom(int x, int y)
{
	int boomCount = 0;
	int startX = x - 1;		//starting position of checking
	int startY = y - 1;		//starting position of checking
	for (int i = 0; i < 9; i++) {
		startX = (x - 1) + i / 3;
		startY = (y - 1) + i % 3;
		// if out of bound, check next term
		if (startX < 0 || startY < 0 || startX >= this->size || startY >= this->size)
			continue;
		// if the block is -1(boom), count++
		if (block[startX][startY].getRole() == -1)
			boomCount++;
	}
	return boomCount;
}

bool Board::assignRole()
{
	// store the boom require randomly assign
	int boomLeft = boomNum;
	int randX;
	int randY;
	while (boomLeft) {
		randX = rand() % size;
		randY = rand() % size;
		// if the block is already boom, generate another
		if (this->block[randX][randY].getRole() == -1) {
			continue;
		}
		else {
			this->block[randX][randY].assignRole(-1);
			boomLeft--;
		}
	}
	// assign role for other block if it is not boom
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->block[i][j].getRole() == -1)
				continue;
			else{
				this->block[i][j].assignRole(findBoom(i, j));
			}
		}
	}

	return true;
}

bool Board::flagBlock(int x, int y)
{
	// return false if no flag can be used
	if (!flagLeft)
		return false;

	// return false if the block is exposed
	if (this->block[x][y].getExposed())
		return false;

	this->block[x][y].setFlagged(true);
	this->flagLeft--;
	return true;
}

bool Board::exposeBlock(int x, int y)
{
	// if the block is already exposed, return false
	if (this->block[x][y].getExposed())
		return false;

	// if the block is already flagged, return false
	if (this->block[x][y].getFlagged())
		return false;

	this->block[x][y].setExposed();
	this->blocksLeft--;
	// if the exposed block is boom, then gameover
	if (this->block[x][y].getRole() == -1)
		gameContinue = false;
	if (this->boomNum + this->blocksLeft == this->size*this->size)
		win = true;
	return true;
}

bool Board::checkGameContinue()
{
	return gameContinue;
}

void Board::printBoard(bool printAll)
{

	if (this->block == nullptr)
		return;

	//gameboard
	int tempSize = 1;

	if (this->size >= 10)
		tempSize = size/2 - 4;

	//---GAME BOARD---
	for (int i = 0; i < tempSize; i++) {
		cout << '-';
	}
	cout << "GAME BOARD";
	for (int i = 0; i < tempSize; i++) {
		cout << '-';
	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->block[i][j].getExposed() || printAll)
				switch (this->block[i][j].getRole()) {
				case 0:	cout << "  "; break;
				case -1: cout << "X "; break;
				default: cout << this->block[i][j].getRole() << " "; break;
				}
			else
				cout << "? ";
		}
		cout << endl;
	}

	//---GAME BOARD---
	for (int i = 0; i < tempSize; i++) {
		cout << '-';
	}
	cout << "GAME BOARD";
	for (int i = 0; i < tempSize; i++) {
		cout << '-';
	}
	cout << endl;
}

bool Board::getWin()
{
	return this->win;
}

