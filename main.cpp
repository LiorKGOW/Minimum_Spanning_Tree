#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Graph.h"
#include "Union.h"
#include "MinHeap.h"
#include "Algorithms.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

void testing();

// argv = [ { name_of_program } , { Input File } , { Output File } ]

void main(int argc, char* argv[]) {

	Graph* graph = nullptr;
	int num_of_vertices = 0;
	int num_of_edges = 0;

	ifstream input(argv[1]);
	ofstream outFile(argv[2]);

	string line;

	bool errorFound = false;

	// TODO: line could be empty => error? 
	// TODO: invalid input? => what error to print? 
	// TODO: if we have an invalid input, do we print invalid input to the output file? to the screen?
	// TODO: fix un used structs

	// getline(EOF) => return value is "" for line. 
	// getline("") => default casting to bool: false.

	if (!getline(input, line))  
	{
		cout << "empty file. invalid input" << endl;

		input.close();
		outFile.close();

		exit(1);
	}

	//TODO: check if number and not char/double/anything

	num_of_vertices = std::stoi(line);

	if (num_of_vertices <= 0) {

		cout << "number of vertices in a graph can't be a non-positive number. invalid input" << endl;

		input.close();
		outFile.close();

		exit(1);
	}

	graph = new Graph(num_of_vertices);

	if (!getline(input, line))//no edge number
	{
		cout << "empty line. invalid input" << endl;
		delete graph;

		input.close();
		outFile.close();

		exit(1);
	}

	//TODO: check if number and not char/double/anything

	num_of_edges = std::stoi(line);

	if (num_of_edges < 0) {//negative number of edges

		cout << "number of edges in a graph can't be a negative number. invalid input" << endl;
		delete graph;

		input.close();
		outFile.close();

		exit(1);
	}

	for (int i = 0; i < num_of_edges; i++) {

		if (!getline(input, line))  //file ended before real number of edges
		{
			cout << "empty line. invalid input" << endl;
			delete graph;

			input.close();
			outFile.close();

			exit(1);
		}

		int ver1, ver2, weight;

		// expected format of a line: "{int} {int} {int}"

		int check = sscanf(line.c_str(), "%d %d %d", &ver1, &ver2, &weight);

		if (check != 3) {

			// TODO: if values are not int, or we have more or less then 3 ints => use check?

			cout << "wrong input format. invalid input" << endl;
			delete graph;

			input.close();
			outFile.close();

			exit(1);
		}

		// TODO: check if ver1 & ver2 are number between 1-n?
		if (!(ver1 >= 1 && ver1 <= num_of_vertices && ver2 >= 1 && ver2 <= num_of_vertices && ver1 != ver2)) {

			cout << "invalid edge. invalid input" << endl;
			delete graph;

			input.close();
			outFile.close();

			exit(1);
		}

		graph->AddEdge(ver1, ver2, weight);
	}

	/************************************************/
	// Algorithm Calls:

	// graph->printGraph();  // check the given graph from the input

	int totalWeight_kruskal, totalWeight_prim;

	Graph* kruskal_res = Kruskal(graph, totalWeight_kruskal);

	if (kruskal_res == nullptr) {

		// string Errormsg;

		outFile << "ERROR! The graph is not connected" << endl;

		delete graph;

		input.close();
		outFile.close();

		exit(1);
	}

	kruskal_res->printGraph();
	cout << "\n\nKruskal " << totalWeight_kruskal << "\n\n" << endl;
	outFile << "Kruskal " << totalWeight_kruskal << endl;

	// If we arrived to the above line, the graph was connected (we checked at Kruskal) so no need to add an additional if(graph == NULL)

	Graph* prim_res = Prim(graph, totalWeight_prim);

	prim_res->printGraph();
	cout << "\n\nPrim " << totalWeight_prim << "\n\n" << endl;
	outFile << "Prim " << totalWeight_prim << endl;

	/************************************************/
	// input of an edge to remove from graph:

	if (!getline(input, line))//edge to remove from graph doesnt exist
	{
		cout << "empty line. invalid input" << endl;

		delete graph;
		delete kruskal_res;
		delete prim_res;

		input.close();
		outFile.close();

		exit(1);
	}

	int ver1, ver2;

	// expected format of a line: "{int} {int}"

	int check = sscanf(line.c_str(), "%d %d", &ver1, &ver2);

	if (check != 2) {

		// TODO: if values are not int, or we have more or less then 3 ints => use check?

		cout << "wrong input format. invalid input" << endl;

		delete graph;
		delete kruskal_res;
		delete prim_res;

		input.close();
		outFile.close();

		exit(1);
	}

	// TODO: check if ver1 & ver2 are number between 1-n?
	if (!(ver1 >= 1 && ver1 <= num_of_vertices && ver2 >= 1 && ver2 <= num_of_vertices && ver1 != ver2)) {

		cout << "invalid edge. invalid input" << endl;

		delete graph;
		delete kruskal_res;
		delete prim_res;

		input.close();
		outFile.close();

		exit(1);
	}

	// TODO: if edge inserted wasn't in the graph? 
	if (!(graph->IsAdjacent(ver1, ver2))) {

		cout << "Edge (" << ver1 << ", " << ver2 << ") wasn't in graph. invalid input" << endl;

		delete graph;
		delete kruskal_res;
		delete prim_res;

		input.close();
		outFile.close();

		exit(1);
	}

	if (!(kruskal_res->IsAdjacent(ver1, ver2)))
	{
		cout << "Removed edge (" << ver1 << ", " << ver2 << ") wasn't in Kruskal's MST" << endl;
	}

	else
	{ 
		// Removed edge (ver1, ver2) was in Kruskal's MST:

		graph->RemoveEdge(ver1, ver2);

		if (!(graph->isConnectedGraph()))
		{
			cout << "No MST. Graph is not connected. Removed edge (" << ver1 << ", " << ver2 << ") was a bridge" << endl;
			// TODO: need to write this comment to file?
		}

		else
		{
			// Removed edge (ver1, ver2) wasn't a bridge:

			delete kruskal_res;
			
			kruskal_res = Kruskal(graph, totalWeight_kruskal);

			// kruskal_res is not nullptr, because we checked this case. no need to verify it.

			kruskal_res->printGraph();
			cout << "\n\n" << "Kruskal after removing " << totalWeight_kruskal << endl;
			outFile << "Kruskal after removing " << totalWeight_kruskal << endl;
		}
	}

	if (getline(input, line))
	{
		cout << "not an empty line, though the input should have ended. invalid input" << endl;

		delete graph;
		delete kruskal_res;
		delete prim_res;

		input.close();
		outFile.close();

		exit(1);
	}

	input.close();
	outFile.close();
}

