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

	List<int> second_insert;
	List<std::string> second_data;

	second_insert.PushBack(7);
	second_insert.PushBack(9);
	second_insert.PushBack(11);
	second_data.PushBack("str7");
	second_data.PushBack("str9");
	second_data.PushBack("str11");

	AVLTree<int, std::string> tree;

	//Insertion testing:
	try {
		while(true) {
			std::cout << "Inserting: Key = " << *keys_iter << "\tData = " << *data_iter << std::endl;
			tree.insertToTree(*keys_iter, *data_iter);
			keys_iter.Next();
			data_iter.Next();
			std::cout << "Number of elements in tree: " << tree.size();
			std::cout << "Printing inorder...\n";
			tree.PrintInorder();
			std::cout << "Printing preorder...\n";
			tree.PrintPreorder();
		}
	} catch(IteratorAtEnd& e) {
		std::cout << "\nFinished Insertion\n";
	}

	//Inserting existing key:
	try {
		tree.insertToTree(1, "str1");
		std::cout << "\n BAD!!!!!!!! \n";
	} catch(AlreadyInTree& e) {
		std::cout << "Key already in tree." << "    GOOD" << std::endl;
	}

	//Finding existing key:
	try {
		std::cout << "Data of key 4 is " << tree.findInTree(4) << "    GOOD" << std::endl;
	} catch (NotInTree& e) {
		std::cout << "Key is not in tree." << "    BAD" << std::endl;
	}

	//Finding non-existing key: (Should throw exception)
	try {
		std::cout << "Data of key 4 is " << tree.findInTree(69) << "    BAD" << std::endl;
	} catch (NotInTree& e) {
		std::cout << "Key is not in tree." << "    GOOD" << std::endl;
	}

	//Removing root test:
	try {
		std::cout << "Removing Key=4 from tree (currently root)...\n";
		tree.removeFromTree(4);
	} catch (...) {
		std::cout << "Error removing root (not good)." << std::endl;
	}

	List<int>::Iterator second_keys(second_insert, true);
	List<std::string>::Iterator data_second(second_data, true);

	//Adding some more to make things more interesting...
	try {
		while(true) {
			tree.insertToTree(*second_keys, *data_second);
			second_keys.Next(); data_second.Next();
			std::cout << "Number of keys now: " << tree.size() << std::endl;
			std::cout << "Printing inorder...\n";
			tree.PrintInorder();
			std::cout << "Printing preorder...\n";
			tree.PrintPreorder();
		}
	} catch (IteratorAtEnd& e) {
		std::cout << "Finished insertion 2.\n";
	} catch (...) {
		std::cout << "Error. NOT GOOD.\n";
	}

	//Creating removal order list:
	List<int> removal_keys;
	removal_keys.PushBack(5);
	removal_keys.PushBack(2);
	removal_keys.PushBack(7);
	removal_keys.PushBack(3);
	removal_keys.PushBack(9);
	removal_keys.PushBack(1);
	removal_keys.PushBack(11);
	removal_keys.PushBack(6);
	List<int>::Iterator remove_iter(removal_keys, true);

	//Removing the nodes in the given order from the list:
	try {
		while(true) {
			tree.removeFromTree(*remove_iter);
			remove_iter.Next();
			std::cout << "Number of keys now: " << tree.size() << std::endl;
			std::cout << "Printing inorder...\n";
			tree.PrintInorder();
			std::cout << "Printing preorder...\n";
			tree.PrintPreorder();
		}
	} catch(IteratorAtEnd& e) {
		if(tree.size() == 0)
			std::cout << "Finished removing tree.    GOOD";
		else
			std::cout << "Removing from tree NOT GOOD.";
	} catch(...) {
		std::cout << "Error removing from tree    NOT GOOD";
	}
}
