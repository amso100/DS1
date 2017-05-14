/*
 * exceptions.h
 *
 *  Created on: May 7, 2017
 *      Author: amit
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

class ListException { };
class IteratorAtEnd : public ListException { };
class IteratorAtStart : public ListException { };

class SchoolException {};
class AllocationError : public SchoolException {};
class InvalidInput    : public SchoolException {};
class Failure         : public SchoolException {};

#endif /* EXCEPTIONS_H_ */
