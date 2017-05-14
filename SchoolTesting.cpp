/*
 * SchoolTesting.cpp
 *
 *  Created on: May 13, 2017
 *      Author: amit
 */

#include <iostream>
#include "MutantSchool.h"
#include "exceptions.h"
#include "Student.h"

void PrintStudentArray(StudentPower* arr, int len) {
	for(int i = 0; i < len; i++) {
		std::cout << "ID: " << arr[i].GetID() << "\tPower: " << arr[i].GetPower() << std::endl;
	}
}

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
	school.GetMostPowerful(1);

	try {
		std::cout << "Getting all students by power from team 1" << std::endl;
		int x = 0;
		StudentPower* by_power1 = school.GetAllStudentsByPower(1, &x);
		PrintStudentArray(by_power1, x);
	} catch(Failure& e) {
		std::cout << "Error getting by power from team 1.\n";
	}
	try {
		std::cout << "Getting all students by power from team 5" << std::endl;
		int x = 0;
		StudentPower* by_power2 = school.GetAllStudentsByPower(5, &x);
		PrintStudentArray(by_power2, x);
	} catch(Failure& e) {
		std::cout << "Error getting by power from team 5.\n";
	}
	try {
		std::cout << "Getting all students by power from team 2" << std::endl;
		int x = 0;
		StudentPower* by_power2 = school.GetAllStudentsByPower(2, &x);
		PrintStudentArray(by_power2, x);
	} catch(Failure& e) {
		std::cout << "Error getting by power from team 2.\n";
	}
	try {
		std::cout << "Removing student 4 from system...\n";
		school.RemoveStudent(4);
	} catch(...) {
		std::cout << "Error removing student 4.\n";
	}
	try {
		std::cout << "Getting all students by power from team 2" << std::endl;
		int x = 0;
		StudentPower* by_power2 = school.GetAllStudentsByPower(2, &x);
		PrintStudentArray(by_power2, x);
	} catch(Failure& e) {
		std::cout << "Error getting by power from team 2.\n";
	}
	try {
		std::cout << "Increase power to all in grade 1 to power=5\n";
		school.IncreaseLevel(1, 5);
		std::cout << "Power increased.\n";
	} catch(...) {
		std::cout << "Error increasing power.\n";
	}
	try {
		school.GetMostPowerful(4);
	} catch(...) {
		std::cout << "Error getting most powerful in group 4.\n";
	}
	try {
		std::cout << "Moving student 5 to team 4.\n";
		school.MoveStudentToTeam(5, 4);
	} catch(...) {
		std::cout << "Error moving student 5 to team 4.\n";
	}
	std::cout << "Most powerful in group 4: " << school.GetMostPowerful(4) << std::endl;
	//Quit
}
