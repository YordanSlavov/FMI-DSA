#include "DancingRing.h"

void menuFunction(DancingRing& myDancingRing, char* buffer)
{
	char dancer[MAX_LEN];
	char leftDancer[MAX_LEN];
	char rightDancer[MAX_LEN];

	while (!myDancingRing.getEnd())
	{
		std::cin.getline(buffer, MAX_LEN);
		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}
		else if (strcmp(buffer, "remove") == 0)
		{
			std::cin.getline(dancer, MAX_LEN);
			if (dancer != "")
			{
				myDancingRing.remove(dancer);
			}
			std::cout << std::endl;
		}
		else if (strcmp(buffer, "add") == 0)
		{
			std::cin.getline(dancer, MAX_LEN);
			std::cin.getline(leftDancer, MAX_LEN);
			std::cin.getline(rightDancer, MAX_LEN);
			if (dancer != "" && leftDancer != "" && rightDancer != "")
			{
				myDancingRing.add(dancer, leftDancer, rightDancer);
			}
			std::cout << std::endl;
		}
		else if (strcmp(buffer, "info") == 0)
		{
			std::cin.getline(dancer, MAX_LEN);
			if (dancer != "")
			{
				myDancingRing.info(dancer);
			}
			std::cout << std::endl;
		}
		else if (strcmp(buffer, "print") == 0)
		{
			myDancingRing.print();
			std::cout << std::endl;
		}
		else if (strcmp(buffer, "grab") == 0)
		{
			std::cin.getline(dancer, MAX_LEN);
			std::cin.getline(leftDancer, MAX_LEN); //otherDancer would've been more fitting, but no need to create more buffers
			if (dancer != "" && leftDancer != "")
			{
				myDancingRing.grab(dancer, leftDancer);
			}
			std::cout << std::endl;
		}
		else if (strcmp(buffer, "release") == 0)
		{
			std::cin.getline(dancer, MAX_LEN);
			std::cin.getline(leftDancer, MAX_LEN);
			myDancingRing.release(dancer, leftDancer);
			std::cout << std::endl;
		}
		else if (strcmp(buffer, "swap") == 0)
		{
			std::cin.getline(dancer, MAX_LEN);
			std::cin.getline(leftDancer, MAX_LEN);
			if (dancer != "" && leftDancer != "")
			{
				myDancingRing.swap(dancer, leftDancer);
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Invalid command." << std::endl;
			continue;
		}
	}
}

int main()
{
	std::cout << "\\\\\\\\ INSTRUCTIONS ////" << std::endl;
	std::cout << "THE FIRST INPUT OF THE PROGRAM IS THE FILE PATH" << std::endl;
	std::cout << "SOMETIMES A FILE PATH WILL NOT BE RECOGNIZED BY THE PROGRAM" << std::endl;
	std::cout << "AND IS AN ERROR THAT I CANNOT REPRODUCE OR REMOVE, IT MAY JUST BE SOMETHIG ON MY END" << std::endl;
	std::cout << "THE PROGRAM EXPECTS EACH COMMAND TO BE WRITTEN ON A NEW LINE" << std::endl;
	std::cout << "ALL ARGUMENTS PASSED AFTER A FUNCTION IS CALLED MUST ALSO BE ON A NEW LINE" << std::endl;
	std::cout << "holdLeft && holdRight ARE INTENTIONALLY SET TO TRUE UPON REMOVAL/ADDITION TO DANCING CIRCLE" << std::endl;
	std::cout << "NOTE THAT CONFLICTS FROM HASH FUNCTION WILL NOT BE ALLOWED, THIS IS INTENTIONAL FOR O(1)" << std::endl;
	std::cout << "//// END OF INSTRUCTIONS \\\\\\\\" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	

	char buffer[MAX_LEN];
	std::cin.getline(buffer, MAX_LEN);

	DancingRing myDancingRing((const char*)buffer);
		
	menuFunction(myDancingRing, (char*)buffer);
	

	return 0;
}
