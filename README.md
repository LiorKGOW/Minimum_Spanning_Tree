# Minimum_Spanning_Tree

In this project, we will implement the Prim's algorithm, and Kruskal's algorithm, to find the minimum spanning tree of a given graph.
In addition, We'll remove an edge from the given graph, and check if the removed edge was in kruskal's found MST.
If it was, We'll find a different MST that does not contain the removed edge (If it exists).

The input file would be given to the program as the first argument.
The output would be printed to both the screen and the second file that was given to the program as an argument.

_Input Format:_

Num_Of_Vertices
Num_Of_Edges
ver1 ver2 weight (X Num_Of_Edges times)
ver1 ver2

- I'll include a few input files in the code as examples.

_Data Structures Used:_

- Two Way Linked List
- Graph
- Union-Find (Disjoint Set)
- Priority Queue (Min Heap)
- Linked List

_Algorithms Used:_

- Prim's Algorithm
- Kruskal's Algorithm
- QuickSort (for Prim's Algorithm)
