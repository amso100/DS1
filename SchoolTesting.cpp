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

	school.AddStudent(1, 1, 1);
	school.AddStudent(2, 1, 1);
	school.AddStudent(3, 1, 1);
	school.AddStudent(5, 1, 1);
	school.RemoveStudent(4);
	school.AddStudent(4, 1, 3);
	school.AddStudent(6, 2, 4);
	school.AddStudent(7, 2, 8);
	school.AddStudent(8, 2, 7);
	school.MoveStudentToTeam(1, 1);
	school.AddTeam(1);
	school.AddTeam(2);
	school.MoveStudentToTeam(1, 1);
	school.MoveStudentToTeam(2, 1);
	school.MoveStudentToTeam(3, 1);
	school.MoveStudentToTeam(4, 2);
	school.MoveStudentToTeam(4, 3);
	school.MoveStudentToTeam(6, 2);
	school.MoveStudentToTeam(7, 1);
	school.MoveStudentToTeam(3, 2);
	school.AddTeam(3);
	school.AddTeam(4);
	school.AddTeam(5);
	school.MoveStudentToTeam(2, 5);
	school.MoveStudentToTeam(8, 4);
	school.GetMostPowerful(-1);
	school.GetMostPowerful(1);
	school.GetMostPowerful(0);
	school.MoveStudentToTeam(8, 1);
	school.GetMostPowerful(1);
	school.RemoveStudent(9);
	school.RemoveStudent(8);
	school.GetMostPowerful(1);
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
