#include "Graph.h"

/*********************************************************************/
// Constructor
Graph::Graph(int n)
{
	this->adjList.reserve(n);
	this->Num_of_Vertices = n;

	MakeEmptyGraph(n);

	this->colors.reserve(n);

	for (int i = 0; i < Num_of_Vertices; i++)
	{
		colors.push_back(WHITE);
	}

	this->colorsIsWhite = true;
}

/*********************************************************************/
// Destructor
Graph::~Graph()
{
	for (int i = 0; i < this->Num_of_Vertices; i++)
	{

		delete adjList[i];
	}
}

/*********************************************************************/
void Graph::MakeEmptyGraph(int n)
{
	for (int i = 0; i < n; i++)
	{
		this->adjList.push_back(new List());
	}
}

/*********************************************************************/
/*
 * Checks if the edge (ver1, ver2) is in the graph.
 */
bool Graph::IsAdjacent(int ver1, int ver2)
{
	return adjList[ver1 - 1]->isInList(ver2 - 1);
}

/*********************************************************************/
/*
 * GetAdjList returns a *duplication* of the adjList of vertex.
 */
List *Graph::GetAdjList(int vertex)
{
	List *result = adjList[vertex - 1]->duplicateList();

	return result;
}

/*********************************************************************/
/*
 * AddEdge Adds the edge (ver1, ver2) to the graph.
 */
void Graph::AddEdge(int ver1, int ver2, int weight)
{
	if (!IsAdjacent(ver1, ver2))
	{

		adjList[ver1 - 1]->insertToTail(ver2 - 1, weight);

		AddInvertedEdge(ver2, ver1, weight);
	}

	// else, the edge is already in the graph -> do nothing.
}

/*********************************************************************/
/*
 * AddEdge Adds the edge (ver2, ver1) to the graph.
 */
void Graph::AddInvertedEdge(int ver2, int ver1, int weight)
{
	if (!IsAdjacent(ver2, ver1))
	{

		adjList[ver2 - 1]->insertToTail(ver1 - 1, weight);
	}

	// else, the inverted edge is already in the graph -> do nothing.
}

/*********************************************************************/
/*
 * Removes the Edges: (ver1, ver2) & (ver2, ver1) from the graph.
 *
 * ASSUMPTION: if the edge (ver1, ver2) is in the graph, the inverted edge (ver2, ver1) is also in the graph.
 */
void Graph::RemoveEdge(int ver1, int ver2)
{
	if (!IsAdjacent(ver1, ver2))
	{
		cout << "The Edge (" << ver1 << "," << ver2 << ") is not in the graph" << endl;
	}
	else
	{
		adjList[ver1 - 1]->removeFromList(ver2 - 1);
		adjList[ver2 - 1]->removeFromList(ver1 - 1);
	}
}

///*********************************************************************/
// void Graph::DFS()
//{
//	if (!this->colorsIsWhite)
//		makeColorsWhite();
//
//	for (int i = 0; i < Num_of_Vertices; i++)
//	{
//		if (colors[i] == WHITE)
//			visit(i);
//	}
//
//	this->colorsIsWhite = false;
// }

/*********************************************************************/
void Graph::makeColorsWhite()
{
	for (int i = 0; i < Num_of_Vertices; i++)
	{
		colors[i] = WHITE;
	}

	this->colorsIsWhite = true;
}

/*********************************************************************/

void Graph::visit(int vertex)
{
	colors[vertex] = GRAY;

	Node *curr = adjList[vertex]->getHead();

	while (curr != nullptr)
	{
		if (colors[curr->getVertex()] == WHITE)
		{
			colors[curr->getVertex()] = GRAY;
			visit(curr->getVertex());
		}

		curr = curr->getNext();
	}

	colors[vertex] = BLACK;
}

/*********************************************************************/
bool Graph::isConnectedGraph()
{
	if (!this->colorsIsWhite)
		makeColorsWhite();

	visit(0);

	this->colorsIsWhite = false;

	for (int i = 0; i < Num_of_Vertices; i++)
	{
		if (colors[i] != BLACK)
			return false;
	}

	return true;
}

/*********************************************************************/
/*
 * in case a vertex doesn't have edges attached to it, printGraph prints an empty line.
 */
void Graph::printGraph()
{
	for (int i = 0; i < Num_of_Vertices; i++)
	{
		adjList[i]->printList(i + 1);
		cout << endl;
	}
}

/*********************************************************************/
int Graph::get_Num_of_Vertices()
{
	return this->Num_of_Vertices;
}

/*********************************************************************/
