#include "DancingRing.h"



//Constructor job is rather lengthy but after it
//things should be O(1)/amortised O(1) aside from print
DancingRing::DancingRing(const char* fileName)
	: currSize(0)
	, capacity(0)
	, end(false)
{
	std::ifstream fileHandler(fileName);
	if (!fileHandler.is_open())
	{
		throw std::logic_error("Could not open file.");
	}

	size_t elements = countNames(fileHandler);
	//saving some extra space in order to speed things up initially
	dancers.reserve(elements * 2);
	capacity = dancers.capacity();
	Dancer* temp = nullptr;
	for (size_t i = 0; i < capacity; ++i)
	{
		dancers.push_back(temp);
	}

	fillRing(fileHandler);

	fileHandler.close();
}

DancingRing::~DancingRing()
{
	for (std::vector<Dancer*>::iterator it = dancers.begin(); it != dancers.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}
}

void DancingRing::info(const std::string& dancerName) const
{
	size_t index = hashingFunction(dancerName, dancerName.size());
	if (dancers[index] != nullptr)
	{
		if (dancers[index]->getLeftDancer() != nullptr && dancers[index]->getRightDancer() != nullptr) 
		{
			std::cout << dancers[index]->getLeftDancer()->getName();
			if (dancers[index]->getLeftDancer()->getRightHold() == false && dancers[index]->getLeftHold() == false)
			{
				std::cout << " ---- " << dancers[index]->getName();
			}
			else if (dancers[index]->getLeftDancer()->getRightHold() == false && dancers[index]->getLeftHold() == true)
			{
				std::cout << " <--- " << dancers[index]->getName();
			}
			else if (dancers[index]->getLeftDancer()->getRightHold() == true && dancers[index]->getLeftHold() == false)
			{
				std::cout << " ---> " << dancers[index]->getName();
			}
			else //  dancers[index]->getLeftDancer()->getRightHold() == true && dancers[index]->getLeftHold() == true
			{
				std::cout << " <--> " << dancers[index]->getName();
			}

			if (dancers[index]->getRightDancer()->getLeftHold() == false && dancers[index]->getRightHold() == false)
			{
				std::cout << " ---- " << dancers[index]->getRightDancer()->getName();
			}
			else if (dancers[index]->getRightDancer()->getLeftHold() == false && dancers[index]->getRightHold() == true)
			{
				std::cout << " ---> " << dancers[index]->getRightDancer()->getName();
			}
			else if (dancers[index]->getRightDancer()->getLeftHold() == true && dancers[index]->getRightHold() == false)
			{
				std::cout << " <--- " << dancers[index]->getRightDancer()->getName();
			}
			else //  dancers[index]->getRightDancer()->getLeftHold() == true && dancers[index]->getRightHold() == true
			{
				std::cout << " <--> " << dancers[index]->getRightDancer()->getName();
			}

		}
		else 
		{
			//there's no specific instruction on what to do when there is(are) no left/right neighbour(s)
			std::cout << "Missing neighbour." << std::endl;
			return;
		}
	}
}

void DancingRing::add(const std::string& newDancer, const std::string& leftDancer, const std::string& rightDancer)
{
	if (currSize >= capacity)
	{
		std::cout << "No more room in the dancing circle." << std::endl;
		return;
	}

	size_t newDancerIndex = hashingFunction(newDancer, newDancer.size());
	size_t leftDancerIndex = hashingFunction(leftDancer, leftDancer.size());
	size_t rightDancerIndex = hashingFunction(rightDancer, rightDancer.size());

	if (dancers[newDancerIndex] == nullptr &&
		dancers[leftDancerIndex]->getRightDancer() == dancers[rightDancerIndex] &&
		dancers[rightDancerIndex]->getLeftDancer() == dancers[leftDancerIndex])
	{
		dancers[newDancerIndex] = new Dancer(newDancer, dancers[leftDancerIndex], dancers[rightDancerIndex]);
		dancers[newDancerIndex]->grabLeft(dancers[leftDancerIndex]);
		dancers[newDancerIndex]->grabRight(dancers[rightDancerIndex]);
		dancers[leftDancerIndex]->grabRight(dancers[newDancerIndex]);
		dancers[rightDancerIndex]->grabLeft(dancers[newDancerIndex]);
		++currSize;
	}
	else
	{
		std::cout << "Could not add dancer." << std::endl;
		return;
	}
}

void DancingRing::remove(const std::string& dancerName)
{
	size_t index = hashingFunction(dancerName, dancerName.size());
	if (dancers[index] != nullptr)
	{
		if (dancers[index]->getLeftHold() == false && dancers[index]->getRightHold() == false &&
			dancers[index]->getLeftDancer()->getRightHold() == false &&
			dancers[index]->getRightDancer()->getLeftHold() == false)
		{
			dancers[index]->getLeftDancer()->grabRight(dancers[index]->getRightDancer()); //rightHold = true
			dancers[index]->getRightDancer()->grabLeft(dancers[index]->getLeftDancer()); //leftHold = true
			delete dancers[index];
			dancers[index] = nullptr;
			std::cout << "Free at last!" << std::endl;
			--currSize;
			if (currSize == 2)
			{
				end = true;
				std::cout << "...and the music stops!" << std::endl;
				return;
			}
		}
		else
		{
			std::cout << "This won't be so easy!" << std::endl;
		}
	}
}

