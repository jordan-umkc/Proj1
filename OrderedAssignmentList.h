/*
Ordered list header
This is a list of assignments that automatically inserts the assignments in order.
Take a look at p288 in our textbook for details on how this list works.
*/

#ifndef __ORDEREDASSIGNMENTLIST_H__
#define __ORDEREDASSIGNMENTLIST_H__
#include "Assignment.h"
#include <list>

class OrderedAssignmentList {
public:

	typedef std::list<Assignment>::const_iterator const_iterator;

	void insert(const Assignment& theAssignment){
		std::list<Assignment>::iterator itr = assignmentList.begin();
		while (itr != assignmentList.end() && itr->getAssignedDate() < theAssignment.getAssignedDate())
			++itr;
		assignmentList.insert(itr, theAssignment);
	}

	void remove(const Assignment& theAssignment){
		assignmentList.remove(theAssignment);
	}

	const_iterator find(const Assignment theAssignment)
	{
		const_iterator iter;
		for (iter = begin(); iter != end(); iter++)
		{
			if (iter->data() == theAssignment)
			{
				return iter;
			}
		}
		throw::exception("The assignment was not found");
	}

	const_iterator begin() const {
		return assignmentList.begin();
	}

	const_iterator end() const {
		return assignmentList.end();
	}

private:
	std::list<Assignment> assignmentList;
};

#endif