/*
 * library1.cpp
 *
 *  Created on: May 15, 2017
 *      Author: amit
 */

#include "library1.h"
#include "MutantSchool.h"

void* Init() {
	MutantSchool* school = new MutantSchool();
	return (void*)school;
}

StatusType AddStudent(void *DS, int StudentID, int Grade, int Power) {
	try {
		((MutantSchool*)DS)->AddStudent(StudentID, Grade, Power);
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType AddTeam(void *DS, int TeamID) {
	try {
		((MutantSchool*)DS)->AddTeam(TeamID);
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType MoveStudentToTeam(void *DS, int StudentID, int TeamID) {
	try {
		((MutantSchool*)DS)->MoveStudentToTeam(StudentID, TeamID);
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID) {
	try {
		int id = ((MutantSchool*)DS)->GetMostPowerful(TeamID);
		*StudentID = id;
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType RemoveStudent(void *DS, int StudentID) {
	try {
		((MutantSchool*)DS)->RemoveStudent(StudentID);
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType GetAllStudentsByPower(void *DS, int TeamID, int **Students, int *numOfStudents) {
	try {
		*Students = ((MutantSchool*)DS)->GetAllStudentsByPower(TeamID, numOfStudents);
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType IncreaseLevel(void *DS, int Grade, int PowerIncrease) {
	try {
		((MutantSchool*)DS)->IncreaseLevel(Grade, PowerIncrease);
		return SUCCESS;
	} catch(InvalidInput& e) {
		return INVALID_INPUT;
	} catch(Failure& e) {
		return FAILURE;
	} catch(AllocationError& e) {
		return ALLOCATION_ERROR;
	}
}

void Quit(void** DS) {
	 delete ((MutantSchool*)(*DS));
	*DS = nullptr;
}
