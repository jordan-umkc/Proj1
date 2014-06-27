/*
Assignment handler class
*/

#ifndef __ASSIGNMENTHANDLER_H__
#define __ASSIGNMENTHANDLER_H__
#include "Ordered_List.h"
#include "Assignment.h"

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
	Ordered_List<Assignment> assignedAssignments;
	Ordered_List<Assignment> completeAssignments;
	string fileName;
};

#endif
