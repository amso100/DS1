/*
 * Team.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: amit
 */

#include "Team.h"

Team::Team(int id) {
	this->team_id = id;
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
	if(this->team_size == 0)
		this->best = StudentPower(student->GetID(), student->GetPower());
	if(this->best.GetPower() < student->GetPower())
		this->best = StudentPower(student->GetID(), student->GetPower());
	this->team_size++;
}

void Team::RemoveStudent(Student* student) {
	try {
		this->team_students.removeFromTree(StudentPower(student->GetID(), student->GetPower()));
	} catch(NotInTree& e) {
		return;
	}
	if(this->best.GetID() == student->GetID())
		this->UpdateMostPowerful();
	this->team_size--;
}

StudentPower Team::MostPowerfulInGroup() {
	return this->best;
}

StudentPower* Team::GetStudentsByPower(int* size) {
	StudentPower* arr = this->team_students.ReverseInorderKeys();
	*size = this->team_size;
	return arr;
}

void Team::UpdateMostPowerful() {
	StudentPower most_power = this->team_students.getBiggestKey();
	this->best = most_power;
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

StudentPower* PowerInGrade(Student** students, StudentPower* power_arr, int len, int grade) {
	int in_grade = GetCountInGrade(students, len, grade);
	StudentPower* power_in_grade = new StudentPower[in_grade];
	int place = 0;
	for(int i = 0; i < len; i++) {
		if(students[i]->GetGrade() == grade) {
			power_in_grade[place] = power_arr[i];
			place++;
		}
	}
	return power_in_grade;
}

StudentPower* PowerNotGrade(Student** students, StudentPower* power_arr, int len, int grade) {
	int in_grade = GetCountInGrade(students, len, grade);
	StudentPower* power_in_grade = new StudentPower[len - in_grade];
	int place = 0;
	for(int i = 0; i < len; i++) {
		if(students[i]->GetGrade() != grade) {
			power_in_grade[place] = power_arr[i];
			place++;
		}
	}
	return power_in_grade;
}

Student** MergeStudsByPower(Student** arr1, int len1, Student** arr2, int len2) {
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

StudentPower* MergePairsByPower(StudentPower* arr1, int len1, StudentPower* arr2, int len2) {
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


void Team::IncreaseLevel(int grade, int inc) {
	StudentPower* power_arr = this->team_students.ReverseInorderKeys();
	Student**     studs_arr = this->team_students.ReverseInorderData();
	int grade_count = GetCountInGrade(studs_arr, this->team_size, grade);
	Student** grade_arr = StudentsOnlyInGrade(studs_arr, grade_count, grade);
	Student** not_grade = NotInGrade(studs_arr, this->team_size, grade);
	StudentPower* grade_power = PowerInGrade(studs_arr, power_arr, this->team_size, grade);
	StudentPower* not_pow_grade = PowerNotGrade(studs_arr, power_arr, this->team_size, grade);
	Student** updated_studs = MergeStudsByPower(grade_arr, grade_count, not_grade, this->team_size-grade_count);
	StudentPower* updated_pairs = MergePairsByPower(grade_power, grade_count, not_pow_grade, this->team_size - grade_count);
	this->team_students.UpdateTreeFromArrays(updated_pairs, this->team_size, updated_studs, this->team_size);
}
