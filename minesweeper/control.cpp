#include "control.h"

Control::Control()
{
	board = nullptr;
	size = -1;
}

Control::~Control()
{
	if (board != nullptr)
		delete board;
	board = nullptr;
	return;
}

void Control::startGame()
{
	cout << "*************Game Start*************" << endl;
	while (this->size < 3) {
		cout << "Input the size of game board(e.g Input 3 if 3x3 size needed):";
		cin >> this->size;
	}
	this->board = new Board(this->size);
	// initialize the gameboard
	this->board->assignRole();

	// store the action, flag or expose
	char choice = 'a';
	int x, y = -1;
												// the line below just for debug usage
	board->printBoard(true);
	while (board->checkGameContinue()) {
		board->printBoard();

		cout << "Input the action, [e] for expose; [f] for flag:" << endl;
		cin >> choice;
		cout << "Input the coordinate (x, y):" << endl;
		cin >> x;
		cin >> y;
		
		if ((choice != 'e' && choice != 'f') || (x < 0 || y < 0 || x >= size || y >= size)) {
			continue;
		}
		switch (choice) {
		case 'e': board->exposeBlock(x, y); break;
		case 'f': board->flagBlock(x, y); break;
		default: break;
		}
	}

	cout << "*************Game Start*************" << endl;
	if (board->getWin())
		cout << "*************You Win*************" << endl;
	else
		cout << "*************You lose*************" << endl;
	
}