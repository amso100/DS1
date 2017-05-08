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
AVLTreeNode<Key,Data>::AVLTreeNode(Data data,Key key): data(data),key(key){
		left_node=NULL;
		right_node=NULL;
		this->height = 0;
}

template<class Key, class Data>
AVLTreeNode<Key, Data>::AVLTreeNode(const AVLTreeNode& avl) {
	this->data = avl.data;
	this->key = avl.key;
	left_node = new AVLTreeNode*();
	right_node = new AVLTreeNode*();
	*left_node = *avl->left_node;
	*right_node = *avl->right_node;
	this->height = avl.height;
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
Key& AVLTreeNode<Key, Data>::GetKey() {
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

	List<AVLTreeNode<Key, Data>> route;
	AVLTreeNode<Key, Data>* node = root;										//Create a node iterator
		while (!node) {															//Travel-tree loop
			route.PushBack(node);												//Add the route to the list
			if (key == node->GetKey()) {
				throw AlreadyInTree();											//The node is already in
			}
			if (node->GetKey() < key) {												//If key lower, go left
				if (!node->GetLeft()) {
					if (node->IsLeaf()) {
						node->SetLeft(new AVLTreeNode<Key,Data>(key, data)); 					//No more left, create a new node
						handleBF(route, true);
						break;
					}
					node->SetLeft(new AVLTreeNode<Key,Data>(key, data));
					break;
				}
				node = node->GetLeft();
				continue;
			}
			if (!node->GetRight()) {
				if (node->isLeaf()) {
					node->SetRight(new AVLTreeNode<Key,Data>(key, data)); 										//No more left, create a new node
					handleBF(route, Add);
					break;
				}
				node->SetRight(new AVLTreeNode<Key,Data>(key, data));
				break;
			}
			node = node->GetRight();
		}

}

template<class Key, class Data>
void AVLTree<Key,Data>::removeNode(AVLTreeNode<Key,Data>* father,bool cond_right){
	if(cond_right){
		if(father->GetRight()->IsLeaf()){
			delete father->GetRight();
			father->SetRight(nullptr);
		}
		if(father->)
	}
}

template<class Key, class Data>
void AVLTree<Key, Data>::removeFromTree(Key key) {
	if(size()==0){
		throw EmptyTree();
	}
	bool cond_right;
	List<AVLTreeNode<Key,Data>*> route;
	AVLTreeNode<Key,Data> node = root;
	while(!node){
		route.PushBack(node);
		if(node.GetKey() == key){
			if(node == root){
				removeRoot(route);
				handleBF(route,Remove);
				return;
			}
			route.RemoveLast();
			List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
			removeNode(*it,cond_right);
			handleBF(route,Remove);
			return;
		}
		if(node.GetKey() < key){
			node = node->GetLeft();
			continue;
		}
		node = node->GetRight();
	}
	throw NotInTree();
}

template<class Key, class Data>
Data& AVLTree<Key, Data>::findCurrentNode(AVLTreeNode<Key, Data>* node,
		Key key) {
	if (node->GetKey() == key)
		return node->data;
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
void AVLTree<Key, Data>::shiftRR(AVLTreeNode<Key, Data>*& node) {
	if (!node) {
		return;
	}
	if (!node->GetLeft()) {
		return;
	}
	AVLTreeNode<Key, Data>* temp = *node->GetLeft();
	node->SetLeft(temp->GetRight());
	*temp->right_node = *node;
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftLL(AVLTreeNode<Key, Data>*& node) {
	if (!node) {
		return;
	}
	if (!node->right_node) {
		return;
	}
	AVLTreeNode<Key, Data>* temp = *node->right_node;
	*node->right_node = *temp->left_node;
	temp->left_node = *node;
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftRL(AVLTreeNode<Key, Data>*& node) {
	if (!node) {
		return;
	}
	if (!node->left_node) {
		return;
	}
	shiftRR(node->left_node);
	shirtLL(node);
}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftLR(AVLTreeNode<Key, Data>*& node) {
	if (!node) {
		return;
	}
	if (!node->right_node) {
		return;
	}
	shiftLL(node->right_node);
	shirtRR(node);
}

template<class Key, class Data>
void AVLTree<Key, Data>::handleBF(List<AVLTreeNode<Key,Data>*>& route,TreeStatus status) {
	List<AVLTreeNode<Key, Data>*>::Iterator it(route, false);
	while (route.size() != 0) {
		switch (status) {
		case Add:
			(*it)->IncHeight();
			break;
		case Remove:
			(*it)->SubHeight();
			break;
		};
		AVLTreeNode<Key, Data>::RollStatus res = (*it)->GetStatus();
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
		it.Prev();
	}
}

template<class Key,class Data>
void AVLTree<Key,Data>::Preorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	std::cout << root->GetKey();
	Preorder_aux(root->GetLeft());
	Preorder_aux(root->GetRight());
}

template<class Key,class Data>
void AVLTree<Key,Data>::Inorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	Inorder_aux(root->GetLeft());
	std::cout << root->GetKey();
	Inorder_aux(root->GetRight());
}

