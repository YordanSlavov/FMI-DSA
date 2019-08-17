#ifndef TERNARY_TREE_DATA_HOLDER
#define TERNARY_TREE_DATA_HOLDER

#include <vector>
#include <iostream>
#include <fstream>

class TernaryTreeDataHolder
{
public:
	TernaryTreeDataHolder(const char*);
	~TernaryTreeDataHolder();

public:
	void printWhole()const;
	void printLevel(const size_t)const;

private:
	int calculateLevels(const char*);
	void loadInformationFromFile(const char*);
	void addElement(const size_t, const char);

private:
	//Vector of vectors of chars was chosen because
	//in reality I don't care one bit about the paret <-> child relationship in the tree
	//I only want to be able to print from left to right each "level" of the tree.
	//Vectors provide good data locallity and amortized O(1) insertion at end
	//which would be faster than any kind of tree that I know of (incl. RBTs, Fusion trees, etc.)
	//and it has the benefit of significantly less function due to no recursion compared to trees.
	//Still I considered the possibility of using an actual tree data structure, but due to the reasons above
	//and the fact that it is harder to implement than a vector the idea was quickly discarded.

	std::vector<std::vector<char>> treeLevels;
};

#endif
