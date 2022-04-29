#pragma once
#include "DataStructuresForHeap.h"
#include <vector>
#include <math.h>
#include <iostream>

#define NOTINHEAP -1
#define INFINITY INT32_MAX

using namespace std;

// graphEdge    = {int ver1, int ver2}
// heapNode     = {graphEdge data, int weight}

class MinHeap
{
	// להכניס רק רשת אחת מהגרף (את הקשת הנגדית לא להכניס)
	
private:
	
	vector<heapNode> heap;
	vector<int> vertexToPlace;  //each vertex has it's own place in the heap

	// heapSize == heap.size()

public:

	MinHeap(vector<int> min);  	// נקבל ב ctor את גודל המערך

	void build(vector<int> min);
	void fixHeap(int index);
	heapNode deleteMin();
	bool isEmpty();
	void deceaseKey(int place, int newKey);

	bool leftChildExists(int index);
	bool rightChildExists(int index);

	// Getters:

	// These functions don't check if the child or parent exit! Be sure to check before calling them.
	int getParent(int index);
	int getLeftChild(int index);
	int getRightChild(int index);

	heapNode getMin() const;

	// Setters:
};
