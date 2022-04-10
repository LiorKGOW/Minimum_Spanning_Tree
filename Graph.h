#pragma once
#include <iostream>
#include "List.h"
#include <vector>

using namespace std;

class Graph
{
private:

	vector<List*> adjList;
	
public:
	Graph(int n);

	void MakeEmptyGraph(int n);
	bool IsAdjacent(int ver1, int ver2);
	List* GetAdjList(int vertex);
	void AddEdge(int ver1, int ver2, int weight);
	void RemoveEdge(int ver1, int ver2);
};

// The vertexes are 0 - n-1, we will treat them as 1 - n