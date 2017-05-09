/*
 * AVLTest.cpp
 *
 *  Created on: May 9, 2017
 *      Author: amit
 */

#include <iostream>
#include "avl_tree.h"
#include "List.h"

int main() {
	List<int> keys_list;
	List<std::string> data_list;

	keys_list.PushBack(1);
	keys_list.PushBack(6);
	keys_list.PushBack(5);
	keys_list.PushBack(4);
	keys_list.PushBack(2);
	keys_list.PushBack(3);
	data_list.PushBack("str1");
	data_list.PushBack("str6");
	data_list.PushBack("str5");
	data_list.PushBack("str4");
	data_list.PushBack("str2");
	data_list.PushBack("str3");

	List<int>::Iterator keys_iter(keys_list, true);
	List<std::string>::Iterator data_iter(data_list, true);

	AVLTree<int, std::string> tree;

	try {
		while(true) {
			std::cout << "Inserting: Key = " << *keys_iter << "\tData = " << *data_iter << std::endl;
			tree.insertToTree(*keys_iter, *data_iter);
			std::cout << "Number of elements in tree: " << tree.size();
			tree.PrintInorder();
			tree.PrintPreorder();
		}
	} catch(IteratorAtEnd& e) {
		std::cout << "\nFinished Insertion\n";
	}

	try {
		tree.insertToTree(1, "str1");
		std::cout << "\n BAD!!!!!!!! \n";
	} catch(AlreadyInTree& e) {
		std::cout << "Key already in tree." << "    GOOD" << std::endl;
	}
}
