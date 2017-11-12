#include "block.h"

Block::Block()
{
	this->x = -1;
	this->y = -1;
	this->role = -2;
	this->flagged = false;
	this->exposed = false;
}

Block::~Block()
{
	return;
}

bool Block::assignCoordinate(int x, int y)
{
	this->x = x;
	this->y = y;
	return false;
}

bool Block::assignRole(int role)
{
	if (role < -1)
		return false;
	this->role = role;
	return true;
}

bool Block::setFlagged(bool flag)
{
	if (this->flagged && flag == true)
		return false;
	else if (!this->flagged && flag == false)
		return false;
	this->flagged = flag;
	return true;
}

bool Block::setExposed()
{
	if (this->exposed)
		return false;
	this->exposed = true;
	return true;
}

int Block::getX()
{
	return this->x;
}

int Block::getY()
{
	return this->y;
}

int Block::getRole()
{
	return this->role;
}

bool Block::getFlagged()
{
	return this->flagged;
}

bool Block::getExposed()
{
	return this->exposed;
}

