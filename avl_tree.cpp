/*
 * avl_tree.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: leschnitzky
 */
#include "avl_tree.h";
#include <list>
///////////////////Node functions////////////////////////////
template<class Key, class Data>
AVLTreeNode<Key, Data>::AVLTreeNode(Data data, Key key) :
		data(data), key(key) {
	left_node = NULL;
	right_node = NULL;
}

template<class Key, class Data>
AVLTreeNode<Key, Data>::AVLTreeNode(const AVLTreeNode& avl) {
	this->data = avl.data;
	this->key = avl.key;
	left_node = new AVLTreeNode*();
	right_node = new AVLTreeNode*();
	*left_node = *avl->left_node;
	*right_node = *avl->right_node;
}

/////////// AvlTree functions///////////////////////
template<class Key, class Data>
AVLTree<Key, Data>::AVLTree() :
		numOfNodes(0) {
	root = NULL;
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
	placeInTree(key, data, root);
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
	*node->left_node = *temp->right_node * temp->right_node = *node;
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
void AVLTree<Key, Data>::placeInTree(Key key, Data data,
		std::list<AVLTreeNode<Key, Data>> route) {
	AVLTreeNode<Key, Data>* node = root;									//Create a node iterator
	while (!node) {															//Travel-tree loop
		route.pushback(*node);												//Add the route to the list
		if (key == *node->key) {
			throw AlreadyInTree();											//The node is already in
		}
		if (key < *node->key) {												//If key lower, go left
			if (!node->left_node) {
				if (node->isLeaf()) {
					*(node->left_node) = AVLTreeNode<Key, Data>(key, data); //No more left, create a new node
					handleBF(route, true);
					break;
				}
				*(node->left_node) = AVLTreeNode<Key, Data>(key, data);
				break;
			}
			node = node->left_node;
			continue;
		}
		if (!node->right_node) {
			if (node->isLeaf()) {
				*(node->left_node) = AVLTreeNode<Key, Data>(key, data); //No more left, create a new node
				handleBF(route, Add);
				break;
			}
			*(node->left_node) = AVLTreeNode<Key, Data>(key, data);
			break;
		}
		node = node->right_node;
	}
}

template<class Key, class Data>
void AVLTree<Key, Data>::handleBF(std::list<AVLTreeNode<Key, Data>*> route,
		TreeStatus status) {
	std::list<AVLTreeNode<Key, Data>*>::iterator it = route.end();
	while (route.size() != 0) {
		switch (status) {
		case Add:
			*(*it)->incHeight();
			break;
		case Remove:
			*(*it)->subHeight();
			break;
		}
		RollStatus res = *(*it).checkBF();
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

