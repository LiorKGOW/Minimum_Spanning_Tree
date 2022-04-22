#pragma once
#include <vector>
#include "List.h"
#include <iostream>

#define UNUSED -1 // usage in printUnion

using namespace std;

typedef struct treeNode
{

	int vertex;
	int parent;
	int size;

} treeNode;

class Union
{
	// With Path Compression & Union By Size.
	// Implementation using tree structure and vector.

private:
	vector<treeNode> arr;
	int size;

public:
	Union(int n); // Ctor

	void MakeSet(int vertex);
	int Find(int vertex);
	void UnionVertices(int ver1, int ver2);

	// Getters:

	int getSize(int vertex);

	// Setters:

	void printUnion();
};
