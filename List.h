/*
 * List.h
 *
 *  Created on: May 7, 2017
 *      Author: amit
 */

#ifndef LIST_H_
#define LIST_H_

/*
 * Class for describing a list to which elements can only be inserted,
 * and an iteration is possible.
 */

#include <iostream>
#include "exceptions.h"

template<typename Data> class List {
protected:

	/*
	 * Class for describing a single 2-direction node in the list.
	 */
	class Node {
	private:
		Data data;  //The node's data
		Node* next; //The next node
		Node* prev; //The previous node
	public:

		// Creates a new node with the given data.
		Node(Data data) : data(data), next(nullptr), prev(nullptr) { }

		//Creates a new node with a set next and previous nodes.
		Node(Data data, Node* next, Node* prev) : data(data), next(next), prev(prev) { }

		//Destroys the current node.
		~Node() { }

		//Returns the data stored in the current node.
		Data& GetData() { return this->data; }

		//Returns the next node after the given one.
		Node* GetNext() { return this->next; }

		//Sets a new value for the next node.
		void  SetNext(Node* set) { this->next = set; }

		//Returns the node before the given one.
		Node* GetPrev() { return this->prev; }

		//Sets the node before the given one.
		void  SetPrev(Node* set) { this->prev = prev; }
	};
private:
	int count;   //The current amount of nodes in the list.
	Node* first; //The first node in the list.
	Node* last;  //The last node in the list.
public:

	/*
	 * Class for describing an iterator for the list (forwards and backwards).
	 */
	class Iterator {
	private:
		Node* cur_node; //The current node the iterator is at.
		List& cur_list; //The current list of iteration.
	public:

		//Creates a new iterator at the start/end of the list.
		Iterator(List<Data>& list, bool start) : cur_list(list) {
			if(start)
				this->cur_node = cur_list.first;
			else
				this->cur_node = cur_list.last;
		}

		//Destroys the given iterator.
		~Iterator() { }

		//Returns the data the current iterator points to.
		Data& operator*() const {
			return this->cur_node->GetData();
		}

		//Advances the iterator to the next node.
		//Throws IteratorAtEnd if at the end of the list.
		void Next() {
			if(this->cur_node->GetNext() == nullptr)
				throw IteratorAtEnd();
			this->cur_node = this->cur_node->GetNext();
		}

		//Retreats the iterator to the previous node.
		//Throws IteratorAtStart if at the start of the list.
		void Prev() {
			if(this->cur_node->GetPrev() == nullptr)
				throw IteratorAtStart();
			this->cur_node = this->cur_node->GetPrev();
		}
	};
public:

	//Creates a new empty list.
	List() : count(0), first(nullptr), last(nullptr) { }

	//Destroys the current list, and all data stored in it.
	~List() {
		Node* cur = this->first;
		Node* temp;
		while(cur != nullptr) {
			temp = cur;
			cur = cur->GetNext();
			delete temp;
		}
	}

	//Returns the size of the current list.
	int Size() { return this->count; }

	//Adds a Data object to the end of the list.
	void PushBack(Data data) {
		if(this->first == nullptr) {
			this->first = new Node(data);
			this->last = this->first;

		}
		else {//If more than 0 nodes:
			Node* insert = new Node(data, nullptr, this->last);
			this->last->SetNext(insert);
			this->last = insert;
		}
		this->count++;
	}

	void RemoveLast() {
		if(this->last == nullptr)
			return;
		else if(this->last == this->first) {
			delete this->first;
			this->first  = nullptr;
			this->last   = nullptr;
		}
		else {
			Node* temp = this->last;
			this->last = this->last->GetPrev();
			this->last->SetNext(nullptr);
			delete temp;
		}
		this->count--;
	}

	//Prints the list in regular order.
	void PrintRegular() {
		Node* cur = this->first;
		while(cur->GetNext() != nullptr) {
			std::cout << cur->GetData() << "\n";
			cur = cur->GetNext();
		}
		std::cout << cur->GetData();
	}

	//Prints the list in reverse order.
	void PrintReverse() {
		Node* cur = this->last;
		while(cur->GetPrev() != nullptr) {
			std::cout << cur->GetData() << "\n";
			cur = cur->GetPrev();
		}
		std::cout << cur->GetData();
	}
};

#endif /* LIST_H_ */
