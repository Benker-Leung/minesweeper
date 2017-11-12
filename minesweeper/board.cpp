#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "utils.h"

Board::Board(int size, int dif)
{
	srand(time(NULL));
	this->size = size;
	this->blocksLeft = size * size;
	this->difficulty = dif;
	this->boomNum = size * size / (dif*8);
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

	// if the block is flagged, then unflag it
	if (this->block[x][y].getFlagged()) {
		block[x][y].setFlagged(false);
		flagLeft++;
	}
	else {
		this->block[x][y].setFlagged(true);
		this->flagLeft--;
	}
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
	// if the exposed block is boom, then gameover
	if (this->block[x][y].getRole() == -1) {
		gameContinue = false;
		win = false;
	}
	if (this->block[x][y].getRole() == 0)
		exposeNearby(x, y);
	return true;
}

bool Board::checkGameContinue()
{
	if (blocksLeft == 0 && flagLeft == 0) {
		gameContinue = false;
		win = true;
	}
	return gameContinue;
}

void Board::printBoard(bool printAll)
{

	if (this->block == nullptr)
		return;

	int m = 5;

	//---GAME BOARD---
	cout << endl;
	for (int i = 0; i < size*m; i++) {
		cout << '-';
	}
	cout << "GAME  BOARD";
	for (int i = 0; i < size*m; i++) {
		cout << '-';
	}
	cout << endl;

	// pinrt the x-coordinate
	cout << "\t";
	for (int i = 0; i < size; i++) {
		cout << i << "\t";
	}
	cout << endl << "\t";
	for (int i = 0; i < size; i++) {
		cout << "-\t";
	}
	cout << endl;
	// end of printing x-coordinate

	for (int i = 0; i < size; i++) {
		// print the y-coordinate
		cout << i << "|\t";
		for (int j = 0; j < size; j++) {
			if (this->block[i][j].getFlagged()) {
				cout << "F\t";
				continue;
			}
			if (this->block[i][j].getExposed() || printAll) {
				switch (this->block[i][j].getRole()) {
				case 0:	cout << " \t"; break;
				case -1: cout << "X\t"; break;
				default: cout << this->block[i][j].getRole() << "\t"; break;
				}
			}
			else
				cout << "?\t";
		}
		cout << " |" << i << endl;
	}

	// pinrt the x-coordinate
	cout << "\t";
	for (int i = 0; i < size; i++) {
		cout << "-\t";
	}
	cout << endl << "\t";
	for (int i = 0; i < size; i++) {
		cout << i << "\t";
	}
	cout << endl;
	// end of printing x-coordinate


	// print some information
	cout << endl;
	for (int i = 0; i < size*m; i++) {
		cout << '-';
	}
	cout << "INFORMATION";
	for (int i = 0; i < size*m; i++) {
		cout << '-';
	}
	cout << endl;
	cout << "\tFlag lefted: " << this->flagLeft << " | Blocks Left: " << this->blocksLeft << endl;

	// end of printing some information

	//---GAME BOARD---
	for (int i = 0; i < size*m; i++) {
		cout << '-';
	}
	cout << "GAME  BOARD";
	for (int i = 0; i < size*m; i++) {
		cout << '-';
	}
	cout << endl << endl;

	/* the following is the one do not use /t*/
	/*
	void Board::printBoard(bool printAll)
{

	if (this->block == nullptr)
		return;


	//---GAME BOARD---
	for (int i = 0; i < size; i++) {
		cout << '-';
	}
	cout << "GAME BOARD";
	for (int i = 0; i < size; i++) {
		cout << '-';
	}
	cout << endl;

	// pinrt the x-coordinate
	cout << "  ";
	for (int i = 0; i < size; i++) {
		cout << i << " ";
	}
	cout << endl << "  ";
	for (int i = 0; i < size; i++) {
		cout << "- ";
	}
	cout << endl;
	// end of printing x-coordinate

	for (int i = 0; i < size; i++) {
		// print the y-coordinate
		cout << i << "|";
		for (int j = 0; j < size; j++) {
			if (this->block[i][j].getFlagged()) {
				cout << "F ";
				continue;
			}
			if (this->block[i][j].getExposed() || printAll) {
				switch (this->block[i][j].getRole()) {
				case 0:	cout << "  "; break;
				case -1: cout << "X "; break;
				default: cout << this->block[i][j].getRole() << " "; break;
				}
			}
			else
				cout << "? ";
		}
		cout << " |" << i << endl;
	}

	// pinrt the x-coordinate
	cout << "  ";
	for (int i = 0; i < size; i++) {
		cout << "- ";
	}
	cout << endl << "  ";
	for (int i = 0; i < size; i++) {
		cout << i << " ";
	}
	cout << endl;
	// end of printing x-coordinate

	//---GAME BOARD---
	for (int i = 0; i < size; i++) {
		cout << '-';
	}
	cout << "GAME BOARD";
	for (int i = 0; i < size; i++) {
		cout << '-';
	}
	cout << endl;
}
	*/
}

bool Board::getWin()
{
	return this->win;
}

void Board::exposeNearby(int x, int y)
{

	int startX = x - 1;		//starting position of exposing
	int startY = y - 1;		//starting position of exposing
	for (int i = 0; i < 9; i++) {
		startX = (x - 1) + i / 3;
		startY = (y - 1) + i % 3;
		// if out of bound, check next term
		if (startX < 0 || startY < 0 || startX >= this->size || startY >= this->size)
			continue;
		// if the block is -1(boom), do not expose
		if (block[startX][startY].getRole() == -1)
			continue;
		// if the block exposed successfully and it is blank, then continue expose
		bool success = block[startX][startY].setExposed();
		if (block[startX][startY].getRole() == 0 && success)
			exposeNearby(startX, startY);
	}
	return;
}

void Board::checkBlockLeft()
{
	int temp = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (block[i][j].getExposed() || block[i][j].getFlagged())
				temp++;
		}
	}
	blocksLeft = size*size - temp;
}

int Board::getFlagLeft()
{
	return flagLeft;
}

int Board::getBlockLeft()
{
	return blocksLeft;
}

