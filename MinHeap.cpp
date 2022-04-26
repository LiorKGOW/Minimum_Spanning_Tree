#include "MinHeap.h"

/*********************************************************************/
MinHeap::MinHeap(vector<weightedEdge> edges) {

	build(edges);
}

/*********************************************************************/
/*
 * In this bulild function we will use Floyd Algorithm to build the Heap
 */
void MinHeap::build(vector<weightedEdge> edges) {

	heap.reserve(edges.capacity());

	for (int i = 0; i < edges.size(); i++) {

		graphEdge e = { edges[i].ver1, edges[i].ver2 };
		heapNode tmp = { e, edges[i].weight };

		heap.push_back(tmp);
	}

	for (int i = edges.size() / 2 - 1; i >= 0; i--) {

		fixHeap(i);
	}
}

/*********************************************************************/
/*
 * fixHeap is a Recursive function
 */
void MinHeap::fixHeap(int index) {

	int indexToCheck = index;
	int left = getLeftChild(index);
	int right = getRightChild(index);
	heapNode tmp;

	if (rightChildExists(index) && leftChildExists(index))
	{
		if (heap[left].weight < heap[right].weight)
			indexToCheck = left;
		else
			indexToCheck = right;
		if (heap[index].weight > heap[indexToCheck].weight)
		{
			tmp = heap[index];
			heap[index] = heap[indexToCheck];
			heap[indexToCheck] = tmp;

			fixHeap(indexToCheck);
		}
	}
	else if (!rightChildExists(index) && leftChildExists(index)) {

		if (heap[index].weight > heap[left].weight)
		{
			tmp = heap[index];
			heap[index] = heap[left];
			heap[left] = tmp;

			fixHeap(left);
		}
	}

	// else, the heap is fixed. No more switches required.
}

/*********************************************************************/
heapNode MinHeap::deleteMin() {

	if (heap.size() < 1) {

		// ERROR ?
	}

	heapNode min = heap[0];

	heap[0] = heap[heap.size() - 1];

	heap.pop_back();  // heapSize-- 

	fixHeap(0);

	return min;
}

/*********************************************************************/
bool MinHeap::isEmpty() {

	if (heap.size() == 0)
		return true;

	return false;
}

/*********************************************************************/
/*
 * deceaseKey changes the weight of heap[place] to newKey and fixes the heap, if necessary.
 * ASSUMPTION: newKey <= heap[place].weight 
 */
void MinHeap::deceaseKey(int place, int newKey) {

	if (place >= heap.size()) {

		// TODO: ERROR place is out of bounds of the heap.
	}

	if (newKey > heap[place].weight) {

		// TODO: ERROR trying to decrease to a greater value
	}

	heapNode temp = heap[place];

	while (place > 0 && heap[getParent(place)].weight > newKey) {

		// Fix Upwards:
		
		heap[place] = heap[getParent(place)];
		place = getParent(place);
	}

	heap[place] = temp;
	heap[place].weight = newKey;
}

/*********************************************************************/

bool MinHeap::leftChildExists(int index) {

	return (getLeftChild(index) < heap.size());
}

bool MinHeap::rightChildExists(int index) {

	return (getRightChild(index) < heap.size());
}

/*********************************************************************/
// Getters:
/*********************************************************************/

int MinHeap::getParent(int index) {

	return (index - 1) / 2;
}

int MinHeap::getLeftChild(int index) {

	return index * 2 + 1;
}

int MinHeap::getRightChild(int index) {

	return index * 2 + 2;
}

/*********************************************************************/
/*
 * ASSUMPION: The heap is not Empty
 */
heapNode MinHeap::getMin() const {

	return heap[0];
}

/*********************************************************************/
