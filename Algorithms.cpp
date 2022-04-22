#include "Algorithms.h"

Graph *Kruskal(Graph *g, int &totalWeight)
{
	totalWeight = 0;

	if (!g->isConnectedGraph())
	{
		return nullptr;
		// TODO: Print Error? Unconnected Graph
	}

	Graph *result = new Graph(g->get_Num_of_Vertices()); // of edges

	vector<edge> vecEdge; // Items: 0 - n-1

	for (int i = 0; i < g->get_Num_of_Vertices(); i++)
	{
		List *currList = g->GetAdjList(i + 1);

		Node *curr = currList->getHead();

		while (curr != nullptr)
		{
			edge e = {i, curr->getVertex(), curr->getWeight()};

			if (!isInVec(vecEdge, e))
			{
				vecEdge.push_back(e);
			}

			curr = curr->getNext();
		}

		delete currList;
	}

	QuickSort(vecEdge, 0, vecEdge.size() - 1); // Sort Edges By weight

	Union Vertices(g->get_Num_of_Vertices());
	// Graph* result, Add(u,v) to the Graph -> AddEdge(u,v)

	int numOfEdges = 0;
	// if result has n-1 edges, We can stop the loop (We have found the tree).

	for (int i = 0; i < vecEdge.size() && numOfEdges < g->get_Num_of_Vertices() - 1; i++)
	{
		// vecEdge[i] // (u,v)

		int vec1Rep = Vertices.Find(vecEdge[i].ver1);
		int vec2Rep = Vertices.Find(vecEdge[i].ver2);

		if (vec1Rep != vec2Rep)
		{

			result->AddEdge(vecEdge[i].ver1 + 1, vecEdge[i].ver2 + 1, vecEdge[i].weight);
			totalWeight += vecEdge[i].weight;

			Vertices.UnionVertices(vec1Rep + 1, vec2Rep + 1);
			numOfEdges++;
		}
	}

	return result;
}

/*********************************************************************/
/*
 * isInVec checks if the inverted edge of e {ver2, ver1, weight} already exist in the vector
 */
bool isInVec(vector<edge> &vecEdge, edge e)
{

	bool check = false;

	for (int i = 0; i < vecEdge.size() && !check; i++)
	{

		if (vecEdge[i].ver1 == e.ver2 && vecEdge[i].ver2 == e.ver1)
			check = true;
	}

	return check;
}

/*********************************************************************/
// edges[i] = {vec1, vec2, weight}
void QuickSort(vector<edge> &edges, int begin, int end)
{
	// Sort Edges By weight

	int pivot;

	if (begin < end)
	{

		pivot = Partition(edges, begin, end);

		QuickSort(edges, begin, pivot - 1);
		QuickSort(edges, pivot + 1, end);
	}
}

/*********************************************************************/
int Partition(vector<edge> &edges, int begin, int end)
{
	// By weight

	edge pivotEdge = edges[end];

	int indP = begin; // Index of smaller element and indicates the right position of pivot found so far

	for (int j = begin; j <= end - 1; j++)
	{
		// If current element is smaller than the pivot
		if (edges[j].weight < pivotEdge.weight)
		{
			swap(edges[indP], edges[j]);
			indP++; // increment index of position of Pivot in the vector
		}
	}

	swap(edges[indP], edges[end]);
	return indP;
}

/*********************************************************************/
void swap(edge &edge1, edge &edge2)
{
	edge t = edge1;
	edge1 = edge2;
	edge2 = t;
}

/*********************************************************************/
