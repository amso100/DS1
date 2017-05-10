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
enum TreeStatus{ Add,Remove};
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

	enum RollStatus {
			RR,
			RL,
			LR,
			LL,
			OK
		};

	AVLTreeNode(Key key, Data data);      //
	~AVLTreeNode(){};                    //
	AVLTreeNode(const AVLTreeNode& avl); //
	int GetHeight();                     //
	bool IsLeaf();                       //
	AVLTreeNode<Key, Data>* GetLeft();   //
	AVLTreeNode<Key, Data>* GetRight();  //
	void SetLeft(AVLTreeNode<Key, Data>* left);   //
	void SetRight(AVLTreeNode<Key, Data>* right); //
	int NumOfSons();					 //
	void IncHeight();                    //
	void SubHeight();                    //
	int BalanceFactor();                 //
	Key GetKey();                       //
	Data& GetData();                     //

	RollStatus GetStatus();              //
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


	AVLTreeNode<Key, Data>* root;

	void deleteTree(AVLTreeNode<Key,Data>* root);
	Data& findCurrentNode(AVLTreeNode<Key,Data>* node,Key key);
	void removeRoot(List<AVLTreeNode<Key,Data>*> route);
	void removeNode(AVLTreeNode<Key,Data>* father,bool cond_right,List<AVLTreeNode<Key,Data>*>& route);
	void removeRightLeaf(AVLTreeNode<Key,Data>* father);
	void removeRightOneSon(AVLTreeNode<Key,Data>* father);
	void removeRightTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route);
	void removeLeftLeaf(AVLTreeNode<Key,Data>* father);
	void removeLeftOneSon(AVLTreeNode<Key,Data>* father);
	void removeLeftTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route);
	void handleBF(List<AVLTreeNode<Key,Data>*>& route,TreeStatus status);
	void shiftRR(AVLTreeNode<Key,Data>* node);
	void shiftLL(AVLTreeNode<Key,Data>* node);
	void shiftRL(AVLTreeNode<Key,Data>* node);
	void shiftLR(AVLTreeNode<Key,Data>* node);
	void Preorder_aux(AVLTreeNode<Key,Data>* root);
	void Inorder_aux(AVLTreeNode<Key,Data>* root);
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

	AVLTree(const AVLTree&)=delete;
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
		right_h = this->right_node->height;
	if(this->left_node == nullptr)
		left_h = 0;
	else
		left_h = this->left_node->height;
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
typename AVLTreeNode<Key, Data>::RollStatus AVLTreeNode<Key, Data>::GetStatus() {
	if(this->BalanceFactor()==2){
		if(this->left_node->BalanceFactor() >= 0){
			return LL;
		}
		return LR;
	}
	if(this->BalanceFactor()==-2){
		if(this->left_node->BalanceFactor() <= 0){
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
	AVLTreeNode<Key, Data>* node = root;										//Create a node iterator
		while (node) {															//Travel-tree loop
			route.PushBack(node);												//Add the route to the list
			if (key == node->GetKey()) {
				throw AlreadyInTree();											//The node is already in
			}
			if (key < node->GetKey()) {												//If key lower, go left
				if (!node->GetLeft()) {
					if (node->IsLeaf()) {
						node->SetLeft(new AVLTreeNode<Key,Data>(key, data)); 					//No more left, create a new node
						handleBF(route, Add);
						break;
					}
					node->SetLeft(new AVLTreeNode<Key,Data>(key, data));
					break;
				}
				node = node->GetLeft();
				continue;
			}
			if (!node->GetRight()) {
				if (node->IsLeaf()) {
					node->SetRight(new AVLTreeNode<Key,Data>(key, data)); 										//No more left, create a new node
					handleBF(route, Add);
					break;
				}
				node->SetRight(new AVLTreeNode<Key,Data>(key, data));
				break;
			}
			node = node->GetRight();
		}
		if(root==nullptr){
			root = new AVLTreeNode<Key,Data>(key,data);
			numOfNodes++;
		}
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRoot(List<AVLTreeNode<Key,Data>*> route){
	if(this->root->IsLeaf()){									// If the root is a leaf, delete it!
		delete root;
		root=nullptr;
	}
	AVLTreeNode<Key,Data>* temp = root;							//If the root has 1 son, it's either the root and the right
	if(this->root->NumOfSons()==1){								//or the root and the left, replace and delete
		if(root->GetRight() == nullptr){
			temp = temp->GetLeft();
			delete root;
			root = temp;
		}
		temp = temp->GetRight();
		delete root;
		root = temp;
	}
	route.PushBack(temp);										//If the root has 2 sons, we'll pick the left son, travel the farthest
	temp = temp->GetRight();									//right, switch between the nodes, and delete the leaf.
	route.PushBack(temp);
	while(temp->GetLeft()!=nullptr){
		temp = temp->GetLeft();
		route.PushBack(temp);
	}
	route.RemoveLast();
	*(root) = *temp;
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
	delete temp;
	(*it)->SetRight(nullptr);
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRightLeaf(AVLTreeNode<Key,Data>* father){
	delete father->GetRight();									//If it's a leaf, simply delete him
	father->SetRight(nullptr);
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeLeftLeaf(AVLTreeNode<Key,Data>* father){
	delete father->GetLeft();
	father->SetLeft(nullptr);
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRightOneSon(AVLTreeNode<Key,Data>* father){
	AVLTreeNode<Key,Data>* temp = father->GetRight();			//If the node has one leaf, we connect the father to it's sub-tree
	if(temp->GetRight() == nullptr){							//and delete the node
		father->SetRight(temp->GetLeft());
		delete temp;
		return;
	}
	father->SetRight(temp->GetRight());
	delete temp;
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeLeftOneSon(AVLTreeNode<Key,Data>* father){
	AVLTreeNode<Key,Data>* temp = father->GetLeft();
	if(temp->GetRight() == nullptr){
		father->SetLeft(temp->GetLeft());
		delete temp;
		return;
	}
	father->SetLeft(temp->GetRight());
	delete temp;
	return;
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeRightTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route){
	AVLTreeNode<Key,Data>* temp = father->GetRight();			//If the node has 2 sons we track for the next value in key, switch the nodes
	route.PushBack(temp);										//and remove the leaf at the end
	AVLTreeNode<Key,Data>* next = temp->GetLeft();				//Must contain left, because 2 sons
	route.PushBack(next);
	while (next->GetRight() != nullptr){
		next = next->GetRight();
		route.PushBack(next);
	}
	route.RemoveLast();
	*temp = *(next);
	delete next;
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);		//The last node before the leaf.
	(*it)->SetRight(nullptr);
}

template<class Key, class Data>
void AVLTree<Key,Data>::removeLeftTwoSons(AVLTreeNode<Key,Data>* father,List<AVLTreeNode<Key,Data>*>& route){
	AVLTreeNode<Key,Data>* temp = father->GetLeft();			//Saves the pointer to switch with next
	route.PushBack(temp);
	AVLTreeNode<Key,Data>* next = temp->GetRight();				//Must contain left, because 2 sons
	route.PushBack(next);
	while (next->GetLeft() != nullptr){
		next = next->GetLeft();
		route.PushBack(next);
	}
	route.RemoveLast();
	*temp = *next;
	delete next;
	typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
	(*it)->SetRight(nullptr);
}



template<class Key, class Data>
void AVLTree<Key,Data>::removeNode(AVLTreeNode<Key,Data>* father,bool cond_right,List<AVLTreeNode<Key,Data>*>& route){
	if(cond_right){												//Check if the node we need to remove is left or right from the father
		if(father->GetRight()->IsLeaf()){
			removeRightLeaf(father);
		}
		if(father->GetRight()->NumOfSons() == 1){
			removeRightOneSon(father);
		}
		removeRightTwoSons(father,route);
	}
	if(father->GetLeft()->IsLeaf()){
		removeLeftLeaf(father);
	}
	if(father->GetLeft()->NumOfSons() == 1){
		removeLeftOneSon(father);
	}
	removeRightTwoSons(father,route);
}

template<class Key, class Data>
void AVLTree<Key, Data>::removeFromTree(Key key) {
	if(size()==0){												//If the tree is empty, nothing to remove
		throw EmptyTree();
	}
	bool cond_right;											//A variable to check which node to remove, left or right
	List<AVLTreeNode<Key,Data>*> route;							//A list of the route to track which nodes we visited
	AVLTreeNode<Key,Data>* node = root;
	while(!node){
		route.PushBack(node);
		if(node->GetKey() == key){
			if(node == root){
				route.RemoveLast();
				removeRoot(route);
				handleBF(route,Remove);
				return;
			}
			route.RemoveLast();
			typename List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
			removeNode(*it,cond_right,route);
			handleBF(route,Remove);
			return;
		}
		if(node->GetKey() < key){
			node = node->GetLeft();
			cond_right=false;
			continue;
		}
		node = node->GetRight();
		cond_right=true;
	}
	throw NotInTree();
}

template<class Key, class Data>
Data& AVLTree<Key, Data>::findCurrentNode(AVLTreeNode<Key, Data>* node,
		Key key) {
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
Data& AVLTree<Key, Data>::findInTree(Key key_tofind) {
	if (!root) {
		throw EmptyTree();
	}
	return this->findCurrentNode(root, key_tofind);

}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftLL(AVLTreeNode<Key, Data>* node) {
	if (!node) {
		return;
	}
	if (!node->GetLeft()) {
		return;
	}
	AVLTreeNode<Key, Data>* temp = node->GetLeft();

	node->SubHeight();
	temp->IncHeight();

	node->SetLeft(temp->GetRight());
	temp->SetRight(node);
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftRR(AVLTreeNode<Key, Data>* node) {
	if (!node) {
		return;
	}
	if (!node->GetRight()) {
		return;
	}

	AVLTreeNode<Key, Data>* temp = node->GetRight();

	node->SubHeight();
	temp->IncHeight();

	node->SetRight(temp->GetLeft());
	temp->SetLeft(node);
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftRL(AVLTreeNode<Key, Data>* node) {
	if (!node) {
		return;
	}
	if (!node->GetLeft()) {
		return;
	}
	shiftRR(node->GetLeft());
	shiftLL(node);
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftLR(AVLTreeNode<Key, Data>* node) {
	if (!node) {
		return;
	}
	if (!node->GetRight()) {
		return;
	}
	shiftLL(node->GetRight());
	shiftRR(node);
}

template<class Key, class Data>
void AVLTree<Key, Data>::handleBF(List<AVLTreeNode<Key,Data>*>& route,TreeStatus status) {
	if(status==Add){
		this->numOfNodes++;
	}
	if(status == Remove){
		this->numOfNodes--;
	}
	typename List<AVLTreeNode<Key, Data>*>::Iterator it(route, false);
	while (route.Size() != 0) {
		switch (status) {
		case Add:
			(*it)->IncHeight();
			break;
		case Remove:
			(*it)->SubHeight();
			break;
		};
		typename AVLTreeNode<Key, Data>::RollStatus res = (*it)->GetStatus();
		switch (res) {
		case (RL):						// Continue from here
			shiftRL(*it);
			break;
		case (RR):
			shiftRR(*it);
			break;
		case (LL):
			shiftLL(*it);
			break;
		case (LR):
			shiftLR(*it);
			break;
		case (OK):
			break;
		}
		try{
		   it.Prev();
		}
		catch(IteratorAtStart&){
			break;
		}
	}
}

template<class Key,class Data>
void AVLTree<Key,Data>::Preorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	std::cout << root->GetKey()<< " ";
	Preorder_aux(root->GetLeft());
	Preorder_aux(root->GetRight());
}

template<class Key,class Data>
void AVLTree<Key,Data>::Inorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	Inorder_aux(root->GetLeft());
	std::cout << root->GetKey()<< " ";
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

#endif /* AVL_TREE_H_ */
