#include "board.h"

Board::Board(int size)
{
	this->size = size;
	this->blocksLeft = size * size;
	this->boomNum = size * size / 5;
	this->flagLeft = this->boomNum;
	this->gameContinue = true;

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

int Board::findBoom(int x, int y){
	int count = 0;
	for(int i = y-1; i >= y+1; i++){
		if(i < 0 || i >= this->size) continue;
		for(int j = x-1; j >= x+1; j++){
			if(j < 0 || j >= this->size) continue;
			if(board[i][j]->getRole() == -1){
				count++;
			}
		}
	}
	return count;
}
