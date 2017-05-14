/*
 * MutantSchool.h
 *
 *  Created on: May 11, 2017
 *      Author: amit
 */

#ifndef MUTANTSCHOOL_H_
#define MUTANTSCHOOL_H_

#include "avl_tree.h"
#include "Student.h"
#include "StudentPower.h"
#include "Team.h"
#include "exceptions.h"

/*
 * Class for describing the entire mutant school.
 */
class MutantSchool {

private:

	//Amount of students in the school.
	int student_count;

	//Amount of teams in the school.
	int team_count;

	//The most powerful student in the entire school.
	StudentPower best_all;

	//Tree of team_id -> Team
	AVLTree<int, Team*> school_teams;

	//Tree of student_power -> Student
	AVLTree<StudentPower, Student*> students_by_power;

	//Tree of student_id -> Student's team
	AVLTree<int, Team*> student_teams;

	//Tree of student_id -> Student
	AVLTree<int, Student*> students_by_id;

	//Updates the school's most powerful student.
	//Called when removing a student, if the removed is the most powerful.
	void UpdatePowerful();

	int GetCountInGrade(Student** stud_arr, int len, int grade);
	Student** StudentsOnlyInGrade(Student** stud_arr, int len, int grade);
	Student** NotInGrade(Student** studs_arr, int len, int grade);
	StudentPower* PowerInGrade(Student** students, StudentPower* power_arr, int len, int grade);
	StudentPower* PowerNotGrade(Student** students, StudentPower* power_arr, int len, int grade);
	Student** MergeStudsByPower(Student** arr1, int len1, Student** arr2, int len2);
	StudentPower* MergePairsByPower(StudentPower* arr1, int len1, StudentPower* arr2, int len2);

public:

	//Creates a new School with empty data. O(1)
	explicit MutantSchool();

	//Destroys the given school instance. O(n + k)
	~MutantSchool();

	int StudentsNum();

	//Adds a new student to the school with given ID, grade, power. O(log n)
	void AddStudent(int id, int grade, int power);

	//Adds a new team to the school, with a given ID. O(log k)
	void AddTeam(int id);

	//Moves a given student to the specified team. O(log(k) + log(n))
	void MoveStudentToTeam(int student_id, int team_id);

	//Returns the most powerful student in a given team, or in the entire school.
	//O(1) for the entire school, O(log k)
	int GetMostPowerful(int team_id);

	//Removes the given student from the system. O(log n)
	void RemoveStudent(int student_id);

	//Returns a vector of all the students in school/team by their power.
	StudentPower* GetAllStudentsByPower(int team_id, int* size);

	//Increases the power of all students in a grade, and their gradde by given amounts. O(n)
	void IncreaseLevel(int grade, int inc);
};

#endif /* MUTANTSCHOOL_H_ */
