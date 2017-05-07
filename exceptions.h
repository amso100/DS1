/*
 * exceptions.h
 *
 *  Created on: May 7, 2017
 *      Author: amit
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

class ListException : public std::exception { };
class IteratorAtEnd : public ListException { };
class IteratorAtStart : public ListException { };

#endif /* EXCEPTIONS_H_ */
