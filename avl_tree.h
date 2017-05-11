/*
 * avl_tree.h
 *
 *  Created on: Apr 29, 2017
 *      Author: leschnitzky
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>
#include "List.h"

enum RollStatus{ LR,RR,LL,RL,OK };
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
	int height;
	AVLTreeNode<Key, Data>* left_node;
	AVLTreeNode<Key, Data>* right_node;
public:

	AVLTreeNode(Key key, Data data);     		  //Node constructor
	~AVLTreeNode(){};                   		  //Node Destructor
	AVLTreeNode(const AVLTreeNode& avl); 		  //Copy Constructor
	int GetHeight();                     		  //Function to get height of a node
	bool IsLeaf();                       	   	  //Checks if the node is leaf
	AVLTreeNode<Key, Data>* GetLeft();   		  //Gets the left node
	AVLTreeNode<Key, Data>* GetRight();  		  //Gets the right node
	void SetLeft(AVLTreeNode<Key, Data>* left);   //Sets the left node
	void SetRight(AVLTreeNode<Key, Data>* right); //Sets the right node
	int NumOfSons();							  //Returns the number of sons the node has
	void SetHeight(int height);					  //Sets the Height of a node
	void IncHeight();                   		  //Increases the Height of the node by 1
	void SubHeight();                    	 	  //Decreases the height of the node by 1
	int BalanceFactor();                 	      //Returns the balance factor of the node
	Key GetKey();                       		  //Gets the key from the node
	Data& GetData();                    		  //Gets the data from the node
	RollStatus GetStatus();             		  //Gets the status telling the node which rotation it needs to follow
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
	enum TreeStatus{ Add,Remove,NAdd,NRemove};
	int numOfNodes;
	AVLTreeNode<Key, Data>* root;

	// Private Functions /////////////////////////////////////////////////////////////////////////////////////////////////////
	void deleteTree(AVLTreeNode<Key,Data>* root);															//Removes the tree for the destructor.
	Data& findCurrentNode(AVLTreeNode<Key,Data>* node,Key key);												//A function for recursive search for the find function
	void removeRoot(List<AVLTreeNode<Key,Data>*> route);													//Removes the root and handles heights and AVL connections
	void removeNode(AVLTreeNode<Key,Data>* father,bool cond_right,List<AVLTreeNode<Key,Data>*>& route);		//Removes the node and handles heights and AVL connections
	void removeRightLeaf(AVLTreeNode<Key,Data>* father);													//Conditionals for the node remove
	void removeRightOneSon(AVLTreeNode<Key,Data>* father);
	void removeRightTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route);
	void removeLeftLeaf(AVLTreeNode<Key,Data>* father);
	void removeLeftOneSon(AVLTreeNode<Key,Data>* father);
	void removeLeftTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route);
	void handleBF(List<AVLTreeNode<Key,Data>*>& route,TreeStatus status);
	void shiftRR(AVLTreeNode<Key,Data>* node,List<AVLTreeNode<Key,Data>*>& route);
	void shiftLL(AVLTreeNode<Key,Data>* node,List<AVLTreeNode<Key,Data>*>& route);
	void shiftRL(AVLTreeNode<Key,Data>* node,List<AVLTreeNode<Key,Data>*>& route);
	void shiftLR(AVLTreeNode<Key,Data>* node,List<AVLTreeNode<Key,Data>*>& route);
	void Preorder_aux(AVLTreeNode<Key,Data>* root);
	void Inorder_aux(AVLTreeNode<Key,Data>* root);
	std::vector<Key> RevInorderAux(std::vector<Key>& vec, AVLTreeNode<Key, Data> root);
public:
	AVLTree();
	~AVLTree();
	Data& findInTree(Key key_tofind);
	void  insertToTree(Key key,Data data);
	void  removeFromTree(Key key);
	int getNodeBF(Key key);
	int size();
	void PrintInorder();
	void PrintPreorder();
	bool Exists(Key key);

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

	AVLTree(const AVLTree&)=delete;																				//No copy constructor for tree
};


/*
 * The exceptions of the tree
 * 		AlreadyInTree - A node with the same key exists in the tree (in Insertion)
 * 		NotInTree - There does not exist a node with a key (in Deletion or Search)
 * 		EmptyTree - The current tree is empty
 */
