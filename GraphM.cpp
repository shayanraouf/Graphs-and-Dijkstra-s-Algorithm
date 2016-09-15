// ------------------------------------------------ GraphM.cpp ------------------
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
// ----------------------------------------------------------------------------
#include "GraphM.h"
#include <fstream>

// ------------------------------------ GraphM() ------------------------------
// Description: Constructor that initializes elements to default values 
// Precondition: initializeTableType() and initializeAdjacencyMatrixCost()
// have been created. 
// Features: Calls two functions initializes elements to default values
// ----------------------------------------------------------------------------
GraphM::GraphM()
{
	// call to helper functions
	initializeTableType();
	initializeAdjacencyMatrixCost();
	size = 0;
}

// ------------------------------------ ~GraphM() ------------------------------
// Description: Distructor that deletes and empties memory space in heap
// Precondition: initializeTableType() and initializeAdjacencyMatrixCost()
// Features: Call two functions initializes elements to default values
// ----------------------------------------------------------------------------
GraphM::~GraphM()
{
}

// ------------------------ initializeTableType() ------------------------------
// Description: initializes TableType struct to default values
// Precondition: NONE
// Features: iteraties through a 100X100 matrix in a nested for loop
// initializing the TableType data members: dist,visited and path to
//	infinity, false (not visited) and the path to zero 
// ----------------------------------------------------------------------------
void GraphM::initializeTableType()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			T[i][j].dist = INFINITE;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
}

// ------------------------ setAllNotVisted() ------------------------------
// Description: initializes TableType boolean visted to false
// Precondition: NONE
// Features: iteraties through a 100X100 matrix in a nested for loop
// initializing the TableType data members: visted to false
// ----------------------------------------------------------------------------
void GraphM::setAllNotVisted()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			T[i][j].visited = false;
		}
	}
}
// ------------------------ initializeTableType() ------------------------------
// Description: initializes TableType struct to default values
// Precondition: NONE
// Features: iteraties through a 100X100 matrix in a nested for loop
// initializing the the adjacency matrix costs to infinity 
// ----------------------------------------------------------------------------
void GraphM::initializeAdjacencyMatrixCost()
{
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++)
		{
			C[i][j] = INFINITE;
		}
	}
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
void GraphM::buildGraph(istream& istream)
{
	// initializes number of nodes
	istream >> size; 
	string lineBreak;

	// reads extra white space
	getline(istream, lineBreak);

	// initializes values in the NodeData array
	initializeNodeData(istream);

	// initializing the tree integers we need
	int vertex1, vertex2, cost;
	while (true)
	{
		if (istream.eof())
		{
			break;
		}
		istream >> vertex1;
		istream >> vertex2;
		istream >> cost;
		if (vertex1 == 0 || vertex2 == 0 || cost == 0)
		{
			break;
		}
		insertEdge(vertex1, vertex2, cost);
	}

}

// -----------------------initializeNodeData(istream& istream) --------------
// Description: iterates through NodeData array
// Precondition: Pre-formated txt file
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphM::initializeNodeData(istream& istream)
{
	for (int i = 1; i <= size; i++)
	{
		data[i].setData(istream);
	}
}

// -----------------------findShortestPath-----------------------------------
// Description: find the shortest path between every node to every other
//              node in the graph and TableType T is updated with 
//				shortest path information. This function executes Dijkstra's 
//				algorithm 
// Precondition: Adjacency matrix have been created with vertices and edges
// Features: 
// ---------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	int V = 0;
	int W = 0;

	for (int i = 1; i <= size; i++)
	{
		// distance of sourse initialized to 0
		T[i][i].dist = 0; 

		for (int j = 1; j <= size; j++)
		{
				V = NotVistedMin(i);
				T[i][V].visited = true;

				for (int k = 1; k <= size; k++)
				{
					
					W = k;
					// if adjacent and not visited
					if (C[V][W] != INFINITE && !(T[i][W].visited))
					{
						// update adjacent to current 
						if(T[i][W].dist > (T[i][V].dist + C[V][W]))
						{
							T[i][W].dist = T[i][V].dist + C[V][W];
							T[i][W].path = V;
						}

					}
					
				}

		}

		// set all to not visited 
		// then re-iterate with next vertex
		setAllNotVisted(); 
	}

}

