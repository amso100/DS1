/*
 * MutantSchool.cpp
 *
 *  Created on: May 11, 2017
 *      Author: amit
 */

#include "MutantSchool.h"

MutantSchool::MutantSchool() {
	this->best_all = nullptr;
	this->student_count = 0;
	this->team_count = 0;
}

void MutantSchool::UpdatePowerful() {
	if(this->student_count == 0)
		this->best_all = nullptr;
	else
		this->best_all = this->students_by_power.getBiggestKey();
}

MutantSchool::~MutantSchool() {
	this->best_all = nullptr;
}

void MutantSchool::AddStudent(int id, int grade, int power) {
	if(id <= 0 || grade <= 0 || power <= 0)
		throw InvalidInput();
	Student* create = nullptr;
	StudentPower cre_pair = nullptr;
	try {
		if(this->students_by_id.Exists(id))
			throw Failure();
		create = new Student(id, grade, power);
		cre_pair = new StudentPower(id, power);
		this->students_by_id.insertToTree(id, create);
		this->students_by_power.insertToTree(cre_pair, create);
		this->student_count++;
		if(this->best_all == nullptr)
			this->best_all = create;
		else
			if(this->best_all->GetPower() < power)
				this->best_all = create;

	} catch(std::bad_alloc& e) {
		throw AllocationError();
	}
}

void MutantSchool::AddTeam(int id) {
	if(id <= 0)
		throw InvalidInput();
	if(this->school_teams.Exists(id))
		throw Failure();
	Team* create = nullptr;
	try {
		create = new Team(id);
		this->school_teams.insertToTree(id, create);
		this->team_count++;
	} catch(std::bad_alloc& e) {
		throw AllocationError();
	}
}

void MutantSchool::MoveStudentToTeam(int stud_id, int team_id) {
	if(stud_id <= 0 || team_id <= 0)
		throw Failure();
	if(this->school_teams.Exists(team_id) == false
	|| this->students_by_id.Exists(stud_id) == false)
		throw Failure();
	Team* current = nullptr;
	if(this->student_teams.Exists(stud_id) == false)
		current = nullptr;
	else
		current = this->student_teams.findInTree(stud_id);
	Team* dest = this->school_teams.findInTree(team_id);
	if(team_id == current->GetID())
		return;

	Student* student = this->students_by_id.findInTree(stud_id);
	current->RemoveStudent(student);
	dest->AddStudent(student);
}

int MutantSchool::GetMostPowerful(int team_id) {

	if(team_id < 0)
		if(this->best_all != nullptr)
			return this->best_all->GetID();
		else
			throw Failure();
	else if(team_id == 0)
		throw Failure();
	else {
		if(this->school_teams.Exists(team_id) == false)
			throw Failure();
		Team* request_team = this->school_teams.findInTree(team_id);
		if(request_team->MostPowerfulInGroup() == nullptr)
			throw Failure();
		return request_team->MostPowerfulInGroup().GetID();
	}
}

void MutantSchool::RemoveStudent(int stud_id) {
	if(stud_id <= 0)
		throw Failure();
	if(this->students_by_id.Exists(stud_id) == false)
		throw Failure();

	Student* remove = this->students_by_id.findInTree(stud_id);
	int rem_power = remove->GetPower();
	Team* rem_team = nullptr;
	if(this->student_teams.Exists(stud_id) == false) //Check if the student was in a team
		rem_team = nullptr;
	else
		rem_team = this->student_teams.findInTree(stud_id);
	if(rem_team != nullptr)                          //If the student was in a team, remove him.
		rem_team->RemoveStudent(remove);
	StudentPower rem_pow(remove->GetID(), remove->GetPower());
	this->students_by_id.removeFromTree(stud_id);               //Removing from tree of ID.
	this->students_by_power.removeFromTree(rem_pow); //Removing from tree of power->Student
	this->student_teams.removeFromTree(stud_id);                //Removing from tree of student->team
	this->student_count--;
	if(this->best_all->GetID() == stud_id)                      //If the removed student was also the best.
		this->UpdatePowerful(); //Update the next most powerful student.
	delete remove;
}

