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
	int dif = -1;
	while (dif < 1 || dif >4) {
		cout << "Input the difficulty [1-4], 1 is most difficult:";
		cin >> dif;
	}
	this->board = new Board(this->size, dif);
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
		cout << "e x y [or] f x y(enter) [where x, y are coordinate]:";
		cin >> choice;
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
		board->checkBlockLeft();
	}
	board->printBoard(true);
	cout << "*************Game Start*************" << endl;
	if (board->getWin())
		cout << "*************You Win*************" << endl;
	else
		cout << "*************You lose*************" << endl;
	
}
