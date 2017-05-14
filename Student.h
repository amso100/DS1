/*
 * Student.h
 *
 *  Created on: Apr 27, 2017
 *      Author: amit
 */

#ifndef STUDENT_H_
#define STUDENT_H_

/*
 * Class for describing a single student of the school.
 */

#include "exceptions.h"

class Student {
private:
	int student_id;
	int grade;
	int power;
public:

	//Creates a new student with a given ID, grade, and power.
	explicit Student(int id, int grade, int power);

	//Destroys the current student.
	~Student();

	//Returns the ID of the current student.
	int GetID();

	//Returns the grade of the student.
	int GetGrade();

	//Returns the student's power.
	int GetPower();

	//Updatees the student's grade.
	void UpdateGrade(int gr);

	//Updates the student's power.
	void UpdatePower(int pw);

	bool operator<(const Student& other);
	bool operator==(const Student& other);
};

#endif /* STUDENT_H_ */
