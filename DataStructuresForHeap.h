#pragma once
#include "Weighted_Edge.h"

// { Data, Key }
// { edge, weight }

typedef struct graphEdge {

	int ver1;
	int ver2;

}graphEdge;

typedef struct heapNode {

	int data;  // vertex
	int weight;  // key

}heapNode;