void DancingRing::swap(const std::string& dancerOne, const std::string& dancerTwo)
{
	size_t indexOne = hashingFunction(dancerOne, dancerOne.size()); //A
	size_t indexTwo = hashingFunction(dancerTwo, dancerTwo.size()); //B
	//								if B is to the left of A and A to the right of B;  B ---- A
	if ((dancers[indexOne]->getLeftDancer() == dancers[indexTwo] && dancers[indexTwo]->getRightDancer() == dancers[indexOne]))
	{
		//									is anyone holding either of them/they're holding anyone else
		if (dancers[indexOne]->getLeftHold() == false && dancers[indexOne]->getRightHold() == false && dancers[indexOne]->getRightDancer()->getLeftHold() == false &&
			dancers[indexTwo]->getRightHold() == false && dancers[indexTwo]->getLeftHold() == false && dancers[indexTwo]->getLeftDancer()->getRightHold() == false)
		{
			Dancer* leftNeighbourIdxTwo = dancers[indexTwo]->getLeftDancer();
			Dancer* rightNeighbourIdxOne = dancers[indexOne]->getRightDancer();
			dancers[indexOne]->grabLeft(leftNeighbourIdxTwo);
			dancers[indexOne]->grabRight(dancers[indexTwo]);
			dancers[indexTwo]->grabLeft(dancers[indexOne]);
			dancers[indexTwo]->grabRight(rightNeighbourIdxOne);
			leftNeighbourIdxTwo->grabRight(dancers[indexOne]);
			rightNeighbourIdxOne->grabLeft(dancers[indexTwo]);
		}
	}
	//								if A is to the left of B and B to the right of A;  A ---- B
	else if ((dancers[indexOne]->getRightDancer() == dancers[indexTwo] && dancers[indexTwo]->getLeftDancer() == dancers[indexOne]))
	{
		//									is anyone holding either of them/they're holding anyone else
		if (dancers[indexOne]->getRightHold() == false && dancers[indexOne]->getLeftHold() == false && dancers[indexOne]->getLeftDancer()->getRightHold() == false &&
			dancers[indexTwo]->getLeftHold() == false && dancers[indexTwo]->getRightHold() == false && dancers[indexTwo]->getRightDancer()->getLeftHold() == false)
		{
			Dancer* leftNeighbourIdxOne = dancers[indexOne]->getLeftDancer();
			Dancer* rightNeighbourIdxTwo = dancers[indexTwo]->getRightDancer();
			dancers[indexOne]->grabRight(rightNeighbourIdxTwo);
			dancers[indexOne]->grabLeft(dancers[indexTwo]);
			dancers[indexTwo]->grabLeft(leftNeighbourIdxOne);
			dancers[indexTwo]->grabRight(dancers[indexOne]);
			rightNeighbourIdxTwo->grabLeft(dancers[indexOne]);
			leftNeighbourIdxOne->grabRight(dancers[indexTwo]);
		}
	}

	return;	
}

void DancingRing::print() const
{
	size_t startingFrom;
	size_t counterForInitialMembers = 0;
	size_t howMany = currSize;
	for (size_t i = 0; i < dancers.size(); ++i)
	{
		//looking for non-removed dancers from initial file since they're saved in order
		startingFrom = hashingFunction(listOfDancerNames[i], listOfDancerNames[i].size());
		if (dancers[startingFrom] != nullptr) //found one, will start printing from it and to the "right"
		{
			break;
		}
		++counterForInitialMembers;
	}

	if (counterForInitialMembers == currSize) //the dancers from file have all been removed
	{
		for (size_t i = 0; i < currSize; ++i)
		{
			if (dancers[i] != nullptr)
			{
				dancers[i]->print(); //will not print them in oreder, but keeping order would be rather hard
			}
		}
		return;
	}
	
	while (dancers[startingFrom]->getRightDancer() != nullptr && howMany != 0)
	{
		dancers[startingFrom]->print();
		startingFrom = hashingFunction(dancers[startingFrom]->getRightDancer()->getName(), dancers[startingFrom]->getRightDancer()->getName().size());
		std::cout << std::endl;
		--howMany;
	}	
}

