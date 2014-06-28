/*
CS303 Data Structures
Project 1
Due July 1, 2014
Team members: Jordan Larson, Evan Bell, Brenton Klassen
*/

#include "HelperFunctions.h"
#include "AssignmentHandler.h"
#include <iostream>
#include <stdlib.h>

int getNumber(int low, int high, std::string message);

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
		{
			Date temp;
			cout << "Enter the assigned date of the assignment you want to edit. ";
			cin >> temp;
			Assignments.completeAnAssignment(temp);
		}
            break;
		case 3:
		{
			Date temp;
			cout << "Enter the assigned date of the assignment you want to edit. ";
			cin >> temp;
			Assignments.editAssignment(temp);
		}
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
}