class TreeExceptions   : public std::exception {};
class AlreadyInTree    : public TreeExceptions {};
class NotInTree        : public TreeExceptions {};
class EmptyTree        : public TreeExceptions {};
class InvalidHeight    : public TreeExceptions {};

/*
 * avl_tree.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: leschnitzky
 */
#include "avl_tree.h"
#include "List.h"

///////////////////Node functions////////////////////////////
template <class Key,class Data>
AVLTreeNode<Key,Data>::AVLTreeNode(Key key, Data data): key(key), data(data){
		this->left_node = nullptr;
		this->right_node = nullptr;
		this->height = 0;
}

template<class Key, class Data>
AVLTreeNode<Key, Data>::AVLTreeNode(const AVLTreeNode<Key, Data>& avl) {
	this->data        = avl.data;
	this->key         = avl.key;
	this->left_node   = avl.left_node;
	this->right_node  = avl.right_node;
	this->height      = avl.height;
}

template <class Key,class Data>
void AVLTreeNode<Key,Data>::SetHeight(int height) {
	this->height=height;
}

template <class Key,class Data>
void AVLTreeNode<Key,Data>::IncHeight() {
	this->height++;
}

template <class Key,class Data>
void AVLTreeNode<Key,Data>::SubHeight() {
	this->height--;
}

template <class Key,class Data>
bool AVLTreeNode<Key, Data>::IsLeaf() {
	return (this->right_node == nullptr && this->left_node == nullptr);
}

template <class Key,class Data>
AVLTreeNode<Key, Data>* AVLTreeNode<Key, Data>::GetLeft() {
	return this->left_node;
}

template <class Key,class Data>
AVLTreeNode<Key, Data>* AVLTreeNode<Key, Data>::GetRight() {
	return this->right_node;
}

template <class Key,class Data>
void AVLTreeNode<Key, Data>::SetLeft(AVLTreeNode<Key, Data>* left) {
	this->left_node = left;
}

template <class Key,class Data>
void AVLTreeNode<Key, Data>::SetRight(AVLTreeNode<Key, Data>* right) {
	this->right_node = right;
}

template <class Key,class Data>
int AVLTreeNode<Key, Data>::NumOfSons() {
	if(this->IsLeaf()){
		return 0;
	}
	if(this->right_node != nullptr){
		if(this->left_node != nullptr){
			return 2;
		}
		return 1;
	}
	return 1;
}

template <class Key,class Data>
int AVLTreeNode<Key, Data>::GetHeight() {
	return this->height;
}

template <class Key,class Data>
int AVLTreeNode<Key, Data>::BalanceFactor() {
	if(this->IsLeaf())
		return 0;
	int right_h, left_h;
	if(this->right_node == nullptr)
		right_h = 0;
	else
		right_h = (this->right_node->height + 1);
	if(this->left_node == nullptr)
		left_h = 0;
	else
		left_h = (this->left_node->height + 1);
	return left_h - right_h;
}

template <class Key,class Data>
Key AVLTreeNode<Key, Data>::GetKey() {
	return this->key;
}

template <class Key,class Data>
Data& AVLTreeNode<Key, Data>::GetData() {
	return this->data;
}

template <class Key,class Data>
RollStatus AVLTreeNode<Key, Data>::GetStatus() {
	int balance_left;											//To check the right son's balance factor
	int balance_right;											//To check the left son's balance factor
	if(this->left_node == nullptr)
		balance_left = 0;
	else
		balance_left = this->left_node->BalanceFactor();
	if(this->right_node == nullptr)
		balance_right = 0;
	else
		balance_right = this->right_node->BalanceFactor();

	if(this->BalanceFactor()==2){								//Returns status according the requirements for the rotation
		if(balance_left >= 0){
			return LL;
		}
		return LR;
	}
	if(this->BalanceFactor()==-2){
		if(balance_right <= 0){
			return RR;
		}
		return RL;
	}
	return OK;
}