void DancingRing::grab(const std::string& dancerName, const std::string& leftRightBoth)
{
	size_t index = hashingFunction(dancerName, dancerName.size());
	if (dancers[index] != nullptr)
	{
		if (leftRightBoth == "both")
		{
			if (dancers[index]->getLeftDancer() != nullptr && dancers[index]->getRightDancer() != nullptr)
			{
				dancers[index]->grabLeft(dancers[index]->getLeftDancer());
				dancers[index]->grabRight(dancers[index]->getRightDancer());
			}
		}
		else if (leftRightBoth == "left")
		{
			if (dancers[index]->getLeftDancer() != nullptr)
			{
				dancers[index]->grabLeft(dancers[index]->getLeftDancer());
			}
		}
		else //leftRightBoth == "right"
		{
			if (dancers[index]->getRightDancer() != nullptr)
			{
				dancers[index]->grabRight(dancers[index]->getRightDancer());
			}
		}
	}
}

void DancingRing::release(const std::string& dancerName, const std::string& leftRightBoth)
{
	size_t index = hashingFunction(dancerName, dancerName.size());
	if (dancers[index] != nullptr)
	{
		if (leftRightBoth == "both")
		{
			if (dancers[index]->getLeftDancer() != nullptr && dancers[index]->getRightDancer() != nullptr)
			{
				dancers[index]->releaseLeft();
				dancers[index]->releaseRight();
			}
		}
		else if (leftRightBoth == "left")
		{
			if (dancers[index]->getLeftDancer() != nullptr)
			{
				dancers[index]->releaseLeft();
			}
		}
		else //leftRightBoth == "right"
		{
			if (dancers[index]->getRightDancer() != nullptr)
			{
				dancers[index]->releaseRight();
			}
		}
	}
}

size_t DancingRing::countNames(std::ifstream& fileHandler)const
{
	size_t nameCounter = 0;
	char dump[257];
	while (!fileHandler.eof())
	{
		fileHandler.getline(dump, MAX_LEN, '\n');
		++nameCounter;
	}

	fileHandler.seekg(0, std::ios::beg);
	return nameCounter;
}

void DancingRing::fillRing(std::ifstream& fileHandler)
{
	char dumpName[MAX_LEN];
	listOfDancerNames.reserve(currSize);
	while (!fileHandler.eof())
	{
		fileHandler.getline(dumpName, MAX_LEN, '\n');
		size_t position = hashingFunction(dumpName, strlen(dumpName));
		//To reiterate, O(1) across the board
		//is NOT achievable if I do not assume
		//that the hashing function will always give a unique index
		//in practice this is not actually possible given enough key values
		if (dancers[position] == nullptr)
		{
			dancers[position] = new Dancer(dumpName, nullptr, nullptr);
			listOfDancerNames.push_back(dumpName);
			++currSize;
		}
		else
		{
			std::logic_error("The file cannot have 2 people with the same name.");
		}
	}
	fixUpPointers();
}

void DancingRing::fixUpPointers()
{
	//when this point is reached, my dancers are partially created
	//they're in my make-shift hash/linked-list, however, their "neighbours"
	//are still nullptrs

	size_t currentHashedPosition;
	size_t forwardHashedPosition;
	//having all dancers grab one another from left to right
	for (size_t i = 0; i < currSize - 1; ++i)
	{
		currentHashedPosition = hashingFunction(listOfDancerNames[i], listOfDancerNames[i].size());
		forwardHashedPosition = hashingFunction(listOfDancerNames[i + 1], listOfDancerNames[i + 1].size());
		dancers[currentHashedPosition]->grabRight(dancers[forwardHashedPosition]);
	}
	//having all dancers grab one another from right to left
	for (size_t i = currSize - 1; i > 0; --i)
	{
		currentHashedPosition = hashingFunction(listOfDancerNames[i], listOfDancerNames[i].size());
		forwardHashedPosition = hashingFunction(listOfDancerNames[i - 1], listOfDancerNames[i - 1].size());
		dancers[currentHashedPosition]->grabLeft(dancers[forwardHashedPosition]);
	}
	//having the first and last dancer from our text file grab one another to form the "circle"
	currentHashedPosition = hashingFunction(listOfDancerNames[0], listOfDancerNames[0].size());
	forwardHashedPosition = hashingFunction(listOfDancerNames[currSize - 1], listOfDancerNames[currSize - 1].size());
	dancers[currentHashedPosition]->grabLeft(dancers[forwardHashedPosition]);
	dancers[forwardHashedPosition]->grabRight(dancers[currentHashedPosition]);
}

//Taken from https://www.partow.net/programming/hashfunctions/#StringHashing
//It's the first function shown (00 - RS Hash Function)
//Has been modified slightly in order to be compatible with my class
//I assume that this will make due for no collisions, otherwise 
//O(1) run-time is not possible for the given task
//Additionally this hashing function isn't even that quick
size_t DancingRing::hashingFunction(const std::string& str, size_t length)const
{
	size_t b = 378551;
	size_t a = 63689;
	size_t hash = 0;

	for (size_t i = 0; i < length; ++i)
	{
		hash = hash * a + (size_t)str[i];
		a = a * b;
	}

	return hash % capacity;
}
