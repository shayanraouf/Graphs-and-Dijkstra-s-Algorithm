// ------------------------------------------------ GraphL.cpp ------------------
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

// ----------------------------------------------------------------------------
#include "GraphL.h"


// -------------------------------- GraphL() ---------------------------------
// Description: default constructor
// Precondition: NONE
// Features: sets AdjList to NULL
// ---------------------------------------------------------------------------
GraphL::GraphL()
{
	AdjList = NULL;
}

// -------------------------------- ~GraphL() ------------------------------
// Description: Destructor
// Precondition: clearAdjList() has been created
// Features: calls  clearAdjList()
// ---------------------------------------------------------------------------
GraphL::~GraphL()
{
	clearAdjList();
}

// -------------------------------- buildGraph ------------------------------
// Description: builds a graph from a text file. 
// Precondition: Pre-formated txt file
// Features:  given an istream arugment passed by reference buildGraph 
// function reads from a file in the following order:
// - int n: represents the number of Vertices (Nodes) of the graph
// - then reads the following string lines in corrilation to the each Vertex
// - reads each each line of three integers representing the edges and the 
// ---------------------------------------------------------------------------
void GraphL::buildGraph(istream& istream)
{
	// initializes number of nodes
	istream >> size;
	string lineBreak;

	// reads extra white space
	getline(istream, lineBreak);

	//if (size > 0) 
	AdjList = new GraphNode[size + 1];
	// initializing the tree integers we need
	initializeAdjacencyList();

	initializeNodeData(istream);

	int vertex1 = 0, vertex2 = 0;
	while (!istream.eof())
	{
	
		istream >> vertex1;
		istream >> vertex2;
		if (vertex1 == 0 || vertex2 == 0)
		{
			break;
		}

		insertEdge(vertex1, vertex2);

	}

}

// -----------------------initializeNodeData----------------------------------
// Description: Fills in the cost in the Adjacency matrix representation 
// Precondition: Adjacency matrix have been initialized to default values
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphL::initializeNodeData(istream& istream)
{
	for (int i = 1; i <= size; i++)
	{
		AdjList[i].data = new NodeData;
		AdjList[i].data->setData(istream);
	}
}

// -----------------------insertEdge---------------------------------------
// Description: Fills in the cost in the Adjacency matrix representation 
// Precondition: Adjacency matrix have been initialized to default values
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphL::insertEdge(int vertex1, int vertex2)
{
	if (AdjList[vertex1].edgeHead == NULL)
	{
		EdgeNode* newNode = new EdgeNode;
		newNode->adjGraphNode = vertex2;
		newNode->nextEdge = NULL;
		AdjList[vertex1].edgeHead = newNode;

	}
	else
	{
		EdgeNode* previous = AdjList[vertex1].edgeHead;
		EdgeNode* current = previous->nextEdge;

		EdgeNode* newNode = new EdgeNode;
		newNode->adjGraphNode = vertex2;
		newNode->nextEdge = previous;
		AdjList[vertex1].edgeHead = newNode;

	}
}

// -----------------------initializeAdjacencyList----------------------------
// Description: Fills in the cost in the Adjacency matrix representation 
// Precondition: Adjacency matrix have been initialized to default values
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphL::initializeAdjacencyList()
{
	for (int i = 1; i <= size; i++)
	{
		AdjList[i].edgeHead = NULL;
		AdjList[i].data = NULL;
		AdjList[i].visited = false;

	}
}

// ----------------------- displayGraph  ------------------------------------
// Description: Fills in the cost in the Adjacency matrix representation 
// Precondition: Adjacency matrix have been initialized to default values
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphL::displayGraph() const
{
	for (int i = 1; i <= size; i++)
	{
		// create temp node
		EdgeNode* current = AdjList[i].edgeHead;

		// display the node data 
		cout << "Node " << i << "     " 
			<< *AdjList[i].data << endl;

		while (current != NULL)
		{
			cout << "    edge " << i << " " 
				<< current->adjGraphNode << endl;

			// update temp pointer to next pointer 
			current = current->nextEdge;
		}

		cout << endl;
	}
}

// ----------------------- depthFirstSearch ----------------------------------
// Description: traverses graph using a a dept first search algorithm 
// Precondition: depthFirstSearch() helper function created
// Features: Calls helper function and executes the depth first search algorithm
// ---------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering: ";
	depthFirstSearch(1);
	cout << endl;
}

// ----------------------- depthFirstSearch ----------------------------------
// Description:  traverses graph using a a dept first search algorithm 
// Precondition: Adjaceny matrix created
// Features: recursively executes the depth first search algorithm
// ---------------------------------------------------------------------------
void GraphL::depthFirstSearch(int vertex)
{
	// print the value
	cout << vertex << " ";

	// mark visited
	AdjList[vertex].visited = true;

	// create temp node to traverse linked list
	EdgeNode* current = AdjList[vertex].edgeHead;

	// proceed while not NULL
	while(current != NULL) 
	{
		if (!AdjList[current->adjGraphNode].visited)
		{
			// recursively call 
			depthFirstSearch(current->adjGraphNode);
		}
		current = current->nextEdge;
	}
	
}

// ----------------------- deleteLinkedList----------------------------------
// Description: deletes the linked list in the adjaceny list from a 
// Precondition: Adjaceny matrix created
// Features: deletes the linked list in the adjaceny list recursively
// ---------------------------------------------------------------------------
void GraphL::deleteLinkedList(EdgeNode*& N)
{
	// base case
	if (N->nextEdge != NULL)
	{
		// recusive call
		deleteLinkedList(N->nextEdge);
	}

	delete N;
	N = NULL;
}

// ----------------------- clearAdjList----------------------------------
// Description: clears and deletes out the whole adjaceny list
// Precondition: deleteLinkedList created
// Features: clears and deletes out the whole adjaceny list and calls,
// deleteLinkedList with in the for loop
// ---------------------------------------------------------------------------
void GraphL::clearAdjList()
{
	for (int i = 1; i <= size; i++)
	{
		if (AdjList[i].edgeHead != NULL)
		{
			// call to helper method to delete linked list
			deleteLinkedList(AdjList[i].edgeHead);
		}

		// deletes the node data
		delete AdjList[i].data;
	}
	// after all that has been deleted
	// we can now proceed and delete the array
	delete AdjList;
}