#pragma once
#include <iostream>
#include "List.h"
#include "Weighted_Edge.h"
#include <vector>

using namespace std;

// Consts for the DFS functions:

#define WHITE 0
#define GRAY 1
#define BLACK 2

class Graph
{
	// The vertexes are 0 - n-1, we will treat them as 1 - n
	// in case a vertex doesn't have edges attached to it, printGraph prints an empty line.

private:
	vector<List *> adjList;
	int Num_of_Vertices;

	vector<int> colors; // in use in DFS functions
	bool colorsIsWhite;

	vector<weightedEdge> edges;   // The vector contains weighted edges with vertices logic of (1 - n)
	// logSize == edges.size() == Num_of_Edges

public:
	Graph(int n); // Constructor
	~Graph();	  // Destructor

	void MakeEmptyGraph(int n);
	bool IsAdjacent(int ver1, int ver2);
	List *GetAdjList(int vertex);
	void AddEdge(int ver1, int ver2, int weight);
	void AddInvertedEdge(int ver2, int ver1, int weight);
	void RemoveEdge(int ver1, int ver2);

	// void DFS();
	void makeColorsWhite();
	void visit(int vertex);
	bool isConnectedGraph();

	// 
	vector<weightedEdge> getWeightedEdgesVector();

	void printGraph(); // in case a vertex doesn't have edges attached to it, printGraph prints an empty line.

	// Getters:

	int get_Num_of_Vertices();
	int get_Num_of_Edges();

	// Setters:
};