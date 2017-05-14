/*
 * SchoolTesting.cpp
 *
 *  Created on: May 13, 2017
 *      Author: amit
 */

#include <iostream>
#include "MutantSchool.h"
#include "exceptions.h"

int main() {
	MutantSchool school;

	for (int i = 1; i < 4; i++) {
		std::cout << "Adding Student with id: " << i << std::endl;
		std::cout << "Power level: " << 1 << std::endl;
		std::cout << "Grade: " << 1 << std::endl;
		school.AddStudent(i, 1, 1);
	}
	std::cout << "Adding Student with id: " << 5 << std::endl;
	std::cout << "Power level: " << 1 << std::endl;
	std::cout << "Grade: " << 1 << std::endl;
	school.AddStudent(5, 1, 1);
	std::cout << "Removing student: " << 4;
	try {
		school.RemoveStudent(4);
		std::cout << "Bad" << std::endl;
	} catch (Failure&) {
		std::cout << "Good" << std::endl;
	}
	std::cout << "Adding Student with id: " << 4 << std::endl;
	std::cout << "Power level: " << 3 << std::endl;
	std::cout << "Grade: " << 1 << std::endl;
	school.AddStudent(4, 1, 3);
	for (int j = 7; j < 9; j++) {
		std::cout << "Adding Student with id: " << j << std::endl;
		std::cout << "Power level: " << 15 - j << std::endl;
		std::cout << "Grade: " << 2 << std::endl;
		school.AddStudent(j, 2, j - 1);
	}
	std::cout << "Adding Student with id: " << 6 << std::endl;
	std::cout << "Power level: " << 2 << std::endl;
	std::cout << "Grade: " << 4 << std::endl;
	school.AddStudent(6, 2, 4);
	std::cout << "Moving student " << 1 << "...";
	try {
		school.MoveStudentToTeam(1, 1);
	} catch (Failure&) {
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	for (int m = 1; m < 3; m++) {
		std::cout << "Adding team " << m << std::endl;
		school.AddTeam(m);
	}
	for (int n = 1; n < 4; n++) {
		std::cout << "Moving Student " << n << "to Group 1...";
		try {
			school.MoveStudentToTeam(n, 1);
			std::cout << "Good" << std::endl;
		} catch (...) {
			std::cout << "Bad" << std::endl;
		}
	}
	std::cout << "Moving Student " << 4 << " to Group 2...";
	try {
		school.MoveStudentToTeam(4, 2);
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Moving Student " << 4 << " to Group 3...";
	try {
		school.MoveStudentToTeam(4, 3);
		std::cout << "Bad" << std::endl;
	} catch (Failure&) {
		std::cout << "Good" << std::endl;
	}
	std::cout << "Moving Student " << 6 << " to Group 2...";
	try {
		school.MoveStudentToTeam(6, 2);
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Moving Student " << 7 << " to Group 1...";
	try {
		school.MoveStudentToTeam(7, 1);
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Moving Student " << 3 << " to Group 2...";
	try {
		school.MoveStudentToTeam(3, 2);
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	for (int j = 3; j < 6; j++) {
		std::cout << "Adding team number " << j << "....";
		school.AddTeam(j);
		std::cout << "Good" << std::endl;
	}
	std::cout << "Moving Student " << 2 << " to Group 5...";
	try {
		school.MoveStudentToTeam(2, 5);
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Moving Student " << 8 << " to Group 4...";
	try {
		school.MoveStudentToTeam(8, 4);
		std::cout << "Good" << std::endl;
	} catch (...) {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Getting the strongest mutant...";
	if (school.GetMostPowerful(-1) == 7) {
		std::cout << " Good" << std::endl;
	}
	std::cout << "Getting the strongest in Team 1....";
	if (school.GetMostPowerful(1) == 7) {
		std::cout << "Good" << std::endl;
	} else {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Getting the strongest in Team 0....";
	try {
		school.GetMostPowerful(0);
		std::cout << "Bad" << std::endl;
	} catch (Failure&) {
		std::cout << "Good" << std::endl;
	}
	std::cout << "Moving student number 8 to team 1" << std::endl;
	school.MoveStudentToTeam(8, 1);
	std::cout << "Moving student number 7 to team 2" << std::endl;
	school.MoveStudentToTeam(7, 2);

	std::cout << "Getting the strongest in Team 1....";
	if (school.GetMostPowerful(1) == 8) {
		std::cout << "Good" << std::endl;
	} else {
		std::cout << "Bad" << std::endl;
	}
	std::cout << "Removing student number 9...";
	try {
		school.RemoveStudent(9);
		std::cout << "Bad" << std::endl;
	} catch (Failure&) {
		std::cout << "Good" << std::endl;
	}
	std::cout << "Removing student number 8...";
	school.RemoveStudent(8);
	if (school.GetMostPowerful(1) == 8) {
		std::cout << "Bad" << std::endl;
	} else {
		std::cout << "Good" << std::endl;
	}
	school.GetAllStudentsByPower(1);
	school.GetAllStudentsByPower(5);
	school.GetAllStudentsByPower(2);
	school.RemoveStudent(4);
	school.GetAllStudentsByPower(2);
	school.IncreaseLevel(1, 5);
	school.GetMostPowerful(4);
	school.MoveStudentToTeam(5, 4);
	school.GetMostPowerful(4);
	//Quit
}
