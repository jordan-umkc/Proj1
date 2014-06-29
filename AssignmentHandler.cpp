/*
Assignment handler implimentation
*/

#include "AssignmentHandler.h"
#include "StringTokenizer.h"
#include "HelperFunctions.h"
#include "Date.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// default, no argument constructor
void AssignmentHandler::addAssignment() // O(n)
{
	Assignment temp;
	temp.userInput();
	assignedAssignments.insert(temp);
}

// edit an assignment in the assigned assignments list
void AssignmentHandler::editAssignment(const Date theDate) // O(n)
{
	Assignment temp = findAssignment(assignedAssignments, theDate);
	if (temp.getAssignedDate() != theDate)
	{
		cout << "Assignment not found" << endl;
		return;
	}
	assignedAssignments.remove(temp);

	cout << "What do you want to edit?" << endl
		<< "1. Assigned Date" << endl
		<< "2. Due Date" << endl
		<< "3. Description" << endl
		<< "4. Nothing" << endl;
	int choice = getNumber(1, 4, "Enter your choice: ");
	switch (choice)
	{
	case 1:
	{
		Date theAssignedDate;
		cout << "Enter Assigned Date (ex. 11/11/1111): ";
		cin >> theAssignedDate;
		temp.setAssignedDate(theAssignedDate);
	}
		break;
	case 2:
	{
		Date theDueDate;
		cout << "Enter Due Date (ex. 11/11/1111): ";
		cin >> theDueDate;
		temp.setDueDate(theDueDate);
	}
		break;
	case 3:
	{
		string theDescription;
		cout << "Enter Description: ";
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, theDescription);
		temp.setDescription(theDescription);
	}
		break;
	case 4:
		break;
	default:
		cout << "Invalid Response" << endl;
		break;
	}

	assignedAssignments.insert(temp);
}

void AssignmentHandler::completeAnAssignment(const Date theDate) // O(n)
{
	Assignment temp = findAssignment(assignedAssignments, theDate);
	if (temp.getAssignedDate() != theDate)
	{
		cout << "Assignment not found" << endl;
		return;
	}
	// remove the assignment from assignedAssignments
	assignedAssignments.remove(temp);
	// change status of assignment to complete
	temp.completeAssignment();
	// add assignment to completed assignments (OrderedAssignmentList)
	completeAssignments.insert(temp);
}

// display all assigned assignments
void AssignmentHandler::displayOrderedAssignedAssignmentList(ostream& out) // O(n)
{
	list<Assignment>::const_iterator iter = assignedAssignments.begin();
	for (iter; iter != assignedAssignments.end(); iter++)
	{
		iter->displayAssignment(out);
	}
}

// display all completed and late assignments
void AssignmentHandler::displayOrderedCompletedAssignmentList(ostream& out) // O(n)
{
    list<Assignment>::const_iterator iter = completeAssignments.begin();
    for (iter; iter != completeAssignments.end(); iter++)
    {
		iter->displayAssignment(out);
    }
}

// output the number of late assignmets to the screen
void AssignmentHandler::countLateAssignments() // O(n)
{
    list<Assignment>::const_iterator iter = completeAssignments.begin();
    int lateAssignmentCount = 0;
    for (iter; iter != completeAssignments.end(); iter++)
    {
        if (iter->getCurrentStatus() == Assignment::status::LATE)
        {
            lateAssignmentCount++;
        }
    }
    cout << "The number of assignments that are LATE is: " << lateAssignmentCount << endl;
}

// output all assigned, completed and late assignments
void AssignmentHandler::displayAllAssignments(ostream& out) // O(n)
{
	cout << "Here are the assignments...\n\n";
    displayOrderedAssignedAssignmentList(out); 
    displayOrderedCompletedAssignmentList(out);
	cout << "That's it!\n\n";
}

//reads assignments from file and adds them to the assigned assignments list
void AssignmentHandler::importAssignmentsFromFile(const string& fName) // O(n)
{
	fileName = fName;
	ifstream in(fName.c_str(), ios::app);
	if (in)
	{
        Assignment temp_assignment;
		Date assignedDate, dueDate;
		string aDate, dDate, desc, line;
		while (getline(in, line))
		{
			String_Tokenizer stLine(line, ",");
			//read in assigned date
			aDate = trim(stLine.next_token());
			String_Tokenizer stADate(aDate, "/");
			assignedDate.setMonth(stoi(trim(stADate.next_token())));
			assignedDate.setDay(stoi(trim(stADate.next_token())));
			assignedDate.setYear(stoi(trim(stADate.next_token())));
			// read in due date
			dDate = trim(stLine.next_token());
			String_Tokenizer stDDate(dDate, "/");
			dueDate.setMonth(stoi(trim(stDDate.next_token())));
			dueDate.setDay(stoi(trim(stDDate.next_token())));
			dueDate.setYear(stoi(trim(stDDate.next_token())));
			// read in description
			desc = trim(stLine.next_token());
            temp_assignment = Assignment(assignedDate, dueDate, desc);
            assignedAssignments.insert(temp_assignment);
		}
	}
	else
		cout << "File Doesn't Exist" << endl;
}

// return the first assignment that has the same date as theAssignedDate (const Date) parameter
Assignment AssignmentHandler::findAssignment(Ordered_List<Assignment> theList, const Date theAssignedDate) // O(n)
{
	Ordered_List<Assignment>::const_iterator iter = theList.begin();
	while (iter != theList.end())
	{
		if (iter->getAssignedDate() == theAssignedDate)
			return *iter;
		else
			iter++;
	}
	return *iter;
}

string AssignmentHandler::trim(const string& the_string)
{
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");
	return the_string.substr(p, q - p + 1);
}