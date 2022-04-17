#pragma once
#include <vector>

using namespace std;

typedef struct treeNode{

	int vertex;
	int parent;
	int size;

}treeNode;

class Union
{
	// With Path Compression & Union By Size

private:
	
	vector<treeNode> arr;
	int size;

public:

	Union(int n);

	void MakeSet(int vertex);
	int Find(int vertex);
	void UnionVertices(int ver1, int ver2);

	// Getter

	// Setter

	void printUnion(); //TODO: implement printUnion
};

