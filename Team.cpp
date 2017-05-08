/*
 * Team.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: amit
 */

#include "Team.h"

Team::Team(int id) {
	this->team_id = id;
	this->best = nullptr;
}

void Team::AddStudent(int stud_id) {
	//Add code for adding to AVL tree.
}

void Team::RemoveStudent(int stud_id) {
	//Add code for removing from AVL tree.
}

Student* Team::MostPowerfulInGroup() {
	return this->best;
}

std::vector<Student*> Team::GetStudentsByPower() {
	//Add code for getting all by power.
	return nullptr;
}
