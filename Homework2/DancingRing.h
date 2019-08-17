#ifndef __MY__HASH__
#define __MY__HASH__

#include <vector>
#include <fstream>
#include "Dancer.h"

const size_t MAX_LEN = 257;

class DancingRing
{
private:
	std::vector<Dancer*> dancers;
	std::vector<std::string> listOfDancerNames; //needed to store initial order of dancers from file
	size_t currSize;
	size_t capacity;
	bool end;

public:
	DancingRing(const char* fileName);
	~DancingRing();
	DancingRing& operator=(const DancingRing&) = delete; //intentional
	DancingRing(const DancingRing&) = delete; //intentional

public:
	void info(const std::string&)const;
	void add(const std::string&, const std::string&, const std::string&);
	void remove(const std::string&);
	void swap(const std::string&, const std::string&);
	void print()const;
	void grab(const std::string&, const std::string&);
	void release(const std::string&, const std::string&);
	bool getEnd()const { return end; };

private:
	size_t countNames(std::ifstream& fileHandler)const;
	size_t hashingFunction(const std::string&, size_t length)const;
	void fillRing(std::ifstream& fileHandler);
	void fixUpPointers();
};

#endif
