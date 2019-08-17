#include "TernaryTreeDataHolder.h"

const size_t MAX_LEN = 257;

void menuFunction(const TernaryTreeDataHolder& myDataHolder)
{
	char inputBuffer[MAX_LEN];
	while (true)
	{
		std::cout << "Input a command ('print', 'exit', 'print level')" << std::endl;
		std::cin.getline(inputBuffer, MAX_LEN);
		if (strcmp(inputBuffer, "exit") == 0)
		{
			std::cout << "You've exited the program." << std::endl;
			return;
		}
		else if (strcmp(inputBuffer, "print") == 0)
		{
			myDataHolder.printWhole();
		}
		else if (strcmp(inputBuffer, "print level") == 0)
		{
			std::cout << "Enter the level you would like to see." << std::endl;
			size_t level;
			std::cin >> level;
			myDataHolder.printLevel(level - 1);
			std::cin.ignore(1);
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
	std::cout << "LEVELS ARE EXPECTED IN THE RANGE [1, N]." << std::endl;
	std::cout << "GIVING A LEVEL VALUE OF 0 OR GREATER THAN N WILL BRING YOU BACK TO THE MENU." << std::endl;
	std::cout << "ALSO MAKE SURE THAT THE INPUT FILE HAS APPROPRIATE BRACKETS OR YOU WILL RECEIVE AN ERROR." << std::endl;
	std::cout << "AN EMPTRY TREE (*) WILL BE LOADED, COMMANDS WILL WORK, HOWEVER, IT WILL NOT BE PRINTED OUT IN ANY WAY." << std::endl;
	std::cout << "//// END OF INSTRUCTIONS \\\\\\\\" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	char filePath[MAX_LEN];
	std::cin.getline(filePath, MAX_LEN);
	TernaryTreeDataHolder myDataHolder((const char*)filePath);
	menuFunction(myDataHolder);

	return 0;
}
