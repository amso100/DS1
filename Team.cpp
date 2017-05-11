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

void Team::AddStudent(Student* student) {
	try {
		//First, add student to tree of students in team.
		this->team_students.insertToTree(student, student->GetPower());
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
		this->team_students.removeFromTree(student);
	} catch(NotInTree& e) {
		return;
	}
	if(this->best == student)
		this->UpdateMostPowerful();
	this->team_size--;
}

Student* Team::MostPowerfulInGroup() {
	return this->best;
}

std::vector<Student*> Team::GetStudentsByPower() {
	std::vector<Student*> by_power;
	return this->team_students.ReverseInorderKeys();
}

void Team::UpdateMostPowerful() {
	Student* most_power = this->team_students.MostRight();
	this->best = most_power;
}
