#include "Union.h"

Union::Union(int n) {

	for (int i = 0; i < n; i++) {
		
		MakeSet(i);
	}
}

void Union::MakeSet(int ver) {

	arr.push_back(treeNode{ ver, ver, 1 });
}

int Union::Find(int ver) {

	if (arr[ver].parent == ver) {

		return ver;
	}

	int parent = Find(arr[ver].parent);
	arr[ver].parent = parent;
	return parent;

	/*int curr = ver;

	while (arr[curr].parent != curr) {

		int temp = arr[curr].parent;
		arr[curr].parent = ver;
		curr = temp;
	}

	return curr;*/
}
void Union:: UnionVertices(int ver1, int ver2);