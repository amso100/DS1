/*
 * Student.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: amit
 */

#include "Student.h"
#include "Exceptions.h"

Student::Student(int id, int grade, int power) {
	this->student_id = id;
	this->grade      = grade;
	this->power      = power;
}

Student::~Student() { }

int Student::GetID() {
	return this->student_id;
}

int Student::GetGrade() {
	return this->grade;
}

int Student::GetPower() {
	return this->power;
}

void Student::UpdateGrade(int gr) {
	if(gr < 0)
		throw Failure();
	this->grade = gr;
}

void Student::UpdatePower(int pw) {
	if(pw < 0)
		throw Failure();
	this->power = pw;
}

bool Student::operator<(const Student& other) {
	if(this->power < other.power)
		return true;
	else if(this->power == other.power && this->student_id < other.student_id)
		return false;
	else
		return true;
}

bool Student::operator==(const Student& other) {
	return this->student_id == other.student_id;
}
