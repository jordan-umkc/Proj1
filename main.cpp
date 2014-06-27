/*
CS303 Data Structures
Project 1
Due July 1, 2014
Team members: Jordan Larson, Evan Bell, Brenton Klassen
*/

#include "AssignmentHandler.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int getNumber(int, int, std::string = "");

void main()
{
	// user's choice
	int choice;

	// instantiate assignment handler
	AssignmentHandler Assignments;

	do {
		// display menu
		cout << "Welcome to the assignment handler!\n\n"
			<< "Choose one of the following commands:\n\n"
			<< "1. Add a new assignment\n"
			<< "2. Complete an assignment\n"
			<< "3. Edit an assignment\n"
			<< "4. Display all assignments\n"
			<< "5. Count the number of late assignments\n"
			<< "6. Read assignments from file\n"
			<< "7. Exit\n\n";

		choice = getNumber(1, 7, "Enter a choice: ");
        
		switch (choice)
		{
		case 1:
			Assignments.addAssignment();
			break;
        case 2:
            Assignments.completeAnAssignment();
            break;
        case 3:
			Assignments.editAssignment(); 
            break;
		case 4:
			Assignments.displayAllAssignments(cout);
			break;
        case 5:
            Assignments.countLateAssignments();
            break;
        case 6:
            Assignments.importAssignmentsFromFile("Assignments.txt");
            break;
		case 7:
			break;
		default:
			cout << "Invalid Input";
			break;
		}

	} while (choice != 7);
    
	system("pause");
}


// function to get number from user and take care of incorrect input
int getNumber(int low, int high, std::string message)
{
	int number;
	bool valid = false;
	if (message == "")
		message = "Enter a number between " + std::to_string(low) + " and " + std::to_string(high) + ": ";
	do
	{
		cout << message;
		cin >> number;
		while (std::cin.fail())
		{
			cout << "You must enter an integer: ";
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
			cin >> number;
		}
		if (number < low || number > high)
			cout << "The number must be between " << low << " and " << high << ".\n";
		else
			valid = true;
	} while (!valid);
	return number;
}
