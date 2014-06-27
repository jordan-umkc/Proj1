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
	// default no-argument constructor
	Assignment() : assignedDate(), dueDate(), description("") { currentStatus = ASSIGNED; }

	// argument constructor
	Assignment(Date anAssignedDate, Date aDueDate, std::string aDescription) : assignedDate(anAssignedDate), dueDate(aDueDate), description(aDescription)
	{
		currentStatus = ASSIGNED;
	}

	// copy constructor
	Assignment(const Assignment& a) : assignedDate(a.assignedDate), dueDate(a.dueDate), description(a.description) { currentStatus = a.currentStatus; }

	// read in user data
	const Assignment& userInput()
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
		return *this;
	}

	
	void displayAssignment(ostream& out) const
	{
		out << "Assigned Date: " << assignedDate << setw(15)
			<< "Due Date: " << dueDate << setw(15)
			<< "Status: " << getCurrentStatus() << endl
			<< "Description: " << description << endl << endl;
	}

	void setAssignedDate(const Date& theDate)
	{
		assignedDate = theDate;
	}

	void setDueDate(const Date& theDate)
	{
		dueDate = theDate;
	}

	void setDescription(const string& theDescription)
	{
		description = theDescription;
	}

	Date getAssignedDate() const { return assignedDate; }
    Date getDueDate() const {return dueDate;}
    string getDescription() const {return description;}

    string getCurrentStatus() const
    {
        if (currentStatus == ASSIGNED) {return "ASSIGNED";}
        else if (currentStatus == COMPLETED) {return "COMPLETE";}
        else {return "LATE";}
    }
    void completeAssignment() {currentStatus = COMPLETED;}
    void overdueAssignment() {currentStatus = LATE;}

    //Assignment::status getStatus() const {return currentStatus;}

	// assigned date is id
	bool operator ==(const Assignment other) const{
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

	bool operator <(const Assignment& other) const {
		return assignedDate < other.assignedDate;
	}


private:
	Date assignedDate;
	Date dueDate;
	string description;
    enum status {LATE = 0, ASSIGNED = 1, COMPLETED = 2}; //stated explicitly so we can use the array below easily
    
    status currentStatus;
};

#endif

