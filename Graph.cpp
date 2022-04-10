#include "Graph.h"

Graph:: Graph(int n) {

	MakeEmptyGraph(n);
}

void Graph::MakeEmptyGraph(int n) {

	for (int i = 0; i < n; i++) {

		this->adjList.push_back(new List());
	}
}

bool Graph::IsAdjacent(int ver1, int ver2) {

	return adjList[ver1]->isInList(ver2);
}

List* Graph::GetAdjList(int vertex) {

	return adjList[vertex];
}

void Graph::AddEdge(int ver1, int ver2, int weight) {

	adjList[ver1] -> insertToTail(ver2, weight);
}

void Graph::RemoveEdge(int ver1, int ver2) {
	
	if (!(adjList[ver1]->isInList(ver2))) {

		cout << "The Edge<" << ver1 + 1 << "," << ver2 + 1 << "> is not in the graph" << endl;
	}
	else { 

		adjList[ver1]->removeFromList(ver2);
		adjList[ver2]->removeFromList(ver1);
	}
}