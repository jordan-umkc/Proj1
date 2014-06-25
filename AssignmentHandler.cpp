/*
Assignment handler implimentation
*/

#include "AssignmentHandler.h"
#include "StringTokenizer.h"
#include "Date.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <iterator>
using namespace std;

// default, no argument constructor
void AssignmentHandler::addAssignment()
{
	Assignment *temp = new Assignment();
	temp->userInput();
	assignedAssignments.insert(*temp);
}

void AssignmentHandler::editAssignment()
{

}

int AssignmentHandler::getLateAssignments()
{
	return 0; // temporary return
}

void AssignmentHandler::completeAnAssignment()
{
	// ask the user to input the information of the assignment they completed
	Date theDueDate, theAssignedDate;
	string theDescription;
	cout << "Enter Assigned Date (ex. 11/11/1111): ";
	cin >> theAssignedDate;
	cout << "Enter Due Date (ex. 11/11/1111): ";
	cin >> theDueDate;
	cout << "Enter Description: ";
	cin >> theDescription;
	// make a new assignment with the user input
	Assignment *temp = new Assignment(theAssignedDate, theDueDate, theDescription);
	// create a const_iterator that points to the assignment in the assignedAssignments (OrderedAssignmentList)
	OrderedAssignmentList::const_iterator iter = assignedAssignments.find(*temp);
	// remove the assignment from assignedAssignments
	assignedAssignments.remove(iter->data());
	// change status of assignment to complete
	temp->completeAssignment();
	// add assignment to completed assignments (OrderedAssignmentList)
	completeAssignments.insert(*temp);
}

void AssignmentHandler::overdueAnAssignment(Assignment& assignment)
{
    assignment.overdueAssignment();
}

void AssignmentHandler::displayOrderedAssignedAssignmentList(ostream& out)
    {
        OrderedAssignmentList::const_iterator iter;
        for (iter = assignedAssignments.begin(); iter != assignedAssignments.end(); iter++)
        {
			iter->displayAssignment(out);
        }
    }

void AssignmentHandler::displayOrderedCompletedAssignmentList(ostream& out)
{
    OrderedAssignmentList::const_iterator iter;
    for (iter = completeAssignments.begin(); iter != completeAssignments.end(); iter++)
    {
		iter->displayAssignment(out);
    }
}

void AssignmentHandler::countLateAssignments()
{
    OrderedAssignmentList::const_iterator iter;
    int lateAssignmentCount = 0;
    for (iter = completeAssignments.begin(); iter != completeAssignments.end(); iter++)
    {
        if (iter->getCurrentStatus() == "LATE")
        {
            lateAssignmentCount++;
        }
    }
    cout << "The number of assignments that are LATE is: " << lateAssignmentCount << endl;
}

void AssignmentHandler::displayAllAssignments(ostream& out)
{
	cout << "Here are the assignments...\n\n";
    displayOrderedAssignedAssignmentList(out);
    displayOrderedCompletedAssignmentList(out);
	cout << "That's it!\n\n";
}


//reads assignments from file and adds them to the assigned assignments list
void AssignmentHandler::importAssignmentsFromFile(const string& fName)
{
	fileName = fName;
	ifstream in(fName.c_str(), ios::app);
	if (in)
	{
        Assignment* temp_assignment;
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
            temp_assignment = new Assignment(assignedDate, dueDate, desc);
            assignedAssignments.insert(*temp_assignment);
		}
	}
	else
		cout << "File Doesn't Exist" << endl;
}

string AssignmentHandler::trim(const string& the_string)
{
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");
	return the_string.substr(p, q - p + 1);
}