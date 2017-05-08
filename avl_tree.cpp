/*
 * avl_tree.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: leschnitzky
 */
#include "avl_tree.h";
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
AVLTreeNode<Key, Data>::RollStatus GetStatus(){
	return RL;
}

/////////// AvlTree functions///////////////////////
template <class Key,class Data>
AVLTree<Key,Data>::AVLTree():numOfNodes(0){
	this->root = NULL;
}

template<class Key, class Data>
AVLTree<Key, Data>::~AVLTree() {
	deleteTree(this->root);
	root = NULL;
}

template<class Key, class Data>
void AVLTree<Key, Data>::deleteTree(AVLTreeNode<Key, Data>* root) {
	if (!root) {
		return;
	}
	deleteTree(root->left_node);
	deleteTree(root->right_node);
	delete root;
}

template<class Key, class Data>
void AVLTree<Key, Data>::insertToTree(Key key, Data data) {
	List<AVLTreeNode<Key, Data>> route;
	AVLTreeNode<Key, Data>* node = root;									//Create a node iterator
		while (!node) {															//Travel-tree loop
			route.PushBack(node);												//Add the route to the list
			if (key == *node->key) {
				throw AlreadyInTree();											//The node is already in
			}
			if (key < *node->key) {												//If key lower, go left
				if (!node->left_node) {
					if (node->isLeaf()) {
						node->left_node = new AVLTreeNode<Key, Data>(key, data); //No more left, create a new node
						handleBF(route, true);
						break;
					}
					node->left_node = new AVLTreeNode<Key, Data>(key, data);
					break;
				}
				node = node->left_node;
				continue;
			}
			if (!node->right_node) {
				if (node->isLeaf()) {
					node->right_node = new AVLTreeNode<Key, Data>(key, data); //No more left, create a new node
					handleBF(route, Add);
					break;
				}
				node->right_node = new AVLTreeNode<Key, Data>(key, data);
				break;
			}
			node = node->right_node;
		}

}
template<class Key, class Data>
void AVLTree<Key, Data>::removeFromTree(Key key) {
	bool cond_right;
	List<AVLTreeNode<Key,Data>*> route;
	AVLTreeNode<Key,Data> node = root;
	while(!node){
		route.PushBack(node);
		if(node.key == key){
			if(node == root){
				removeRoot();
			}
			route.RemoveLast();
			List<AVLTreeNode<Key,Data>*>::Iterator it(route,false);
			removeNode(*it,cond_right);
		}

	}
}

template<class Key, class Data>
Data& AVLTree<Key, Data>::findCurrentNode(AVLTreeNode<Key, Data>* node,
		Key key) {
	if (node->key == key)
		return node->data;
	if (!node->left_node && !node->right_node) {
		throw NotInTree();
	}
	if (node->key > key) {
		return findCurrentNode(node->right_node, key);
	}
	return findCurrentNode(node->left_node, key);
}

template<class Key, class Data>
Data& AVLTree<Key, Data>::findInTree(Key key_tofind) {
	if (!root) {
		throw EmptyTree();
	}
	try {
		return this->findCurrentNode(root, key_tofind);
	} catch (NotInTree&) {
		throw NotInTree();
	}

}

template<class Key, class Data>
void AVLTree<Key, Data>::shiftRR(AVLTreeNode<Key, Data>*& node) {
	if (!node) {
		return;
	}
	if (!node->left_node) {
		return;
	}
	AVLTreeNode<Key, Data>* temp = *node->left_node;
	*node->left_node = *temp->right_node
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
void AVLTree<Key, Data>::handleBF(List<AVLTreeNode<Key, Data>*> route,
		TreeStatus status) {
	List<AVLTreeNode<Key, Data>*>::Iterator it = route.end();
	while (route.size() != 0) {
		switch (status) {
		case Add:
			(*it)->IncHeight();
			break;
		case Remove:
			(*it)->SubHeight();
			break;
		}
		RollStatus res = (*it).GetStatus();
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
		it--;
	}
}

template<class Key,class Data>
void Preorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	std::cout << root->GetKey();
	Preorder_aux(root->left_node);
	Preorder_aux(root->right_node);
}

template<class Key,class Data>
void Inorder_aux(AVLTreeNode<Key,Data>* root) {
	if(root == nullptr)
		return;
	Inorder_aux(root->left_node);
	std::cout << root->GetKey();
	Inorder_aux(root->right_node);
}