Student** MutantSchool::GetAllStudentsByPower(int team_id) {
	if(team_id == 0)
		throw Failure();
	else if(team_id < 0)
		return this->students_by_power.ReverseInorderData();
	else {
		if(this->school_teams.Exists(team_id) == false)
			throw Failure();
		Team* get_all = this->school_teams.findInTree(team_id);
		return get_all->GetStudentsByPower();
	}
}

int GetCountInGrade(Student** stud_arr, int len, int grade) {
	int count = 0;
	for(int i = 0; i < len; i++) {
		if(stud_arr[i]->GetGrade() == grade)
			count++;
	}
	return count;
}

Student** StudentsOnlyInGrade(Student** stud_arr, int len, int grade) {
	int in_grade = GetCountInGrade(stud_arr, len, grade);
	Student** only_in_grade = new Student*[in_grade];
	int place = 0; // place < in_grade
	for(int i = 0; i < len; i++) {
		if(stud_arr[i]->GetGrade() == grade) {
			only_in_grade[place] = stud_arr[i];
			place++;
		}
	}
	return only_in_grade;
}

Student** NotInGrade(Student** studs_arr, int len, int grade) {
	int in_grade = GetCountInGrade(studs_arr, len, grade);
	Student** not_in_grade = new Student*[len - in_grade];
	int place = 0;
	for(int i = 0; i < len; i++) {
		if(studs_arr[i]->GetGrade() != grade) {
			not_in_grade[place] = studs_arr[i];
			place++;
		}
	}
	return not_in_grade;
}

StudentPower* PowerInGrade()

Student** MergeByPower(Student** arr1, int len1, Student** arr2, int len2) {
	Student** res = new Student*[len1 + len2];
}

//Solution does not currently meet the required complexity
//Also switch power and Student in students_by_power tree.
void MutantSchool::IncreaseLevel(int grade, int inc) {
	//For the whole school power tree:
	StudentPower* power_arr = this->students_by_power.ReverseInorderKeys();
	Student**     studs_arr = this->students_by_power.ReverseInorderData();
	int grade_count = GetCountInGrade(studs_arr, this->student_count, grade);
	Student** grade_arr = StudentsOnlyInGrade(studs_arr, grade_count, grade);
	Student** not_grade = NotInGrade(studs_arr, this->student_count, grade);
	//Split StudentPower array as well
	//Merge both pairs of arrays in parallel, or do one and the other as a key for which to take.
	//Insert both merged arrays into the AllPowers tree.
	//Do the same for every team that needs this as well, and explain why it is O(n+k) total.
}

//	if(grade <= 0 || inc <= 0)
//		throw Failure();
//	List<Student*> studs_in_grade;
//	//PROBLEM WITH ROW BELOW
//	List<Student*> all_students = this->students_by_id.ReverseInorderData();
//	List<Student*>::Iterator iter(all_students, true);
//	try {
//		while(true) {
//			if((*iter)->GetGrade() == grade)
//				studs_in_grade.PushBack(*iter);
//			iter.Next();
//		}
//	} catch(IteratorAtEnd& e) { }
//	List<Student*>::Iterator inc_level_iter(studs_in_grade, true);
//	Student* current = nullptr;
//	Team* current_team = nullptr;
//	try {
//		while(true) {
//			current = *inc_level_iter;
//			if(this->student_teams.Exists(current->GetID()))
//				current_team = this->student_teams.findInTree(current->GetID());
//			this->students_by_power.removeFromTree(StudentPower(current->GetID(), current->GetGrade()));
//			current_team->RemoveStudent(current);
//			current->UpdateGrade(grade);
//			current->UpdatePower(inc);
//			this->students_by_power.insertToTree(StudentPower(current->GetID(), current->GetPower()), current);
//			current_team->AddStudent(current);
//
//			current = nullptr;
//			current_team = nullptr;
//			inc_level_iter.Next();
//		}
//	} catch(IteratorAtEnd& e) { }
