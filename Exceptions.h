/*
 * Exceptions.h
 *
 *  Created on: Apr 27, 2017
 *      Author: amit
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

class SchoolException {};
class AllocationError : public SchoolException {};
class InvalidInput    : public SchoolException {};
class Failure         : public SchoolException {};

#endif /* EXCEPTIONS_H_ */
