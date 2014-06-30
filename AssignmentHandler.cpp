/*
Assignment handler implimentation
*/

#include "AssignmentHandler.h"
#include "StringTokenizer.h"
#include "HelperFunctions.h"
#include <iostream>
#include <fstream>
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
	if (temp == Assignment())
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
    updateFile("Assignments.txt");
}

void AssignmentHandler::completeAnAssignment(const Date theDate) // O(n+m)
{
	Assignment temp = findAssignment(assignedAssignments, theDate);
	if (temp == Assignment())
	{
		cout << "\nAssignment not found.\n" << endl;
		return;
	}
	 
	// remove the assignment from assignedAssignments
	assignedAssignments.remove(temp);

    (temp).displayAssignment(cout);
	// change status of assignment to complete
	(temp).completeAssignment();

	// add assignment to completed assignments (Ordered_List)
	completeAssignments.insert(temp);
    updateFile("Assignments.txt");
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
    Ordered_List<Assignment>::const_iterator iter = completeAssignments.begin();
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
void AssignmentHandler::displayAllAssignments(ostream& out) // O(n+m)
{
	cout << "\nASSIGNED ASSIGNMENTS\n\n"
		<< setw(12) << left << "Assigned"
		<< setw(12) << left << "Due"
		<< setw(20) << left << "Description"
		<< setw(12) << left << "Status" << endl
		<< "-------------------------------------------------------\n";
	displayOrderedAssignedAssignmentList(out);

	cout << "\nCOMPLETED ASSIGNMENTS\n\n"
		<< setw(12) << left << "Assigned"
		<< setw(12) << left << "Due"
		<< setw(20) << left << "Description"
		<< setw(12) << left << "Status" << endl
		<< "-------------------------------------------------------\n";
	displayOrderedCompletedAssignmentList(out);
	cout << endl;
}

//reads assignments from file and adds them to the assigned assignments list
void AssignmentHandler::importAssignmentsFromFile(const string& fName) // O(n)
{
	fileName = fName;
	ifstream in(fName.c_str());
	if (in)
	{
		Date assignedDate, dueDate;
		string aDate, dDate, desc, line, statusString;
        Assignment::status status;
		while (getline(in, line))
		{
            if (line == "") {break;}
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
            //read in status
            statusString = trim(stLine.next_token());
            if (statusString == "ASSIGNED") {status = Assignment::status::ASSIGNED;}
            else if (statusString == "COMPLETED") {status = Assignment::status::COMPLETED;}
            else {status = Assignment::LATE;}
            Assignment temp_assignment = Assignment(assignedDate, dueDate, desc, status);
            if (status == Assignment::ASSIGNED) {assignedAssignments.insert(temp_assignment);}
            else {completeAssignments.insert(temp_assignment);}
		}
        
	}
	else
		cout << "File Doesn't Exist" << endl;
    in.close(); //close file so it can be edited later
}

void AssignmentHandler::updateFile(const string& fName)
{
    fileName = fName;
    ofstream filestream(fName.c_str());
    filestream.flush();
    displayOrderedAssignedAssignmentList(filestream); 
    filestream.flush();
	displayOrderedCompletedAssignmentList(filestream);
    filestream.flush();
    filestream.close();
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
	return Assignment();
}

string AssignmentHandler::trim(const string& the_string)
{
	size_t p = the_string.find_first_not_of(" ");
	if (p == string::npos) return "";
	size_t q = the_string.find_last_not_of(" ");
	return the_string.substr(p, q - p + 1);
}