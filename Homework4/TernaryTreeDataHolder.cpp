#include "TernaryTreeDataHolder.h"

const size_t INITIAL_RESERVE = 3;

TernaryTreeDataHolder::TernaryTreeDataHolder(const char* filePath)
{
	int numberOfLevels = calculateLevels(filePath);
	if (numberOfLevels < 0)
	{
		throw std::logic_error("File not in valid state."); //opening and closing brackets aren't equal in numbers
	}

	treeLevels.resize(numberOfLevels);
	for (int i = 0; i < numberOfLevels; ++i)
	{
		treeLevels[i].reserve(INITIAL_RESERVE); //set to some arbitrary number
	}
	
	loadInformationFromFile(filePath);
}

//not *really* needed since std::vector will clean its own memory on destruct
//but I decided to add it for clarity
TernaryTreeDataHolder::~TernaryTreeDataHolder()
{
	size_t levels = treeLevels.size(); //avoiding some stack calls
	for (size_t i = 0; i < levels; ++i)
	{
		treeLevels[i].clear();
	}
	treeLevels.clear();
}

//amortised O(1), could be lowered to true O(1) if enough info
//is gathered from our input file via reserving enough space
//in each level of the tree, but I've opted not to do so
void TernaryTreeDataHolder::addElement(const size_t levelIdx, const char value)
{
	treeLevels[levelIdx].push_back(value);
}

//O(n) where n is equal to all elements of the tree
void TernaryTreeDataHolder::printWhole() const
{
	size_t dataHolderSize = treeLevels.size(); //avoiding some stack calls
	for (size_t i = 0; i < dataHolderSize; ++i)
	{
		size_t subLevelSize = treeLevels[i].size(); //avoiding some stack calls
		for (size_t j = 0; j < subLevelSize; ++j)
		{
			if (!treeLevels[i].empty())
			{
				std::cout << treeLevels[i][j];
			}
		}
		std::cout << std::endl;
	}
}

//O(n) where n is equal to all elements of the given level
void TernaryTreeDataHolder::printLevel(const size_t levelIdx) const
{
	if (levelIdx >= treeLevels.size() || levelIdx == 0)
	{
		std::cout << "No such level." << std::endl;
		return;
	}

	size_t levelLength = treeLevels[levelIdx].size(); //avoiding some stack calls
	for (size_t i = 0; i < levelLength; ++i)
	{
		std::cout << treeLevels[levelIdx][i];
	}
}

//O(n), where n is the length of all characters in input file
int TernaryTreeDataHolder::calculateLevels(const char* filePath)
{
	std::ifstream fileHandler(filePath);
	if (!fileHandler.is_open())
	{
		throw std::logic_error("Could not open file.");
	}

	char dump;
	int highestLevelReached = 0;
	int levels = 0;
	int bracketsCheck = 0;
	while (!fileHandler.eof())
	{
		fileHandler.get(dump);
		if (dump == '(')
		{
			++bracketsCheck;
			++levels;
			if (highestLevelReached < levels)
			{
				highestLevelReached = levels;
			}
		}
		else if (dump == ')')
		{
			--bracketsCheck;
			--levels;
		}
		else if (dump == '*' || dump == ' ')
		{
			continue;
		}
		dump = ' '; // Needed because of fileHandler.get(dump). Because of this I cannot use continue in all of the ifs, otherwise it would RIP my logic.
	}
	
	fileHandler.close();

	return bracketsCheck == 0 ? highestLevelReached : -1; //easier than writting more if statements
}

//When we're here, we've already reserved all the vectors of chars we would need
//all that is left is to parse the file properly and input each individual char
//into its respective "level", NOTE: this function could be merged with calculateLevels one,
//however, it would require me to resize my vectors at run-time not just once, but lots of times
//and I believe that having to re-allocate memory many times instead of just reading a file twice
//is significantly slower. I may be wrong on that, however.
void TernaryTreeDataHolder::loadInformationFromFile(const char* filePath)
{
	std::ifstream fileHandler(filePath);
	if (!fileHandler.is_open())
	{
		throw std::logic_error("Could not open file.");
	}

	char dump;
	int levels = 0;

	while (!fileHandler.eof())
	{
		fileHandler.get(dump);
		if (dump == '(')
		{
			++levels;
			
		}
		else if (dump == ')')
		{
			--levels;
		}
		else if (dump == '*' || dump == ' ')
		{
			continue;
		}
		else
		{
			addElement(levels - 1, dump);
		}

		dump = ' '; // Needed because of fileHandler.get(dump). Because of this I cannot use continue in all of the ifs, otherwise it would RIP my logic.
	}

	fileHandler.close();
}
