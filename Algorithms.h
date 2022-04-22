#pragma once
#include "Graph.h"
#include "Union.h"
#include <vector>

typedef struct edge
{
	int ver1;
	int ver2;
	int weight;
} edge;

Graph *Kruskal(Graph *g, int &totalWeight);

void QuickSort(vector<edge> &edges, int begin, int end); // By weight
int Partition(vector<edge> &edges, int begin, int end);
void swap(edge &edge1, edge &edge2);
bool isInVec(vector<edge> &vecEdge, edge e);
