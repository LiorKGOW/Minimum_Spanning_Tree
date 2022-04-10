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
private:
	
	vector<treeNode> arr;

public:

	Union(int n);

	void MakeSet(int ver);
	int Find(int ver);
	void UnionVertices(int ver1, int ver2);

	// Getter

	// Setter
};

