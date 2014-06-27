#include "HelperFunctions.h"

// function to get number from user and take care of incorrect input
int getNumber(int low, int high, std::string message)
{
	int number;
	bool valid = false;
	if (message == "")
		message = "Enter a number between " + std::to_string(low) + " and " + std::to_string(high) + ": ";
	do
	{
		std::cout << message;
		std::cin >> number;
		while (std::cin.fail())
		{
			std::cout << "You must enter an integer: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			std::cin >> number;
		}
		if (number < low || number > high)
			std::cout << "The number must be between " << low << " and " << high << ".\n";
		else
			valid = true;
	} while (!valid);
	return number;
}
