/*
Assignment class header
*/

#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__
#include "Date.h"
#include <string>
#include <iostream>
using namespace std;

class Assignment {
public:
	Assignment::Assignment() : assignedDate(), dueDate(), description("") {}
	Assignment::Assignment(Date anAssignedDate, Date aDueDate, std::string aDescription) : assignedDate(anAssignedDate), dueDate(aDueDate), description(aDescription)
	{
		currentStatus = ASSIGNED;
        dueDate = aDueDate;
        assignedDate = anAssignedDate;
        description = aDescription;
	}

	void Assignment::displayAssignment(ostream& out) const
	{
		out << "Assigned Date: " << assignedDate << "\t"
			<< "Due Date: " << dueDate << "\t" << endl
			<< "Assignment Description: " << description
			<< "Assignment Status: " << "\t" << getCurrentStatus() << endl << endl;
	}

	//Assignment::~Assignment(); // this was causing a lnk error
	Date getAssignedDate() const { return assignedDate; }
    Date getDueDate() const {return dueDate;}
    string getDescription() const {return description;}


    string getCurrentStatus() const
    {
        if (currentStatus == ASSIGNED) {return "ASSIGNED";}
        else if (currentStatus == COMPLETED) {return "COMPLETE";}
        else if (currentStatus == LATE) {return "LATE";}
        //handle an error
    }
    void completeAssignment() {currentStatus = COMPLETED;}
    void overdueAssignment() {currentStatus = LATE;}

    //Assignment::status getStatus() const {return currentStatus;}


	bool operator ==(const Assignment other) const{
		return assignedDate == other.assignedDate &&
            dueDate == other.dueDate && description == other.description; //&& currentStatus == other.currentStatus;
	}
	//not sure status needs to be checked here? Let's discuss - it's probably best to leave it as is, however

private:
	Date assignedDate;
	Date dueDate;
	std::string description;
    enum status {LATE = 0, ASSIGNED = 1, COMPLETED = 2}; //stated explicitly so we can use the array below easily
    
    status currentStatus;
};

#endif

