#pragma once
#include <iostream>
#include "List.h"
#include <vector>

using namespace std;

class Graph
{
	// The vertexes are 0 - n-1, we will treat them as 1 - n
	// in case a vertex doesn't have edges attached to it, printGraph prints an empty line.

	// TODO: if Graph size is 0? -> throw exception? / deal with the kelet
	// TODO: if addEdge(3,3) -> Error?
	// TODO: adding an existing edge -> Error?
	// TODO: trying to remove unexisting edge from the graph -> Error?  (We print an error message and continuing as normal

private:

	vector<List*> adjList;
	int size;
	
public:
	Graph(int n);  // Constructor
	~Graph();      // Destructor

	void MakeEmptyGraph(int n);
	bool IsAdjacent(int ver1, int ver2);
	List* GetAdjList(int vertex);
	void AddEdge(int ver1, int ver2, int weight);
	void AddInvertedEdge(int ver2, int ver1, int weight);
	void RemoveEdge(int ver1, int ver2);

	void printGraph();
	// in case a vertex doesn't have edges attached to it, printGraph prints an empty line.
};