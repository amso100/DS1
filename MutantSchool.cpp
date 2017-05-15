/*
 * MutantSchool.cpp
 *
 *  Created on: May 11, 2017
 *      Author: amit
 */

#include "MutantSchool.h"
#include "exceptions.h"

MutantSchool::MutantSchool() {
	this->best_all = StudentPower(0, 0);
	this->student_count = 0;
	this->team_count = 0;
}

void MutantSchool::UpdatePowerful() {
	if(this->student_count == 0)
		this->best_all = StudentPower(0, 0);
	else
		this->best_all = this->students_by_power.getBiggestKey();
}

MutantSchool::~MutantSchool() {
	Team** all_teams = this->school_teams.InorderData();
	Student** all_students = this->students_by_id.InorderData();
	for(int i = 0; i < this->student_count; i++) {
		if(all_students[i] != nullptr)
			delete all_students[i];
	}
	for(int i = 0; i < this->school_teams.size(); i++) {
		if(all_teams[i] != nullptr)
			delete all_teams[i];
	}
	delete[] all_teams;
	delete[] all_students;
}

int MutantSchool::StudentsNum() {
	return this->student_count;
}

void MutantSchool::AddStudent(int id, int grade, int power) {
	if(id <= 0 || grade < 0 || power <= 0)
		throw InvalidInput();
	Student* create = nullptr;
	StudentPower cre_pair;
	try {
		if(this->students_by_id.Exists(id))
			throw Failure();
		create = new Student(id, grade, power);
		cre_pair = StudentPower(id, power);
		this->students_by_id.insertToTree(id, create);
		this->students_by_power.insertToTree(cre_pair, create);
		this->student_count++;
		if(this->student_count == 0)
			this->best_all = StudentPower(id, power);
		else
			if(this->best_all.GetPower() < power)
				this->best_all = StudentPower(id, power);

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
	if(current != nullptr && (team_id == current->GetID()))
		return;

	Student* student = this->students_by_id.findInTree(stud_id);
	if(current != nullptr) {
		current->RemoveStudent(student);
		this->student_teams.removeFromTree(stud_id);
	}
	dest->AddStudent(student);
	this->student_teams.insertToTree(stud_id, dest);
}

int MutantSchool::GetMostPowerful(int team_id) {

	if(team_id < 0)
		if(this->student_count > 0)
			return this->best_all.GetID();
		else
			throw Failure();
	else if(team_id == 0)
		throw Failure();
	else {
		if(this->school_teams.Exists(team_id) == false)
			throw Failure();
		Team* request_team = this->school_teams.findInTree(team_id);
		if(request_team->GetSize() == 0)
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
	this->student_teams.removeFromTree(stud_id);
	this->student_count--;
	if(this->best_all.GetID() == stud_id)                      //If the removed student was also the best.
		this->UpdatePowerful(); //Update the next most powerful student.
	delete remove;
}

StudentPower* MutantSchool::GetAllStudentsByPower(int team_id, int* size, int x) {
	if(team_id == 0)
		throw Failure();
	else if(team_id < 0) {
		StudentPower* temp = this->students_by_power.InorderKeys();
		StudentPower* arr = this->ReverseArray(temp, this->students_by_power.size());
		delete[] temp;
		*size = this->students_by_power.size();
		return arr;
	}
	else {
		if(this->school_teams.Exists(team_id) == false)
			throw Failure();
		Team* get_all = this->school_teams.findInTree(team_id);
		return get_all->GetStudentsByPower(size);
	}
}

int*  MutantSchool::GetAllStudentsByPower(int team_id, int* size) {
	StudentPower* arr = this->GetAllStudentsByPower(team_id, size, 0);
	int* res = new int[*size];
	for(int i = 0; i < *size; i++) {
		res[i] = arr[i].GetID();
	}
	delete[] arr;
	return res;
}

int MutantSchool::GetCountInGrade(Student** stud_arr, int len, int grade) {
	int count = 0;
	for(int i = 0; i < len; i++) {
		if(stud_arr[i]->GetGrade() == grade)
			count++;
	}
	return count;
}

Student** MutantSchool::StudentsOnlyInGrade(Student** stud_arr, int len, int grade) {
	int in_grade = GetCountInGrade(stud_arr, this->student_count, grade);
	Student** only_in_grade = new Student*[in_grade];
	int place = 0; // place < in_grade
	for(int i = 0; i < this->student_count; i++) {
		if(stud_arr[i]->GetGrade() == grade) {
			only_in_grade[place] = stud_arr[i];
			place++;
		}
	}
	return only_in_grade;
}

Student** MutantSchool::NotInGrade(Student** studs_arr, int len, int grade) {
	int in_grade = GetCountInGrade(studs_arr, this->student_count, grade);
	Student** not_in_grade = new Student*[len - in_grade];
	int place = 0;
	for(int i = 0; i < this->student_count; i++) {
		if(studs_arr[i]->GetGrade() != grade) {
			not_in_grade[place] = studs_arr[i];
			place++;
		}
	}
	return not_in_grade;
}

StudentPower* MutantSchool::PowerInGrade(Student** students, StudentPower* power_arr, int len, int grade) {
	int in_grade = GetCountInGrade(students, this->student_count, grade);
	StudentPower* power_in_grade = new StudentPower[in_grade];
	int place = 0;
	for(int i = 0; i < this->student_count; i++) {
		if(students[i]->GetGrade() == grade) {
			power_in_grade[place] = power_arr[i];
			place++;
		}
	}
	return power_in_grade;
}

StudentPower* MutantSchool::PowerNotGrade(Student** students, StudentPower* power_arr, int len, int grade) {
	int in_grade = GetCountInGrade(students, this->student_count, grade);
	StudentPower* power_in_grade = new StudentPower[len - in_grade];
	int place = 0;
	for(int i = 0; i < this->student_count; i++) {
		if(students[i]->GetGrade() != grade) {
			power_in_grade[place] = power_arr[i];
			place++;
		}
	}
	return power_in_grade;
}

Student** MutantSchool::MergeStudsByPower(Student** arr1, int len1, Student** arr2, int len2) {
	Student** res = new Student*[len1 + len2];
	int i1 = 0, i2 = 0, i3 = 0;
	while(i1 != len1 && i2 != len2) {
		if(arr1[i1]->GetPower() > arr2[i2]->GetPower())
			res[i3++] = arr1[i1++];
		else
			res[i3++] = arr2[i2++];
	}
	while(i1 < len1)
		res[i3++] = arr1[i1++];
	while(i2 < len2)
		res[i3++] = arr2[i2++];
	return res;
}

StudentPower* MutantSchool::MergePairsByPower(StudentPower* arr1, int len1, StudentPower* arr2, int len2) {
	StudentPower* res = new StudentPower[len1 + len2];
	int i1 = 0, i2 = 0, i3 = 0;
	while(i1 != len1 && i2 != len2) {
		if(arr1[i1].GetPower() > arr2[i2].GetPower())
			res[i3++] = arr1[i1++];
		else
			res[i3++] = arr2[i2++];
	}
	while(i1 < len1)
		res[i3++] = arr1[i1++];
	while(i2 < len2)
		res[i3++] = arr2[i2++];
	return res;
}

//Solution does not currently meet the required complexity
//Also switch power and Student in students_by_power tree.
void MutantSchool::IncreaseLevel(int grade, int inc) {
	//For the whole school power tree:
	StudentPower* temp = this->students_by_power.InorderKeys();
	StudentPower* power_arr = this->ReverseArray(temp, this->students_by_power.size());
	delete[] temp;
	Student**     temp2 = this->students_by_power.InorderData();
	Student**     studs_arr = this->ReverseStudents(temp2, this->students_by_power.size());
	delete[] temp2;
	int grade_count = GetCountInGrade(studs_arr, this->student_count, grade);
	Student** grade_arr = StudentsOnlyInGrade(studs_arr, grade_count, grade);
	Student** not_grade = NotInGrade(studs_arr, this->student_count, grade);
	StudentPower* grade_power = PowerInGrade(studs_arr, power_arr, this->student_count, grade);
	StudentPower* not_pow_grade = PowerNotGrade(studs_arr, power_arr, this->student_count, grade);
	for(int i = 0; i < grade_count; i++) {
		grade_arr[i]->UpdatePower(inc);
		grade_power[i].SetPower(inc);
	}
	Student** updated_studs = MergeStudsByPower(grade_arr, grade_count, not_grade, this->student_count-grade_count);
	StudentPower* updated_pairs = MergePairsByPower(grade_power, grade_count, not_pow_grade, this->student_count - grade_count);
	this->students_by_power.UpdateTreeFromArrays(updated_pairs, this->student_count, updated_studs, this->student_count);

	//Do for every team as well.
	Team** all_teams = this->school_teams.InorderData();
	for(int i = 0; i < this->school_teams.size(); i++) {
		all_teams[i]->IncreaseLevel(grade, inc);
	}
	delete[] all_teams;
	delete[] power_arr;
	delete[] studs_arr;
	delete[] grade_arr;
	delete[] not_grade;
	delete[] grade_power;
	delete[] not_pow_grade;
	delete[] updated_studs;
	delete[] updated_pairs;
}

StudentPower* MutantSchool::ReverseArray(StudentPower* arr, int len) {
	if(len == 0)
		return nullptr;
	StudentPower* reverse = new StudentPower[len];
	for(int i=0; i<len; i++)
		reverse[len - i - 1] = arr[i];
	return reverse;
}

Student** MutantSchool::ReverseStudents(Student** arr, int len) {
	if(len == 0)
		return nullptr;
	Student** reverse = new Student*[len];
	for(int i=0; i<len; i++)
		reverse[len - i - 1] = arr[i];
	return reverse;
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