/////////// AvlTree functions///////////////////////
template <class Key,class Data>
AVLTree<Key,Data>::AVLTree():numOfNodes(0){
	this->root = NULL;
}

template<class Key, class Data>
AVLTree<Key, Data>::~AVLTree() {
	deleteTree(this->root);
	this->root = NULL;
}

template<class Key, class Data>
int AVLTree<Key, Data>::size() {
	return this->numOfNodes;
}

template<class Key, class Data>
void AVLTree<Key, Data>::deleteTree(AVLTreeNode<Key, Data>* root) {
	if (!root) {
		return;
	}
	deleteTree(root->GetLeft());
	deleteTree(root->GetRight());
	delete root;
}

template<class Key, class Data>
void AVLTree<Key, Data>::insertToTree(Key key, Data data) {

	List<AVLTreeNode<Key, Data>*> route;
	AVLTreeNode<Key, Data>* node = root;											//Create a node iterator
		while (node) {																//Travel-tree loop
			route.PushBack(node);													//Add the route to the list
			if (key == node->GetKey()) {
				throw AlreadyInTree();												//The node is already in
			}
			if (key < node->GetKey()) {												//If key lower, go left
				if (node->GetLeft() == nullptr) {
					if (node->IsLeaf()) {											//If the new node added to a leaf, update route +1
						node->SetLeft(new AVLTreeNode<Key,Data>(key, data));		//Adds a new node
						handleBF(route, Add);										//Handles the AVL requirements
						break;
					}
					node->SetLeft(new AVLTreeNode<Key,Data>(key, data));
					node->GetLeft()->SetHeight(root->GetHeight()-route.Size());
					handleBF(route,NAdd);											//If added to a node with a son, no need to add +1 to route
					break;
				}
				node = node->GetLeft();
				continue;
			}																		//The same process for the right side.
			if (node->GetRight() == nullptr) {
				if (node->IsLeaf()) {
					node->SetRight(new AVLTreeNode<Key,Data>(key, data));
					handleBF(route, Add);
					break;
				}
				node->SetRight(new AVLTreeNode<Key,Data>(key, data));
				node->GetRight()->SetHeight(root->GetHeight()-route.Size());
				handleBF(route,NAdd);
				break;
			}
			node = node->GetRight();
		}
		if(root==nullptr){
			root = new AVLTreeNode<Key,Data>(key,data);
			handleBF(route, Add);
		}
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRoot(List<AVLTreeNode<Key,Data>*> route){
	if(root->IsLeaf()){
		delete root;
		root = nullptr;
		return;
	}
	AVLTreeNode<Key,Data>* temp = root;									//If the root has 1 son, it's either the root and the right
	if(this->root->NumOfSons()==1){										//or the root and the left, replace and delete
		if(root->GetRight() == nullptr){
			temp = temp->GetLeft();
			delete root;
			root = temp;
		}
		temp = temp->GetRight();
		delete root;
		root = temp;
	}
	route.PushBack(temp);												//If the root has 2 sons, we'll pick the left son, travel the farthest
	temp = temp->GetLeft();												//right, switch between the nodes, and delete the leaf.
	route.PushBack(temp);												//add the route to the node we're switching
	while(temp->GetRight()!=nullptr){									//Loop until we get to the last right node possible
		temp = temp->GetRight();
		route.PushBack(temp);
	}
	route.RemoveLast();													//Switch the nodes
	int height = root->GetHeight();
	temp->SetRight(root->GetRight());
	temp->SetLeft(root->GetLeft());
	*(root) = *temp;
	root->SetHeight(height);
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
	delete temp;
	(*it)->SetRight(nullptr);
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRightLeaf(AVLTreeNode<Key,Data>* father){
	delete father->GetRight();											//If it's a leaf, simply delete him
	father->SetRight(nullptr);
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeLeftLeaf(AVLTreeNode<Key,Data>* father){
	delete father->GetLeft();											//If it's a leaf, simply delete him
	father->SetLeft(nullptr);
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRightOneSon(AVLTreeNode<Key,Data>* father){
	AVLTreeNode<Key,Data>* temp = father->GetRight();				//If the node has one leaf, we connect the father to it's sub-tree
	if(temp->GetRight() == nullptr){								//and delete the node
		father->SetRight(temp->GetLeft());
		delete temp;
		return;
	}
	father->SetRight(temp->GetRight());
	if(father->GetLeft()->GetHeight()==0){							//From AVL tree, right side must contain node
		father->SetHeight(1);										//We decrease the height
	}
	delete temp;
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeLeftOneSon(AVLTreeNode<Key,Data>* father){
	AVLTreeNode<Key,Data>* temp = father->GetLeft();				//In an AVL tree if the node contains one son, the son is a leaf.
	if(temp->GetRight() == nullptr){
		father->SetLeft(temp->GetLeft());
		delete temp;
		return;
	}
	father->SetLeft(temp->GetRight());
	if(father->GetRight()->GetHeight()==0){							//From AVL tree, right side must contain node
		father->SetHeight(1);										//We decrease the height
	}
	delete temp;
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRightTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route){
	AVLTreeNode<Key,Data>* temp = father->GetRight();						//If the node has 2 sons we track for the next value in key, switch the nodes
	route.PushBack(temp);													//and remove the leaf at the end
	AVLTreeNode<Key,Data>* next = temp->GetLeft();							//Must contain left, because 2 sons
	route.PushBack(next);													//We save the route to the leaf we switch
	while (next->GetRight() != nullptr){									//Loop to get the leaf we want to switch
		next = next->GetRight();
		route.PushBack(next);
	}
	route.RemoveLast();														//Switch the nodes
	*temp = *(next);
	temp->SetRight(next->GetRight());
	temp->SetLeft(next->GetLeft());
	delete next;
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);		//The last node before the leaf.
	(*it)->SetRight(nullptr);
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeLeftTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route){
	AVLTreeNode<Key,Data>* temp = father->GetLeft();						//Saves the pointer to switch with next
	route.PushBack(temp);
	AVLTreeNode<Key,Data>* next = temp->GetRight();							//Must contain left, because 2 sons
	route.PushBack(next);													//We save the route to the leaf we switch
	while (next->GetLeft() != nullptr){										//Loop to get the leaf we want to switch
		next = next->GetLeft();
		route.PushBack(next);
	}
	route.RemoveLast();
	*temp = *next;															//Switch the nodes
	temp->SetRight(next->GetRight());
	temp->SetLeft(next->GetLeft());
	delete next;
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
	(*it)->SetRight(nullptr);
}



template<class Key, class Data>
void AVLTree<Key,Data>::removeNode(AVLTreeNode<Key,Data>* father,bool cond_right,List<AVLTreeNode<Key,Data>*>& route){
	if(cond_right){												//Check if the node we need to remove is left or right from the father
		if(father->GetRight()->IsLeaf()){
			removeRightLeaf(father);
			return;
		}
		if(father->GetRight()->NumOfSons() == 1){
			removeRightOneSon(father);
			return;
		}
		removeRightTwoSons(father,route);
		return;
	}
	if(father->GetLeft()->IsLeaf()){
		removeLeftLeaf(father);
		return;
	}
	if(father->GetLeft()->NumOfSons() == 1){
		removeLeftOneSon(father);
		return;
	}
	removeRightTwoSons(father,route);
}

template<class Key, class Data>
void AVLTree<Key, Data>::removeFromTree(Key key) {
	if(size()==0){															//If the tree is empty
		throw EmptyTree();
	}
	bool cond_right;														//A variable to check which node to remove, left or right
	List<AVLTreeNode<Key,Data>*> route;										//A list of the route to track which nodes we visited
	AVLTreeNode<Key,Data>* node = root;										//Start the search from the root
	while(node != nullptr){													//Loop on the tree
		route.PushBack(node);												//Add the current node to the route of the tree
		if(node->GetKey() == key){											//In case we found the node
			if(node == root){												//If it's the root
				route.RemoveLast();
				removeRoot(route);
				handleBF(route,Remove);
				return;
			}
			route.RemoveLast();												//If it's not the root
			typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
			removeNode(*it,cond_right,route);
			handleBF(route,Remove);
			return;
		}
		if(key < node->GetKey()){											//If we go left
			node = node->GetLeft();
			cond_right=false;
			continue;
		}
		node = node->GetRight();											//if we go right
		cond_right=true;
	}
	throw NotInTree();
}

template<class Key, class Data>
Data& AVLTree<Key, Data>::findCurrentNode(AVLTreeNode<Key, Data>* node,
		Key key) {										//Recursive find in the tree.
	if (node->GetKey() == key)
		return node->GetData();
	if (!node->GetLeft() && !node->GetRight()) {
		throw NotInTree();
	}
	if (node->GetKey() > key) {
		return findCurrentNode(node->GetRight(), key);
	}
	return findCurrentNode(node->GetLeft(), key);
}

template<class Key, class Data>
Data& AVLTree<Key, Data>::findInTree(Key key_tofind) {			//Calls the recursive find in the tree.
	if (!root) {
		throw EmptyTree();
	}
	return this->findCurrentNode(root, key_tofind);

}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftLL(AVLTreeNode<Key, Data>* node,List<AVLTreeNode<Key,Data>*>& route) {
	if (!node) {														//If there is no node, can't rotate
		return;
	}
	if (!node->GetLeft()) {												//If the node doesn't have a left son, can't rotate
		return;
	}
	AVLTreeNode<Key, Data>* temp = node->GetLeft();						//We assign the left son as a temporary node
	int height= node->GetHeight();
	if(node->GetHeight() > 1){											//We need to lower the node to be the left node's son, so the height decreases by 2
	node->SetHeight(height - 2);
	}
	else{
		node->SetHeight(0);												//If it's only the node and it's left son, the height updates
	}


	node->SetLeft(temp->GetRight());									//Update the pointers
	temp->SetRight(node);

	if(node->GetLeft()!=nullptr){										//If the node carried a sub tree- reserve the height
		node->SetHeight(node->GetLeft()->GetHeight()+1);
		temp->SetHeight(node->GetLeft()->GetHeight()+2);
	}

	if(root->GetKey() == node->GetKey()){								//If it's the root, switch the root with the temp
		root = temp;
		route.RemoveLast();
		route.PushBack(root);
		return;
	}
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
	it.Prev();															// not root at least 1 previous node
	if((*it)->GetLeft()!=nullptr){
		if((*it)->GetLeft()->GetKey() == node->GetKey()){
			(*it)->SetLeft(temp);
			route.RemoveLast();
			return;
		}
	}
	(*it)->SetRight(temp);
	route.RemoveLast();
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftRR(AVLTreeNode<Key, Data>* node,List<AVLTreeNode<Key,Data>*>& route) {
	if (!node) {												//Symetric to the LL method on the other side.
		return;
	}
	if (!node->GetRight()) {
		return;
	}

	AVLTreeNode<Key, Data>* temp = node->GetRight();
	int height= node->GetHeight();
	if(node->GetHeight() > 1){
		node->SetHeight(height - 2);
	}
	else{
		node->SetHeight(0);
	}

	node->SetRight(temp->GetLeft());
	temp->SetLeft(node);
	if(node->GetRight()!=nullptr){
		node->SetHeight(node->GetRight()->GetHeight()+1);
		temp->SetHeight(node->GetRight()->GetHeight()+2);
	}

	if(root->GetKey() == node->GetKey()){
		root = temp;
		route.RemoveLast();
		route.PushBack(root);
		return;
	}
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
	it.Prev();
	if((*it)->GetLeft()!=nullptr){
		if((*it)->GetLeft()->GetKey() == node->GetKey()){
			(*it)->SetLeft(temp);
			route.RemoveLast();
			return;
		}
	}
	(*it)->SetRight(temp);
	route.RemoveLast();
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftRL(AVLTreeNode<Key, Data>* node,List<AVLTreeNode<Key,Data>*>& route) {
	if (!node) {											//Same as before, if no nodes, can't do the rotation
		return;
	}
	if (!node->GetRight()) {
		return;
	}
	route.PushBack(node->GetRight());
	node->GetRight()->GetLeft()->IncHeight();				//Updates the heights of the nodes,
	node->GetRight()->IncHeight();
	shiftLL(node->GetRight(),route);						//First LL the right node with it's left
	shiftRR(node,route);									//Then RR the father with it's right node

}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftLR(AVLTreeNode<Key, Data>* node,List<AVLTreeNode<Key,Data>*>& route) {
	if (!node) {											//Symetric to the RL method.
		return;
	}
	if (!node->GetLeft()) {
		return;
	}
	route.PushBack(node->GetLeft());
	node->GetLeft()->GetRight()->IncHeight();
	node->GetLeft()->IncHeight();
	shiftRR(node->GetLeft(),route);
	shiftLL(node,route);
}

template<class Key, class Data>
void AVLTree<Key, Data>::handleBF(List<AVLTreeNode<Key,Data>*>& route,TreeStatus status) {
	if((status==Add )||(status==NAdd)){														//If we add, inc the total number of nodes
		this->numOfNodes++;
	}
	if((status==Remove )||(status==NRemove)){												//If we remove,decrease the total number
		this->numOfNodes--;
	}
	int factor=0,height;																	//factor to manage the height, height to store the height of the node
	while (route.Size() != 0) {																//Loop to travel the route of the action
		typename List<AVLTreeNode<Key, Data>*>::Iterator it(route, false);
		switch (status) {
		case Add:
			height=(*it)->GetHeight();														//Manage the height of adding items;
			(*it)->SetHeight(height-factor+1);
			break;
		case Remove:
			height=(*it)->GetHeight();														//Manage the height of removing items
			(*it)->SetHeight(height+factor-1);
			break;
		default: break;																		//otherwise, do nothing
		};
		RollStatus res = (*it)->GetStatus();												//Gets the BF from the node and calculates which rotation to do
		switch (res) {
		case (RL):																			//For each rotation we lower the tree's total height by 1
			shiftRL(*it,route);
			factor++;
			break;
		case (RR):
			shiftRR(*it,route);
			factor++;
			break;
		case (LL):
			shiftLL(*it,route);
			factor++;
			break;
		case (LR):
			shiftLR(*it,route);
			factor++;
			break;
		case (OK):
			route.RemoveLast();
			break;
		};
	}
}

template<class Key,class Data>
Key AVLTree<Key,Data>::getBiggestKey(){
	if(root==nullptr){																	//If the tree is empty.
		throw EmptyTree();
	}
	AVLTreeNode<Key,Data>* node = root;													//travel to the right from the root
	while(node->right != nullptr){
		node= node->GetRight();
	}
	return node->GetKey();																//Return the key
}

template<class Key,class Data>
void AVLTree<Key,Data>::Preorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	std::cout << root->GetKey()<< ","<<root->GetHeight()<< " ";
	Preorder_aux(root->GetLeft());
	Preorder_aux(root->GetRight());
}

template<class Key,class Data>
void AVLTree<Key,Data>::Inorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	Inorder_aux(root->GetLeft());
	std::cout << root->GetKey()<< ","<<root->GetHeight()<<" ";
	Inorder_aux(root->GetRight());
}

template<class Key, class Data>
void AVLTree<Key,Data>::PrintPreorder() {
	this->Preorder_aux(this->root);
}

template<class Key, class Data>
void AVLTree<Key,Data>::PrintInorder() {
	this->Inorder_aux(this->root);
}

template<class Key, class Data>
std::vector<Key> AVLTree<Key, Data>::ReverseInorderKeys() {
	std::vector<Key> vec;
	return RevInorderAux(vec, this->root);
}

template<class Key, class Data>
std::vector<Key> AVLTree<Key, Data>::RevInorderAux(std::vector<Key>& vec, AVLTreeNode<Key, Data> root) {
	if(root.IsLeaf())
		vec.push_back(root.GetKey());
	else {
		vec += RevInorderAux(vec, root.GetRight());
		vec.push_back(root.GetKey());
		vec += RevInorderAux(vec, root.GetLeft());
	}
	return vec;
}

template<class Key, class Data>
bool AVLTree<Key, Data>::Exists(Key key) {
	try {
		this->findInTree(key);
		return true;
	} catch(NotInTree& e) {
		return false;
	}
}

#endif /* AVL_TREE_H_ */