/*********************************************************************/

void testing() {

  // Algorithms checks:

  // Prim

	/*Graph* g = new Graph(7);*/

	// g1:

	/*g->AddEdge(1, 4, 1);
	g->AddEdge(4, 3, 0);
	g->AddEdge(2, 3, -2);
	g->AddEdge(1, 2, 3);

	g->AddEdge(2, 4, -1);
	g->AddEdge(4, 5, 6);
	g->AddEdge(7, 1, -3);
	g->AddEdge(2, 6, 4);*/

	// g2:

	/*g->AddEdge(1, 4, 1);
	g->AddEdge(4, 3, 0);
	g->AddEdge(2, 3, -2);

	g->AddEdge(4, 5, 6);
	g->AddEdge(7, 1, -3);
	g->AddEdge(2, 6, 4);*/

	// g3:

	//g->AddEdge(1, 5, 0);
	//g->AddEdge(4, 5, 1);
	//g->AddEdge(3, 5, -1);
	//g->AddEdge(2, 5, 2);
	//g->AddEdge(6, 5, 4);
	//g->AddEdge(7, 5, 3);
	//g->AddEdge(4, 3, -2);
	//g->AddEdge(4, 6, -3);
	//g->AddEdge(7, 1, 5);
	//g->AddEdge(2, 3, 1);


	//g->printGraph();
	//cout << "................................................\n\n\n";

	//int weight = 0;
	//Graph* result = Prim(g, weight);
	//cout << weight << "\n\n" << endl;

	//result->printGraph();

	// check visit in Prim


 /*********************************************************************/

	// Kruskal:

	// 3

	/*Graph* g = new Graph(6);

	g->AddEdge(6, 2, 2);
	g->AddEdge(1, 3, 3);
	g->AddEdge(2, 4, 4);
	g->AddEdge(1, 5, 5);
	g->AddEdge(6, 1, 2);
	g->AddEdge(5, 3, 3);
	g->AddEdge(2, 5, 4);
	g->AddEdge(3, 2, 5);

	g->printGraph();

	cout << "\n\n";

	int weight;

	Graph* result = Kruskal(g, weight);

	result->printGraph();*/

	// 3 Unconnected graph

	/*g->AddEdge(1, 2, 2);
	g->AddEdge(1, 3, 3);
	g->AddEdge(1, 4, 4);
	g->AddEdge(1, 5, 5);

	g->printGraph();

	cout << "\n\n";

	int weight;

	Graph* result = Kruskal(g, weight);*/

	// result->printGraph();

	// 2

	/*Graph* g = new Graph(5);

	g->AddEdge(1, 2, 2);
	g->AddEdge(1, 3, 3);
	g->AddEdge(1, 4, 4);
	g->AddEdge(1, 5, 5);

	g->AddEdge(2, 3, -1);
	g->AddEdge(3, 4, 0);
	g->AddEdge(4, 5, 1);

	g->printGraph();

	cout << "\n\n";

	int weight;

	Graph* result = Kruskal(g, weight);

	result->printGraph();

	cout << "\n\n" << "weight of Graph: " << weight << endl;*/

	/*
	Graph* g = new Graph(4);

	g->AddEdge(1, 4, 1);
	g->AddEdge(4, 3, 0);
	g->AddEdge(2, 3, -2);
	g->AddEdge(1, 2, 3);

	g->AddEdge(2, 3, -1);
	g->AddEdge(3, 4, 0);
	g->AddEdge(4, 5, 1);


	g->printGraph();

	cout << "\n\n";

	int weight;

	Graph* result = Kruskal(g, weight);

	result->printGraph();

	cout << "\n\n" << "weight of Graph: " << weight << endl;*/


	/*********************************************************************/

	// Quick Sort:

	/* vector<edge> vecEdge;

	vecEdge.push_back({ 1,2,2 });
	vecEdge.push_back({ 1,3,3 });
	vecEdge.push_back({ 1,4,4 });
	vecEdge.push_back({ 1,5,5 });
	vecEdge.push_back({ 2,3,-1 });
	vecEdge.push_back({ 3,4,0 });
	vecEdge.push_back({ 4,5,1 });

	vecEdge.push_back({ 2,1,2 });
	vecEdge.push_back({ 3,1,3 });
	vecEdge.push_back({ 4,1,4 });
	vecEdge.push_back({ 5,1,5 });
	vecEdge.push_back({ 3,2,-1 });
	vecEdge.push_back({ 4,3,0 });
	vecEdge.push_back({ 5,4,1 });

	for (int i = 0; i < vecEdge.size(); i++) {

		cout << "( " << vecEdge[i].ver1 << ", " << vecEdge[i].ver2 << "): " << vecEdge[i].weight << endl;
	}

	cout << "-----------------------------------------";

	QuickSort(vecEdge, 0, vecEdge.size() - 1);

	cout << "Sorted: " << endl;

	for (int i = 0; i < vecEdge.size(); i++) {

		cout << "(" << vecEdge[i].ver1 << ", " << vecEdge[i].ver2 << "): " << vecEdge[i].weight << endl;
	}*/


	/*********************************************************************/
	/*********************************************************************/

// Data Structures:

// MinHeap:

	/*Graph* g = new Graph(7);

	g->AddEdge(1, 4, 1);
	g->AddEdge(4, 3, 0);
	g->AddEdge(2, 3, -2);
	g->AddEdge(1, 2, 3);

	g->AddEdge(2, 4, -1);
	g->AddEdge(4, 5, 6);
	g->AddEdge(7, 1, -3);
	g->AddEdge(2, 6, 4);


	g->printGraph();

	cout << "................................................\n\n\n";*/

	//vector <weightedEdge>edges = g->getWeightedEdgesVector();

	//MinHeap Chester = MinHeap(edges);

	//Chester.deceaseKey(3, 2);

	//heapNode drake = Chester.deleteMin();

	//cout << 1 << "  " << drake.data.ver1 << drake.data.ver2 << drake.weight << endl;

	//Chester.deceaseKey(2, -3);

	//drake = Chester.deleteMin();

	//cout << 2 << "  " << drake.data.ver1 << drake.data.ver2 << drake.weight << endl;

	//drake = Chester.deleteMin();

	//cout << 3 << "  " << drake.data.ver1 << drake.data.ver2 << drake.weight << endl;

	//cout << "done";

	//// weightedEdge = {int ver1, int ver2, int weight}


	/*********************************************************************/

	// Union Checks:

	//Union mshadows(6);

	//mshadows.UnionVertices(1, 6);
	//mshadows.UnionVertices(2, 3);
	//mshadows.UnionVertices(2, 4);

	/*mshadows.UnionVertices(2, 3);
	mshadows.UnionVertices(4, 5);
	mshadows.UnionVertices(2, 4);
	mshadows.UnionVertices(1, 2);*/

	/*mshadows.UnionVertices(2, 3);
	mshadows.UnionVertices(4, 5);
	mshadows.UnionVertices(2, 4);
	mshadows.UnionVertices(1, 6);
	mshadows.UnionVertices(1, 2);*/

	//mshadows.printUnion();

	/*********************************************************************/

	// Graph Check:

	//Graph g = Graph(5);
	//
	//g.AddEdge(1, 2, 2);
	//g.AddEdge(1, 3, 3);
	//g.AddEdge(1, 4, 4);
	//g.AddEdge(1, 5, 5);

	//cout << g.IsAdjacent(1, 2) << endl;
	//cout << g.IsAdjacent(2, 1) << endl;

	//g.AddEdge(2, 5, 5);
	//g.AddEdge(5, 4, 4);

	//g.printGraph();
	//cout << "\n\n\n";
	//List* adjlist1 = g.GetAdjList(1);
	//adjlist1->printList(1);
	//delete adjlist1;

	//cout << "\n\n\n";

	//g.RemoveEdge(5,4);

	//g.printGraph();
	//cout << "\n\n\n";
	//adjlist1 = g.GetAdjList(1);
	//adjlist1->printList(1);
	//delete adjlist1;

	//cout << "\n\n\n";

	//g.RemoveEdge(1,4);

	//g.printGraph();
	//cout << "\n\n\n";
	//adjlist1 = g.GetAdjList(1);
	//adjlist1->printList(1);
	//delete adjlist1;

	//cout << "\n\n\n";

	//g.RemoveEdge(1,2);

	//g.printGraph();
	//cout << "\n\n\n";
	//adjlist1 = g.GetAdjList(1);
	//adjlist1->printList(1);
	//delete adjlist1;

	//cout << "\n\n\n";

	//g.AddEdge(2, 1, 1);  // to see that adding an exsisting edge to the graph

	//cout << g.IsAdjacent(1, 2) << endl;
	//cout << g.IsAdjacent(2, 1) << endl;

	//cout << "\n\n\n";

	//List* adjlist1 = g.GetAdjList(1);
	//adjlist1->printList(1);

	//cout << "\n\n\n";

	//List* adjlist2 = g.GetAdjList(2);
	//adjlist2->printList(2);

	//cout << "\n\n\n";

	//g.AddEdge(3, 2, 2);

	//g.IsAdjacent(2, 3);

	//g.AddEdge(4, 3, 2);
	//g.AddEdge(4, 5, 2);
	//g.AddEdge(5, 3, 2);
	//g.AddEdge(3, 3, 2);  // Error

	/*********************************************************************/

	// List checks:

	//List lst;
	//lst.insertToHead(1, 2);
	//lst.insertToHead(2, 3);
	//lst.insertToHead(3, 4);

	////lst.removeFromList(2);

	//lst.insertToHead(4, 5);

	////lst.removeFromList(1);

	//lst.insertToHead(5, 6);

	////lst.removeFromList(5);

	//// 5 -> 4 -> 3 -> 2 -> 1

	//lst.printList(1);
	//cout << "\n\n\n";
	//lst.printListBack();

	//cout << "\n\n\n";

	//cout << "1 is in lst: " << lst.isInList(1) << endl;
	//cout << "2 is in lst: " << lst.isInList(2) << endl;
	//cout << "3 is in lst: " << lst.isInList(3) << endl;
	//cout << "4 is in lst: " << lst.isInList(4) << endl;
	//cout << "5 is in lst: " << lst.isInList(5) << endl;

	//List lst2;
	//lst2.insertToTail(1, 2);
	//lst2.insertToTail(2, 3);
	//lst2.insertToTail(3, 4);
	//lst2.insertToTail(4, 5);
	//lst2.insertToTail(5, 6);

	//lst2.printList();
	//cout << "\n\n\n";
	//lst2.printListBack();

}
