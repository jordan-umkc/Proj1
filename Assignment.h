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
	Assignment() : assignedDate(), dueDate(), description("") {}
	Assignment(Date anAssignedDate, Date aDueDate, std::string aDescription) : assignedDate(anAssignedDate), dueDate(aDueDate), description(aDescription)
	{
		currentStatus = ASSIGNED;
		/* These variables have already been set using member initialization
        dueDate = aDueDate;
        assignedDate = anAssignedDate;
        description = aDescription;
		*/
	}

	void Assignment::displayAssignment(ostream& out) const
	{
		out << "Assigned Date: " << assignedDate << setw(15)
			<< "Due Date: " << dueDate << setw(15)
			<< "Status: " << getCurrentStatus() << endl
			<< "Description: " << description << endl << endl;
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


	bool operator ==(Assignment other){
		return assignedDate == other.assignedDate &&
            dueDate == other.dueDate && description == other.description && currentStatus == other.currentStatus;
	}
	//not sure status needs to be checked here? Let's discuss - it's probably best to leave it as is, however

private:
	Date assignedDate;
	Date dueDate;
	string description;
    enum status {LATE = 0, ASSIGNED = 1, COMPLETED = 2}; //stated explicitly so we can use the array below easily
    
    status currentStatus;
};

#endif

