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
	Student* best;
	//AVL tree <Student*>
public:
	explicit Team(int id);
	~Team();
	void AddStudent(int  stud_id);
	void RemoveStudent(int stud_id);
	Student* MostPowerfulInGroup();
	std::vector<Student*> GetStudentsByPower();
};
#endif /* TEAM_H_ */
