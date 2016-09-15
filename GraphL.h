// ------------------------------------------------ GraphL.h ------------------
// Shayan Raouf CSS343 Section Number
// Creation Date: 2/04/2016
// Date of Last Modification: 2/11/2016
// ----------------------------------------------------------------------------
// Purpose - To create adjaceny list and execute DFS
// ----------------------------------------------------------------------------
// As stated in the direction by professor Min Chen:
// This project is to display the graph information and implement 
// depth - first(search always starts at node #1).
//
// Similar to Part 1, in the input data(e.g., data32.txt), 
// the first line tells the number of nodes, say n, followed by a text description 
// of each of the 1 through n nodes, one description per line(50 chars max length).
// After that, each line consists of 2 integers(instead of 3 integers in Part 1) 
// representing an edge.If there is an edge from node 1 to node 2, the data is 
// 1 2.  A zero for the first integer signifies the end of the data for that 
// one graph.In the file, all the edges for the 1st node will be listed first,
// then all the edges for the 2nd node, etc.Take them as they come, no sorting.
// There may be several graphs, each having at most 100 nodes.For example, Figure 
// 1 (a)shows part of data from data32.txt(the data file you will be given)
// where it contains 5 nodes.For clarity, (b)shows a graph drawn based on data 
// in(a).However, Figure 1 (b)is just for your reference.It’s not part of your 
// input data or the output you need to produce.Figure 1 (c)shows the sample output 
// where the last line is produced by calling depthFirstSearch function and the rest
// of them are produced by displayGraph.As you may see, edges in the input are always 
// shown in reverse order in the output
// - Function:
//		buildGraph(istream& istream);
//		displayGraph() const;
//		depthFirstSearch();
//		depthFirstSearch(int vertex);
//		insertEdge(int vertex1, int vertex2);
// ----------------------------------------------------------------------------
#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
#include "NodeData.h"
#include <sstream>
using namespace std;

struct EdgeNode;      // forward reference for the compiler
struct GraphNode {    // structs used for simplicity, use classes if desired
	EdgeNode* edgeHead; // head of the list of edges
	NodeData* data;     // data information about each node
	bool visited;
};

struct EdgeNode {
	int adjGraphNode;  // subscript of the adjacent graph node
	EdgeNode* nextEdge;
};

class GraphL
{
public:

	GraphL();
	~GraphL();
	void buildGraph(istream& istream);
	void displayGraph() const;
	void depthFirstSearch();
	void depthFirstSearch(int vertex);
	void insertEdge(int vertex1, int vertex2);

private:

	GraphNode* AdjList;
	int size;
	void initializeNodeData(istream& istream);
	void initializeAdjacencyList();
	void deleteLinkedList(EdgeNode*& N);
	void clearAdjList();
};

#endif