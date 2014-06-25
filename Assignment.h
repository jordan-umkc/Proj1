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
	Assignment() : assignedDate(), dueDate(), description("") { currentStatus = ASSIGNED; }
	Assignment(Date anAssignedDate, Date aDueDate, std::string aDescription) : assignedDate(anAssignedDate), dueDate(aDueDate), description(aDescription)
	{
		currentStatus = ASSIGNED;
		/* These variables have already been set using member initialization
        dueDate = aDueDate;
        assignedDate = anAssignedDate;
        description = aDescription;
		*/
	}
	Assignment(const Assignment& a) : assignedDate(a.assignedDate), dueDate(a.dueDate), description(a.description) { currentStatus = a.currentStatus; }
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

	void Assignment::displayAssignment(ostream& out) const
	{
		out << "Assigned Date: " << assignedDate << setw(15)
			<< "Due Date: " << dueDate << setw(15)
			<< "Status: " << getCurrentStatus() << endl
			<< "Description: " << description << endl << endl;
	}

	void setAssignedDate(const Assignment& theDate)
	{
		assignedDate = theDate;
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


	bool operator ==(const Assignment other) const{
		return assignedDate == other.assignedDate &&
            dueDate == other.dueDate && description == other.description && currentStatus == other.currentStatus;
	}
	//not sure status needs to be checked here? Let's discuss - it's probably best to leave it as is, however

	Assignment operator =(const Assignment theAssignment)
	{
		if (*this == theAssignment) return *this;
		assignedDate = theAssignment.assignedDate;
		dueDate = theAssignment.dueDate;
		description = theAssignment.description;
		return *this;
	}

	const Assignment data() const
	{
		return *this;
	}

private:
	Date assignedDate;
	Date dueDate;
	string description;
    enum status {LATE = 0, ASSIGNED = 1, COMPLETED = 2}; //stated explicitly so we can use the array below easily
    
    status currentStatus;
};

#endif

