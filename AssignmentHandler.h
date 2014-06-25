/*
Assignment handler class
*/

#ifndef __ASSIGNMENTHANDLER_H__
#define __ASSIGNMENTHANDLER_H__
#include "OrderedAssignmentList.h"
#include <iterator>

class AssignmentHandler {
    
public:
	AssignmentHandler() : assignedAssignments(), completeAssignments() {} // default constructor
	
	void addAssignment();
	void editAssignment();
    void displayOrderedAssignedAssignmentList(ostream& out);
    void displayOrderedCompletedAssignmentList(ostream& out);
    void displayAllAssignments(ostream& out);
	int getLateAssignments();
	void importAssignmentsFromFile(const string& sourceName);
	string trim(const string&);
    void countLateAssignments();
    void completeAnAssignment();
    void overdueAnAssignment(Assignment& assignment);

private:
	OrderedAssignmentList assignedAssignments;
	OrderedAssignmentList completeAssignments;
	string fileName;
};

#endif
