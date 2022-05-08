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

#define CheckWithMinus true
#define DoNotCheckWithMinus false

inline bool digitOrSpace(char c);
bool checkIfValidChar(string& line, bool checkWithMinus);
bool checkFileOpened(ifstream& input, ofstream& output, string& line);
bool checkEmptyLine(ifstream& input, string& line);

bool checkLegalLine_NumOfVertices(string& line, int& num_of_vertices);
bool checkLegalLine_NumOfEdges(string& line, int& num_of_edges);
bool checkLegalLine_WeightedEdge(string& line, int num_of_vertices, int& ver1, int& ver2, int& weight);
bool checkLegalLine_RemovedEdge(string& line, Graph* g, int& ver1, int& ver2);

void deleteEverything(ifstream& input, ofstream& output, Graph*& g1, Graph*& g2, Graph*& g3);

// argv = [ { name_of_program } , { Input File } , { Output File } ]

void main(int argc, char* argv[]) {

	Graph* graph = nullptr;
	int num_of_vertices = 0;
	int num_of_edges = 0;

	Graph* kruskal_res = nullptr;
	Graph* prim_res = nullptr;

	ifstream input(argv[1]);
	ofstream outFile(argv[2]);

	string line;

	if (!checkFileOpened(input, outFile, line)) {
		cout << line;
		if (!outFile.fail())
			outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);
		exit(1);
	}

	if (!checkEmptyLine(input, line)) {

		cout << line;
		outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);
		exit(1);
	}

	if (!checkLegalLine_NumOfVertices(line, num_of_vertices)) {

		// print to console and file:
		cout << line;
		outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);
	}

	graph = new Graph(num_of_vertices);

	if (!checkEmptyLine(input, line)) {  // No edge number

		cout << line;
		outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);
		exit(1);
	}

	if (!checkLegalLine_NumOfEdges(line, num_of_edges)) {

		// prints to console and file:
		cout << line;
		outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);
		exit(1);
	}

	// getting the edges: 

	for (int i = 0; i < num_of_edges; i++) {

		if (!checkEmptyLine(input, line)) {

			cout << line;
			outFile << line;
			deleteEverything(input, outFile, graph, kruskal_res, prim_res);
			exit(1);
		}

		int ver1, ver2, weight;

		if (!checkLegalLine_WeightedEdge(line, num_of_vertices, ver1, ver2, weight)) {

			cout << line;
			outFile << line;
			deleteEverything(input, outFile, graph, kruskal_res, prim_res);

			exit(1);
		}
		else
			graph->AddEdge(ver1, ver2, weight);
	}

	/*cout << "Graph: " << endl;
	graph->printGraph();
	cout << "\n\n";*/

	/************************************************
	* Algorithm Calls:
	************************************************/

	int totalWeight_kruskal, totalWeight_prim;

	kruskal_res = Kruskal(graph, totalWeight_kruskal, line);

	if (kruskal_res == nullptr) {

		cout << line;
		outFile << line;

		deleteEverything(input, outFile, graph, kruskal_res, prim_res);

		exit(1);
	}

	//kruskal_res->printGraph();
	cout << "Kruskal " << totalWeight_kruskal << endl;
	outFile << "Kruskal " << totalWeight_kruskal << endl;

	// If we arrived to the above line, the graph was connected (we checked at Kruskal) so no need to add an additional if(graph == NULL)

	prim_res = Prim(graph, totalWeight_prim);

	//prim_res->printGraph();
	cout << "Prim " << totalWeight_prim << endl;
	outFile << "Prim " << totalWeight_prim << endl;

	/************************************************
	* input of an edge to remove from graph:
	************************************************/

	if (!checkEmptyLine(input, line)) {

		cout << line;
		outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);
		exit(1);
	}

	int ver1, ver2;

	if (!checkLegalLine_RemovedEdge(line, graph, ver1, ver2)) {

		cout << line;
		outFile << line;
		deleteEverything(input, outFile, graph, kruskal_res, prim_res);

		exit(1);
	}

	/********************************************************
	* Removing the edge
	*********************************************************/

	if (!(kruskal_res->IsAdjacent(ver1, ver2)))
	{
		cout << "Removed edge (" << ver1 << ", " << ver2 << ") wasn't in Kruskal's MST" << endl;
		outFile << "Removed edge (" << ver1 << ", " << ver2 << ") wasn't in Kruskal's MST" << endl;
	}

	else
	{
		// Removed edge (ver1, ver2) was in Kruskal's MST:

		graph->RemoveEdge(ver1, ver2);

		if (!(graph->isConnectedGraph()))
		{
			cout << "No MST. Graph is not connected. Removed edge (" << ver1 << ", " << ver2 << ") was a bridge" << endl;
			outFile << "No MST. Graph is not connected. Removed edge (" << ver1 << ", " << ver2 << ") was a bridge" << endl;
		}

		else
		{
			// Removed edge (ver1, ver2) wasn't a bridge:

			delete kruskal_res;

			kruskal_res = Kruskal(graph, totalWeight_kruskal, line);

			// kruskal_res is not nullptr, because we checked this case. no need to verify it.

			cout << "Kruskal after removing " << totalWeight_kruskal << endl;
			outFile << "Kruskal after removing " << totalWeight_kruskal << endl;
		}
	}

	if (getline(input, line))
	{
		cout << "not an empty line, though the input should have ended. invalid input" << endl;
		outFile << "not an empty line, though the input should have ended. invalid input" << endl;

		deleteEverything(input, outFile, graph, kruskal_res, prim_res);

		exit(1);
	}

	deleteEverything(input, outFile, graph, kruskal_res, prim_res);
}

