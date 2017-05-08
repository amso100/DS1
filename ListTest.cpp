/*
 * ListTest.cpp
 *
 *  Created on: May 7, 2017
 *      Author: amit
 */

#include "List.h"
#include "exceptions.h"
#include <iostream>

int main() {
	List<std::string> test;
	test.PushBack("String 1");
	test.PushBack("String 2");
	test.PushBack("String 3");
	test.PushBack("String 4");
	test.PushBack("String 69");
	test.PushBack("String 420");

	std::cout << "List has " << test.Size() << " elements. Printing...\n";
	test.PrintRegular();
	std::cout << "\n\n";

	std::cout << "Testing iterator forward...\n";
	List<std::string>::Iterator iter(test, true);
	try {
		while(true) {
			std::cout << *iter << "\n";
			iter.Next();
		}
	} catch(ListException& e) {
		std::cout << "End of list.\n";
	}
	std::cout << "Finished test forward.\n";
	std::cout << "Testing iterator backwards...\n";
	List<std::string>::Iterator iter2(test, false);
	try {
		while(true) {
			std::cout << *iter2 << "\n";
			iter2.Prev();
		}
	} catch(ListException& e) {
		std::cout << "Start of list.\n";
	}

	std::cout << "Printing list in reverse...\n";
	test.PrintReverse();

	std::cout << "Removing last twice...\n";
	test.RemoveLast();
	test.RemoveLast();
	List<std::string>::Iterator iter3(test, false);
	std::cout << "Last object in list is: " << *iter3 << "\n";
}
