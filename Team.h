/*
 * Team.h
 *
 *  Created on: Apr 27, 2017
 *      Author: amit
 */

#ifndef TEAM_H_
#define TEAM_H_

#include <vector>
#include "Student.h"
//Include AVL

class Team {
private:
	int team_id;
	int team_size;
	StudentPower best;
	AVLTree<StudentPower, Student*> team_students;
	void UpdateMostPowerful();
public:

	//Creates a new empty team.
	explicit Team(int id);

	//Destroys the current team.
	~Team();

	//Returns team's current size.
	int GetSize();

	//Returns the current team's ID.
	int GetID();

	//Adds a student with the given ID to the current team.
	void AddStudent(Student* student);

	//Removes the student with the given ID.
	void RemoveStudent(Student* student);

	//Returns the most powerful student on the team.
	StudentPower MostPowerfulInGroup();

	//Gets a vector of all students in team by their power.
	StudentPower* GetStudentsByPower();
};
#endif /* TEAM_H_ */
