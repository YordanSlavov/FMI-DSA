#include "Dancer.h"

void Dancer::grabLeft(Dancer* left)
{
	leftNeighbour = left;
	holdingLeft = true;
}

void Dancer::grabRight(Dancer* right)
{
	rightNeighbour = right;
	holdingRight = true;
}

void Dancer::releaseLeft()
{
	holdingLeft = false;
}

void Dancer::releaseRight()
{
	holdingRight = false;
}

void Dancer::setNewName(const std::string& newName)
{
	dancerName = newName;
}

void Dancer::print() const
{
	std::cout << dancerName;
}

Dancer::Dancer()
	: dancerName("")
	, leftNeighbour(nullptr)
	, rightNeighbour(nullptr)
	, holdingLeft(false)
	, holdingRight(false)
{
}

Dancer::Dancer(const std::string& name, Dancer* left, Dancer* right)
	: dancerName(name)
	, leftNeighbour(left)
	, rightNeighbour(right)
	, holdingLeft(false)
	, holdingRight(false)
{
}