/*********************************************************************/
bool checkFileOpened(ifstream& input, ofstream& output, string& line) {

	if (input.fail() || output.fail())
	{
		line = "Error occured while trying to open the files";
		return false;
	}
	return true;
}

/*********************************************************************/
 /* This Function checks that the current line is not an empty line.
 * And sets line as the line that was inserted.
 */
bool checkEmptyLine(ifstream& input, string& line)
{
	if (!getline(input, line))
	{
		line = "empty line. invalid input \n";
		return false;
	}

	return true;
}

/*********************************************************************/
 /* This Function checks that the current line is legal according to the expected input,
 * And assigns the value to num_of_vertices.
 */
bool checkLegalLine_NumOfVertices(string& line, int& num_of_vertices) {

	num_of_vertices = 0;

	if (!checkIfValidChar(line, DoNotCheckWithMinus)) {

		return false;
	}

	num_of_vertices = std::stoi(line);
	if (num_of_vertices <= 0) {

		line = "number of vertices in a graph can't be a non-positive number. invalid input\n";
		return false;
	}

	return true;
}

/*********************************************************************/
/* This Function checks that the current line is legal according to the expected input,
 * And assigns the value to num_of_edges.
 */
bool checkLegalLine_NumOfEdges(string& line, int& num_of_edges) {

	num_of_edges = 0;

	if (!checkIfValidChar(line, DoNotCheckWithMinus)) {

		return false;
	}

	num_of_edges = std::stoi(line);
	if (num_of_edges < 0) {

		line = "number of edges in a graph can't be a negative number. invalid input\n";
		return false;
	}

	return true;
}

/*********************************************************************/
/* This Function checks that the current line is legal according to the expected input,
 * And assigns the value to ver1, ver2 & ver3.
 *
 * Expected format of a line: "{int} {int} {int}"
 * ASSUMPTION: there are no duplicate edges {v1,v2} & {v1,v2} or {v2,v1}
 */
bool checkLegalLine_WeightedEdge(string& line, int num_of_vertices, int& ver1, int& ver2, int& weight) {

	ver1 = ver2 = weight = 0;

	if (!checkIfValidChar(line, CheckWithMinus)) {

		return false;
	}

	int check = sscanf(line.c_str(), "%d %d %d", &ver1, &ver2, &weight);

	if (check != 3) {

		line = "wrong input format. invalid input \n";

		return false;
	}

	if (!(ver1 >= 1 && ver1 <= num_of_vertices && ver2 >= 1 && ver2 <= num_of_vertices && ver1 != ver2)) {

		line = "invalid edge. invalid input \n";

		return false;
	}

	return true;
}

/*********************************************************************/
/* This Function checks that the current line is legal according to the expected input,
 * And assigns the value to ver1 and ver2.
 *
 * Expected format of a line: "{int} {int}"
 */
bool checkLegalLine_RemovedEdge(string& line, Graph* g, int& ver1, int& ver2) {

	ver1 = ver2 = 0;

	if (!checkIfValidChar(line, DoNotCheckWithMinus)) {

		return false;
	}

	int dump;

	int check = sscanf(line.c_str(), "%d %d %d", &ver1, &ver2, &dump);

	if (check != 2) {

		line = "wrong input format. invalid input \n";

		return false;
	}

	if (!(ver1 >= 1 && ver1 <= g->get_Num_of_Vertices() && ver2 >= 1 && ver2 <= g->get_Num_of_Vertices() && ver1 != ver2)) {

		line = "invalid edge. invalid input \n";

		return false;
	}

	// if edge inserted wasn't in the graph:

	if (!(g->IsAdjacent(ver1, ver2))) {

		line = "Edge (";
		line += ver1;
		line += ", ";
		line += ver2;
		line += ") wasn't in graph. invalid input \n";

		return false;
	}

	return true;
}

/*********************************************************************
 *
 * This Function checks that the string contains only legal characters
 */
bool checkIfValidChar(string& line, bool checkWithMinus)
{
	for (int i = 0; i < line.size(); i++) {

		if (!(digitOrSpace(line[i]) || (checkWithMinus && line[i] == '-'))) {

			char temp = line[i];
			line = "invalid character inserted: '";
			line += temp;
			line += "'";
			line += " is an invalid input. \n";

			return false;
		}
	}

	return true;
}

/*********************************************************************/

inline bool digitOrSpace(char c) {

	return (c == ' ' || (c >= '0' && c <= '9'));
}

/*********************************************************************/

void deleteEverything(ifstream& input, ofstream& output, Graph*& g1, Graph*& g2, Graph*& g3)
{
	if (input.is_open())
		input.close();
	if (output.is_open())
		output.close();
	if (!g1)
		delete g1;
	if (!g2)
		delete g2;
	if (!g3)
		delete g3;
}

/*********************************************************************/
