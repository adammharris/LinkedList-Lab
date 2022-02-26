#pragma once
#include <string>
#include <sstream>
#include <exception>
#include <iostream>

using namespace std;

template<typename T>
class LinkedList {
private:
	struct Node {
		T data;
		Node* next;
	};
	Node* head;
	bool isInList(T value, Node* &iter) {
		// Returns true is any node in list contains value
		// Also changes iter to node before node with value
		if (head == NULL)
			return false; // check for size == 0
		if (head->data == value)
			return true; // check head
		if (head->next == NULL)
			return false; // check for size == 1
		do {
			if (iter->next->data == value)
				return true; //check body
			iter = iter->next;
		} while (iter->next != NULL);
		if (iter->data == value)
			return true; //check tail
		return false; // If this returns, iter->next = tail
	}
public:
	LinkedList() {
		head = NULL;
	}
	~LinkedList() {
		clear();
	}
	void insertHead(T value) { 
    Node* iter = head;
    if (isInList(value, iter))
			return;
		Node* newHead = new Node();
		newHead->data = value;
		if (head == NULL) {
			head = newHead;
			return;
		}
		Node* oldHead = head;
		head = newHead;
		head->next = oldHead;
	}
	void insertTail(T value) {
		if (head == NULL) { // If size == 0
			insertHead(value);
			return;
		}
		Node* iter = head;
		if (isInList(value, iter))
			return; // After this, assume iter == tail
		Node* newTail = new Node();
		newTail->data = value;
		newTail->next = NULL;
		iter->next = newTail;
	}

	void insertAfter(T value, T insertionNode) {
		if (head == NULL) // check for size == 0
			return;
		Node* iter = head;
		if (isInList(value, iter))
			return; // see if value is in list
		iter = head;
		if (!isInList(insertionNode, iter))
			return; // see if insertionNode is in list
		Node* newNode = new Node();
		newNode->data = value;
		if (head->data == insertionNode) {
			Node* temp = head->next;
			head->next = newNode;
			newNode->next = temp;
			return;
		}

		newNode->next = iter->next->next;
		iter->next->next = newNode;
	}
	void remove(T value) {
		if (head == NULL) // Check for size == 0
			return;
		if (head->data == value) { // If head must be removed
			Node* toDelete = head;
			head = head->next;
			delete toDelete;
			return;
		}
		Node* iter = head;
		if (!isInList(value, iter))
			return;
		Node* toDelete = iter->next;
		iter->next = toDelete->next;
		delete toDelete;
	}

	void clear() {
		if (head == NULL)
			return;
		do {
			remove(head->data);
		} while (head->next != NULL);
    Node* toDelete = head;
		head = NULL;
		delete toDelete;
	}

	T at(int index) {
		if (head == NULL)
			throw out_of_range("Index is invalid: list is empty");
		if (index == 0)
			return head->data;
		if (index < 0)
			throw out_of_range("Index is invalid: below 0");
		int currentIndex = 0;
		Node* iter = head;
		while (iter->next != NULL) {
			iter = iter->next;
			currentIndex++;
			if (currentIndex == index)
				return iter->data;
		}
		throw out_of_range("Index is invalid: greater than size of list");
	}

	int size() {
		if (head == NULL) {
			return 0;
		}
		int sizeOfList = 1;
		Node* iter = head;
		while (iter->next != NULL) {
			sizeOfList++;
			iter = iter->next;
		}
		return sizeOfList;
	};

	string toString() {
		if (head == NULL) // check if size == 0
			return "";
		stringstream ss;
		ss << head->data;
		if (head->next == NULL)
			return ss.str();
		Node* iter = head;
		while (iter->next != NULL) {
			ss << ' ';
			iter = iter->next;
			ss << iter->data;

		}
		return ss.str();
	};

};

