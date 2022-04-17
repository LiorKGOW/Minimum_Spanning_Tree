#include "Union.h"

/*********************************************************************/

Union::Union(int n)
{

	this->size = n;

	for (int i = 0; i < n; i++)
	{

		MakeSet(i);
	}
}

/*********************************************************************/

void Union::MakeSet(int vertex)
{

	arr.push_back(treeNode{vertex, vertex, 1});
}

/*********************************************************************/
/*
 * Find is a recursive function.
 * The function returns the representative of ver.
 * With Path Compression
 */
int Union::Find(int vertex)
{

	// Stop Condition
	if (arr[vertex].parent == vertex)
	{

		return vertex;
	}

	// recursive call
	int representative = Find(arr[vertex].parent);

	arr[vertex].parent = representative; // path compression

	return representative;
}

/*********************************************************************/
/*
 * With Union By Size
 * ASSUMPTION: ver1 and ver2 are representatives of their Set.
 */
void Union::UnionVertices(int ver1, int ver2) // TODO: implement
{
	if (ver1 == ver2)
		return;

	if (arr[ver1].size >= arr[ver2].size)
	{

		arr[ver2].parent = ver1;
	}
	else
	{ // arr[Find(ver1)].size < arr[Find(ver2)].size

		arr[ver1].parent = ver2;
	}
}

/*********************************************************************/
/*
 * {/?rep: ?/1, 2, 3}, { rep: 4,5 }, { rep: 6 }
 */
void Union::printUnion()
{ // TODO: implement

	// for(int i=0;i<)
}