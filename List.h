#pragma once
#include "Node.h"

class List
{
private:
	Node* head;
	Node* tail;

public:
	List();
	~List();

	void makeEmptyList();
	bool isEmpty();
	void removeFromList(int val);
	bool isInList(int val);

	// Getters:

	Node* getHead();
	Node* getTail();

	// Setters:

	void insertToHead(int vertex, int weight);
	void insertToTail(int vertex, int weight);

	void printList(int graphVertex);
	void printListBack();
	List* duplicateList();
};

