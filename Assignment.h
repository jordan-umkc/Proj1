/*
Assignment class header
*/

#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__
#include "Date.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Assignment {
public:

	enum status { LATE, ASSIGNED, COMPLETED };

	enum memberDate { ASSIGNEDDATE, DUEDATE };

	// default no-argument constructor
	Assignment() : assignedDate(), dueDate(), description(""), sortBy(ASSIGNEDDATE), currentStatus(ASSIGNED) {}

	// argument constructor
	Assignment(Date anAssignedDate, Date aDueDate, std::string aDescription) : assignedDate(anAssignedDate), dueDate(aDueDate), description(aDescription), sortBy(ASSIGNEDDATE), currentStatus(ASSIGNED) {}

	// copy constructor
	Assignment(const Assignment& a) : assignedDate(a.assignedDate), dueDate(a.dueDate), description(a.description), sortBy(a.sortBy), currentStatus(a.currentStatus) {}

	// Setters
	void setAssignedDate(const Date& theDate) { assignedDate = theDate; }
	void setDueDate(const Date& theDate) { dueDate = theDate; }
	void setDescription(const string& theDescription) { description = theDescription; }
	// Getters
	Date getAssignedDate() const { return assignedDate; }
	Date getDueDate() const { return dueDate; }
	string getDescription() const { return description; }
	status getCurrentStatus() const { return currentStatus; }
	// changing status
	void completeAssignment()
	{
		sortBy = DUEDATE;
		Date currentDate;
		cout << "What is today's date? (ex. 11/11/1111) ";
		cin >> currentDate;
		// check if assignment is overdue
		if (currentDate <= dueDate)
			currentStatus = COMPLETED;
		else
			currentStatus = LATE;
	}

	// read in user data to assign the private variables of an assignment (used in AssignmentHandler::addAssignment)
	void userInput()
	{ 
		Date theDueDate, theAssignedDate;
		string theDescription;
		cout << "Enter Assigned Date (ex. 11/11/1111): ";
		cin >> theAssignedDate;
		cout << "Enter Due Date (ex. 11/11/1111): ";
		cin >> theDueDate;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Enter Description: ";
		getline(cin, theDescription);
		assignedDate = theAssignedDate;
		dueDate = theDueDate;
		description = theDescription;
	}

	// read in assigned date from user (used in AssignmentHandler to find the assignment the user wants to complete or edit)
	void userInputAssignedDate()
	{
		Date theAssignedDate;
		cout << "Enter Assigned Date (ex. 11/11/1111): ";
		cin >> theAssignedDate;
		assignedDate = theAssignedDate;
	}

	//  display information about an assignment
	void displayAssignment(ostream& out) const
	{
		string statusString;
		if (currentStatus == ASSIGNED) statusString = "Assigned";
		if (currentStatus == LATE) statusString = "Late";
		if (currentStatus == COMPLETED) statusString = "Completed";

		out << "Assigned Date: " << assignedDate << setw(15)
			<< "Due Date: " << dueDate << setw(15)
			<< "Status: " << statusString << endl
			<< "Description: " << description << endl << endl;
	}

    //Assignment::status getStatus() const {return currentStatus;}

	// assigned date is id
	bool operator ==(const Assignment other) const
	{
		return assignedDate == other.assignedDate;
	}

	const Assignment operator =(const Assignment& theAssignment)
	{
		if (*this == theAssignment) return *this;
		assignedDate = theAssignment.assignedDate;
		dueDate = theAssignment.dueDate;
		description = theAssignment.description;
		return *this;
	}

	bool operator <(const Assignment& other) const 
	{
		if (sortBy == ASSIGNEDDATE)
			return assignedDate < other.assignedDate;
		else
			return dueDate < other.dueDate;
	}

private:
	Date assignedDate;
	Date dueDate;
	string description;
    Assignment::status currentStatus;
	Assignment::memberDate sortBy;
};

#endif

