/*
 * avl_tree.h
 *
 *  Created on: Apr 29, 2017
 *      Author: leschnitzky
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>

/**
 * The Node of the AVL tree.
 * privates:
 * 		key - The key of the note in the binary search tree.
 * 		data - The data associated with the key.
 * 		left,right nodes - A pointer, carrying the sons of the node.
 *
 * 	functions:
 * 		constructor, destructor, copy-constructor.
 */
template <class Key,class Data>
class AVLTreeNode{
	Key key;
	Data data;
	int balanceFactor;
	AVLTreeNode* left_node;
	AVLTreeNode* right_node;
public:
	AVLTreeNode(Data data,Key key);
	~AVLTreeNode(){};
	AVLTreeNode(const AVLTreeNode& avl);
	int getBF(){
		return this->balanceFactor;
	}
};

/**
 * The AVLTree:
 * privates:
 * 		numOfNodes - the number of nodes in the tree
 * 		root - A pointer to the head of the tree
 *
 * 	functions:
 * 		constructor,destructor, (no copy constructor)
 * 		findInTree -  gets a key, and checks the tree if a node containing that key, exists.
 * 		insertToTree - 	gets key and data parameters, checks whether a node containing that key
 * 					   exists, then adds a new node in it's correct place. afterwards fixes the
 * 					   tree to fit the AVL Tree rules.
 * 		removeFromTree - gets a key, and checks if a node containing that key, exists.
 * 						 if it does, it removes it, and fixes the tree to fit the AVL Tree ruling.
 * 						 otherwise, alerts the user.
 * 		getNodeBF - gets a key to a node,the function returns the balance factor of that node,
 * 					if a node doesn't exists returns the appropriate exception.
 * 		size - returns the amount of nodes in the tree.
 *
 */
template<class Key,class Data>
class AVLTree{
	int numOfNodes;
	AVLTreeNode* root;

	void deleteTree(AVLTreeNode<Key,Data>* root);
	Data& findCurrentNode(AVLTreeNode<Key,Data>* node,Key key);
	void placeInTree(AVLTreeNode<Key,Data>* node);
	void shiftRR(AVLTreeNode<Key,Data>* node);
	void shiftLL(AVLTreeNode<Key,Data>* node);
	void shiftRL(AVLTreeNode<Key,Data>* node);
public:
	AVLTree();
	~AVLTree();

	// Test Functions/////
	bool testAllBFs(AVLTreeNode<Key,Data>* node){
		if(!node){
			return true;
		}
		if((*node->getBF()< -1)||(*node->getBF()> 1)){
			return false;
		}
		return ((testAllBFs(*node->left_node))&&(testAllBFs(*node->right_node)));
	}

	void addValuesToTree(Data* array,AVLTreeNode<Key,Data>* node){
		if(!node){
			return;
		}
		addValuesToTree(array,*node->left_node);
		*array = *node->data;
		addValuesToTree(array+1,*node->right_node);
		return;
	}
	bool testSearchTree(AVLTreeNode<Key,Data>* node){
		if(!node){
			return false;
		}
		Data array[]= new Data[numOfNodes];
		addValuesToTree(array,root);
		for(int i=0;i<numOfNodes-1;i++){
			if(array[i]>=array[i+1]){
				return false;
			}
		}
		delete array;
		return true;
	}
	///// The rest of the tree functions//////
	Data& findInTree(Key key_tofind);
	void  insertToTree(Key key,Data data);
	void  removeFromTree(Key key);
	int getNodeBF(Key key);
	int size();

	AVLTree(const AVLTree&)=delete;
};


/*
 * The exceptions of the tree
 * 		AlreadyInTree - A node with the same key exists in the tree (in Insertion)
 * 		NotInTree - There does not exist a node with a key (in Deletion or Search)
 * 		EmptyTree - The current tree is empty
 */
class TreeExceptions: public std::exception{};
class AlreadyInTree: public TreeExceptions{};
class NotInTree: public TreeExceptions{};
class EmptyTree: public TreeExceptions{};




#endif /* AVL_TREE_H_ */
