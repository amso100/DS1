/*
 * StudentPower.cpp
 *
 *  Created on: May 13, 2017
 *      Author: amit
 */

#include "StudentPower.h"

StudentPower::StudentPower(int id, int pow) : student_id(id), power(pow) { }

StudentPower::~StudentPower() { }

int StudentPower::GetID() {
	return this->student_id;
}

int StudentPower::GetPower() {
	return this->power;
}

void StudentPower::SetPower(int pow) {
	this->power = pow;
}

bool StudentPower::operator==(const StudentPower& other) {
	return ((this->student_id == other.student_id) && (this->power == other.power));
}

bool StudentPower::operator<(const StudentPower& other) {
	if(this->power < other.power)
		return true;
	else if(this->power == other.power && this->student_id < other.student_id)
		return true;
	else
		return false;
}
