#ifndef __DANCER__
#define __DANCER__

#include <string>
#include <iostream>

class Dancer
{
private:
	std::string dancerName;
	Dancer* leftNeighbour;
	Dancer* rightNeighbour;
	bool holdingLeft;
	bool holdingRight;

public:
	Dancer();
	Dancer(const std::string&, Dancer*, Dancer*);
	~Dancer() = default;
	Dancer(const Dancer&) = delete;
	Dancer& operator=(const Dancer&) = delete;

public:
	bool getLeftHold()const { return holdingLeft; };
	bool getRightHold()const { return holdingRight; };
	Dancer* getLeftDancer() { return leftNeighbour; };
	Dancer* getRightDancer() { return rightNeighbour; };
	std::string getName()const { return dancerName; };
	void grabLeft(Dancer*);
	void grabRight(Dancer*);
	void releaseLeft();
	void releaseRight();
	void setNewName(const std::string&);
	void print()const;
};

#endif