// -----------------------NotVistedMin---------------------------------------
// Description: returns the smallest none visited adjacent vertex
// Precondition: prove the row (vertex)
// Features: returns the smallest none visited adjacent vertex
// by running through a row in the matrix using a simple get min algorithm 
// ---------------------------------------------------------------------------
int GraphM::NotVistedMin(int row)
{
	int min = 1;
	int max = INFINITE;
	for (int i = 1; i <= size; i++)
	{
		// if the distance is less then max
		// and if not visited
		if (T[row][i].dist < max &&  !(T[row][i].visited))
		{
			// update min and max
			min = i;
			max = T[row][i].dist;
		}
	}

	//returns the min index. 
	return min;
}

// -----------------------insertEdge---------------------------------------
// Description: Fills in the cost in the Adjacency matrix representation 
// Precondition: Adjacency matrix have been initialized to default values
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphM::insertEdge(int startIndex, int endIndex, int cost)
{
	if (startIndex > 0 && startIndex < 101
		&& endIndex > 0 && endIndex < 101
		&& cost > 0)
	{
		C[startIndex][endIndex] = cost;
	}
	
}

// -----------------------removeEdge----------------------------------------
// Description: Fills in the cost in the Adjacency matrix representation 
// Precondition: Adjacency matrix have been initialized to default values
// Features:  given an istream arugment passed by reference, this function
// initializes the NodeData string data member 
// ---------------------------------------------------------------------------
void GraphM::removeEdge(int startIndex, int endIndex)
{
	if (startIndex > 0 && startIndex < 101
		&& endIndex > 0 && endIndex < 101)
	{
		C[startIndex][endIndex] = INFINITE;
	}
	
	
}

// -----------------------displayAll()   ------------------------------------
// Description: displays the different path's in the matrix  
// Precondition: NONE
// Features: Loops through and displays all the path ways  
// ---------------------------------------------------------------------------
void GraphM::displayAll() const
{

	cout << "Description              From node   To node  " <<
		"Dijkstra's   Path    " << endl;

	for (int i = 1; i <= size; i++)
	{
		// print the street name
		cout << setw(50) << left << data[i] << endl;

		for (int j = 1; j <= size; j++)
		{
			// if refereing to self then skip
			if (j == i) continue; 

			if (T[i][j].dist > 0 && T[i][j].dist != INFINITE)
			{
				// set margines appropriately for proper display
				cout << setw(30) << right << i << setw(13) << right << j;
				cout << setw(5) << " " << left << T[i][j].dist << setw(10);
				getPath(i, j);
				cout << endl;

			}
			else
			{
				// no path, print ---
				cout << setw(30) << right << i << setw(13) << j << setw(5);
				cout << " " << left << "---" << setw(10) << endl;

			}
			
		}

		cout << endl;
	}
}

// -----------------------display()   ------------------------------------
// Description: displays the different path's in the matrix  
// Precondition: getPath and getPathData created
// Features: Loops through and displays all the path ways  
// ---------------------------------------------------------------------------
void GraphM::display(int fromPath, int toPath) const
{
	cout << setw(5) << " ";
	cout << setw(5) << left << fromPath << setw(5) << toPath;
	if (T[fromPath][toPath].dist != INFINITE)
	{
		cout << setw(7) << T[fromPath][toPath].dist;

		// call to get path
		getPath(fromPath, toPath);

		cout << endl;

		// call to the street name 
		getPathData(fromPath, toPath);

	}
	else
	{
		cout << "---";
	}
	cout << endl;
}

// ----------------------- getPath() -----------------------------------------
// Description: displays the different path's in the matrix  
// Precondition: NONE
// Features: displays all the path ways recursively 
// ---------------------------------------------------------------------------
void GraphM::getPathData(int fromPath, int toPath) const
{
	if (fromPath != toPath && T[fromPath][toPath].dist < INFINITE)
	{
		getPathData(fromPath, T[fromPath][toPath].path);
	}

	cout << data[toPath] << endl;

}

// ----------------------- getPath() -----------------------------------------
// Description: displays the path from a starting vertex to an ending vertex
// Precondition: NONE
// Features: displays the path executing the function recursively 
// ---------------------------------------------------------------------------
void GraphM::getPath(int fromPath, int toPath) const
{
	if (fromPath != toPath && T[fromPath][toPath].dist < INFINITE)
	{
		getPath(fromPath, T[fromPath][toPath].path);
	}
		cout << " " << toPath;
	
}