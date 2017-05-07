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
	class Node {
	private:
		Data data;
		Node* next;
		Node* prev;
	public:
		Node(Data data) : data(data), next(nullptr), prev(nullptr) { }
		Node(Data data, Node* next, Node* prev) : data(data), next(next), prev(prev) { }
		~Node() { }
		Data& GetData() { return this->data; }
		Node* GetNext() { return this->next; }
		void  SetNext(Node* set) { this->next = set; }
		Node* GetPrev() { return this->prev; }
		void  SetPrev(Node* set) { this->prev = prev; }
	};
private:
	int count;
	Node* first;
	Node* last;
public:
	class Iterator {
	private:
		Node* cur_node;
		List* cur_list;
	public:
		Iterator(List<Data>* list, bool start) : cur_list(list) {
			if(start)
				this->cur_node = list->first;
			else
				this->cur_node = list->last;
		}
		~Iterator() { }
		Data& operator*() const {
			return this->cur_node->GetData();
		}
		void Next() {
			if(this->cur_node->GetNext() == nullptr)
				throw IteratorAtEnd();
			this->cur_node = this->cur_node->GetNext();
		}
		void Prev() {
			if(this->cur_node->GetPrev() == nullptr)
				throw IteratorAtStart();
			this->cur_node = this->cur_node->GetPrev();
		}
	};
public:
	List() : count(0), first(nullptr), last(nullptr) { }
	~List() {
		Node* cur = this->first;
		Node* temp;
		while(cur != nullptr) {
			temp = cur;
			cur = cur->GetNext();
			delete temp;
		}
	}
	int Size() { return this->count; }
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

	void PrintRegular() {
		Node* cur = this->first;
		while(cur->GetNext() != nullptr) {
			std::cout << cur->GetData() << "\n";
			cur = cur->GetNext();
		}
		std::cout << cur->GetData();
	}

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
