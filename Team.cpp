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
	this->team_size = 0;
}

int Team::GetSize() {
	return this->team_size;
}

int Team::GetID() {
	return this->team_id;
}

void Team::AddStudent(Student* student) {
	try {
		//First, add student to tree of students in team.
		this->team_students.insertToTree(StudentPower(student->GetID(), student->GetPower()), student);
	} catch(AlreadyInTree& e) {
		return;
	}

	//Then check if best, or if team was empty until now.
	if(this->best == nullptr)
		this->best = student;
	if(*(this->best) < *student)
		this->best = student;
	this->team_size++;
}

void Team::RemoveStudent(Student* student) {
	try {
		this->team_students.removeFromTree(StudentPower(student->GetID(), student->GetPower()));
	} catch(NotInTree& e) {
		return;
	}
	if(this->best == student)
		this->UpdateMostPowerful();
	this->team_size--;
}

StudentPower Team::MostPowerfulInGroup() {
	return this->best;
}

StudentPower* Team::GetStudentsByPower() {
	return this->team_students.ReverseInorderKeys();
}

void Team::UpdateMostPowerful() {
	StudentPower most_power = this->team_students.getBiggestKey();
	this->best = most_power;
}
