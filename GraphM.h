// ------------------------------------------------ GraphM.h ------------------
// Shayan Raouf CSS343 Section Number
// Creation Date: 2/04/2016
// Date of Last Modification: 2/11/2016
// ----------------------------------------------------------------------------
// Purpose - To create adjaceny matrix and execute Dikstra's Algorithm 
// ----------------------------------------------------------------------------
//  As stated in the direction by professor Min Chen :
//  This project is to implement Dijkstra's shortest path algorithm. Your code should
//  be able to read a data file consisting of many lines (an example file called 
//	data31.txt will be given, explained below) and will be able to find the lowest
//	cost paths (findShortestPath function) and display the cost and path from every 
//	node to every other node (displayAll function).  Another display routine 
//	(display function) will output one path in detail. 
//
//    In the input data(e.g., data31.txt), the first line tells the number of nodes, 
//	say n, followed by a text description of each of the 1 through n nodes, 
//	one description per line(50 chars max length).After that, each line consists 
//	of 3 integers representing an edge.If there is an edge from node 1 to node 2 
//	with a label of 10, the data is : 1 2 10.  If the first integer is zero, it 
//	means the end of the data for that one graph.There may be several graphs, each 
//	having at most 100 nodes.For example, Figure 1 (a)shows part of data from 
//	data31.txt(the data file you will be given) where it contains 5 nodes.For 
//	clarity, (b)shows a graph drawn based on data in(a).However, Figure 1 (b)is 
//	just for your reference.It’s not part of your input data or the output you 
//	need to produce.For this lab(including part 2, ) you may assume the input 
//	data file has correctly formatted, valid data.
// - Functions:
//		- buildGraph(istream& istream);
//		- insertEdge(int startIndex, int endIndex, int cost);
//		- removeEdge(int startIndex, int endIndex);
//		- findShortestPath();
//		- displayAll() const;
//		- display(int fromPath, int toPath) const;
#ifndef GRAPHM_H
#define GRAPHM_H

#include "NodeData.h"
#include <iostream>
#include <limits>
#include <iomanip>
const int MAXNODES = 101;
const int INFINITE = numeric_limits<int>::max();
using namespace std;
class GraphM
{
public:
	GraphM();
	~GraphM();
	void buildGraph(istream& istream);
	void insertEdge(int startIndex, int endIndex, int cost);
	void removeEdge(int startIndex, int endIndex);
	void findShortestPath();
	void displayAll() const;
	void display(int fromPath, int toPath) const;

private:
	struct TableType {
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};

	NodeData data[MAXNODES];              // data for graph nodes 
	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

	void initializeTableType();
	void initializeAdjacencyMatrixCost();
	void initializeNodeData(istream& istream);
	void setAllNotVisted();
	void getPath(int fromPath, int toPath) const;
	void getPathData(int fromPath, int toPath) const;

	int NotVistedMin(int row);
};

#endif
