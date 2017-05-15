/*
 * StudentPower.h
 *
 *  Created on: May 13, 2017
 *      Author: amit
 */

#ifndef STUDENTPOWER_H_
#define STUDENTPOWER_H_

/*
 * Class for describing the pair of student his power level.
 */
class StudentPower {
private:
	int student_id;
	int power;
public:
	StudentPower();
	StudentPower(int id, int pow);
	~StudentPower();
	int GetID();
	int GetPower();
	void SetPower(int pow);
	bool operator==(const StudentPower& other);
	bool operator<(const StudentPower& other);
	void operator=(const StudentPower& other);
};

#endif /* STUDENTPOWER_H_ */
