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

class Student {
private:
	int student_id;
	int grade;
	int power;
public:
	explicit Student(int id, int grade, int power);
	~Student();
	int GetID();
	int GetGrade();
	int GetPower();
	void UpdateGrade(int gr);
	void UpdatePower(int pw);
};

#endif /* STUDENT_H_ */
