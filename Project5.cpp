//Project5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Project Will store vertices and edges and Create a Graph
// Has a Breadth First Search and Depth First Search method for both Data Structures
// Version 4

#include <iostream>
#include <queue>
#include <list>
using namespace std;

class AdjacencyMatrix
{
protected:
	int** GraphMatrix;	//GraphMatrix Data structure
	int numberOfVertices; //Number of vertices
	queue<int> Q; // My queue that is used for DFS
	list<int>* LBFS;	// List for BFS
	list<int>* BAF;
	bool* visitedBFS;	//Array of which neighbors are visited for BFS
	bool* visitedDFS;	// Array of which neighbors are visited for DFS
	int* parentBFS;	// Parent array for BFS
	int* parentDFS;	// Parent array for DFS
	int** Dmatrix;
public:
	AdjacencyMatrix(const AdjacencyMatrix& M); //Copy constructor
	~AdjacencyMatrix(); // Destructor 
	void operator=(const AdjacencyMatrix &M); // Copy constructor
	AdjacencyMatrix(int numOfVertice);	// Initializer for Adjacency
	void deleteEdge(int i, int j);	// Delete edge 
	void addEdge(int i, int j);	// Adding edges for vertices where i is vertice and j is edge
	void DFS(int x); // Depth First Search for Adjacency Matrix
	void BFS(int start); // Breath First Search for Adjacency Matrix
	void DFSUtil(int v, bool visited[]); // DFS that calls into DFS recursively
	friend ostream&  operator<<(ostream& os, const AdjacencyMatrix& P) //inside the class (MUST DO)
	{
		for (int i = 0; i < P.numberOfVertices; i++)
		{
			for (int j = 0; j < P.numberOfVertices; j++)
			{
				if (P.Dmatrix[i][j] == 1)
				{
					cout << "(" << i << "," << j << ")";
				}
			}
		}
		cout << endl;
		return os;
	}
};

void AdjacencyMatrix::BFS(int start)
{
	parentBFS = new int[numberOfVertices]; // Initilize the parent Array of BFS
	parentBFS[start] = -1; // Set the position of what ever is passed in to -1 in the array
	bool *visited = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) // Mark all the vertices as not visited 
	{
		visited[i] = false;
	}
	list<int> queue; // Create a queue for BFS 

	visited[start] = true; 	// Mark the current vertice as visited and enqueue it
	queue.push_back(start);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<int>::iterator i;

	while (!queue.empty())
	{
		start = queue.front(); // Dequeue a vertex from queue and print it 
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (i = BAF[start].begin(); i != BAF[start].end(); ++i)
		{
			if (!visited[*i])
			{
				parentBFS[*i] = start; // Insert into parent array
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
	for (int i = 0; i < numberOfVertices; i++)
	{
		cout << i << ":" << parentBFS[i] << " "; // Print out parent array
	}
}




void AdjacencyMatrix::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and 
	// print it 
	visited[v] = true;
	// Recur for all the vertices adjacent 
	// to this vertex 
	list<int>::iterator i;
	for (i = LBFS[v].begin(); i != LBFS[v].end(); ++i)
	{
		if (!visited[*i])
		{
			parentDFS[*i] = v;
			DFSUtil(*i, visited);
		}

	}
}


void AdjacencyMatrix::DFS(int x)
{
	// DFS traversal of the vertices reachable from v. 
	// It uses recursive DFSUtil() 
	parentDFS[x] = -1;
	// Mark all the vertices as not visited 
	bool *visitedDFS = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		visitedDFS[i] = false;
	}

	DFSUtil(x, visitedDFS); //Recursively call DFS Util

	for (int i = 0; i < numberOfVertices; i++)
	{
		cout << i << ":"<< parentDFS[i] << " "; // Print parent array
	}

}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& M) // Copy constructor
{
	BAF = M.BAF;
	numberOfVertices = M.numberOfVertices; // Copy size/ number of vertice's
	Dmatrix = new int*[numberOfVertices];
	GraphMatrix = new int*[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) // Loop through amount of vertices
	{
		Dmatrix[i] = new int[numberOfVertices];
		GraphMatrix[i] = new int[numberOfVertices];
		for (int j = 0; j < numberOfVertices; j++) // Loop through number of vertices of for J
		{
			Dmatrix[i][j] = M.Dmatrix[i][j];
			GraphMatrix[i][j] = M.GraphMatrix[i][j]; // Copy values of both Matrix's
		}
	}
}

void AdjacencyMatrix ::operator=(const AdjacencyMatrix& M) // Same thing as copy constructor
{
	BAF = M.BAF;
	numberOfVertices = M.numberOfVertices;
	GraphMatrix = new int*[numberOfVertices];
	Dmatrix = new int*[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		GraphMatrix[i] = new int[numberOfVertices];
		Dmatrix[i] = new int[numberOfVertices];
		for (int j = 0; j < numberOfVertices; j++)
		{
			Dmatrix[i][j] = M.Dmatrix[i][j];
			GraphMatrix[i][j] = M.GraphMatrix[i][j];
		}
	}
}

AdjacencyMatrix ::~AdjacencyMatrix() // Destructor
{
	delete[] GraphMatrix;
	delete[] LBFS;
	delete[] BAF;
	delete[] visitedBFS;
	delete[] visitedDFS;
	delete[] Dmatrix;
}


AdjacencyMatrix::AdjacencyMatrix(int numOfVertice)
{
	BAF = new list<int>[numOfVertice];
	parentDFS = new int[numOfVertice]; // Initialize parent array
	LBFS = new list<int>[numOfVertice]; // Initilize BFS list
	numberOfVertices = numOfVertice; // Initilize our size
	Dmatrix = new int*[numOfVertice];
	GraphMatrix = new int*[numOfVertice]; // Initilize double array
	for (int i = 0; i < numberOfVertices; i++) // Loop through number of vertices
	{
		Dmatrix[i] = new int[numberOfVertices];
		GraphMatrix[i] = new int[numberOfVertices]; // Initilize row
		for (int j = 0; j < numberOfVertices; j++) // Loop though number of vertices again
		{
			GraphMatrix[i][j] = 0; // Assign it to zero because no vertices or edges has been added
			Dmatrix[i][j] = 0;
		}
	}
}

void AdjacencyMatrix::addEdge(int i, int j)
{
	Dmatrix[i][j] = 1; // Add vertice to edge
	GraphMatrix[i][j] = 1; // Add vertice to edge
	GraphMatrix[j][i] = 1; // Add edge to vertice because it is undirected
	LBFS[i].push_back(j);
	BAF[i].push_back(j);
	BAF[j].push_back(i);
}

void AdjacencyMatrix::deleteEdge(int i, int j)
{
	GraphMatrix[i][j] = 0;
	GraphMatrix[j][i] = 0;
}
class AdjacencyList
{
protected:
	list<int>* GraphList; // Create Graphlist that hold my AdjacencyList
	list<int>* myList;	// Used to find DFS and BFS
	int numOfVert; //Number of vertices
	int* parentDFS; // parent array for Depth First Search
	int* parentBFS; // parent array for Breadth First Search
	bool* visitedDFS; // visited array for Depth First Search
	bool* visitedBFS; // visited array for Breadth First Search
public:
	AdjacencyList(const AdjacencyList& L); // Copy Constructor
	~AdjacencyList(); // Destructor
	void operator=(const AdjacencyList &L); // = overloaded operator
	AdjacencyList(int verticeNum); // Initialize Constructor
	void addEdge(int i, int j); // Add vertices at a certain position and push in what edges it is connected to
	void deleteEdge(int i); // Delete the edge
	void BFS(int x); // Breadth First Search
	void DFS(int x); // Depth First Search
	void DFSUtil(int v, bool visited[]); // Recursive method used for Depth First Search
	friend ostream&  operator<<(ostream& os, const AdjacencyList& P) //inside the class (MUST DO)
	{

		for (int i = 0; i < P.numOfVert; i++)
		{
			for (auto x : P.myList[i])
			{
				cout << "(" << i << "," << x << ")";
			}
		}
		return os;
	}
};

AdjacencyList ::~AdjacencyList()
{
	delete[] visitedBFS;
	delete[] visitedDFS;
	delete[] parentBFS;
	delete[] parentDFS;
	delete[] myList;
	delete[] GraphList;
}

void AdjacencyList::DFSUtil(int v, bool visited[])
{
	visited[v] = true; // Mark the current node as visited
	// Recur for all the vertices adjacent 
	list<int>::iterator i;
	for (i = myList[v].begin(); i != myList[v].end(); ++i)
	{
		if (!visited[*i]) // If the neighbor hasnt already been visited
		{
			parentDFS[*i] = v; // Add it into the parent array
			DFSUtil(*i, visited);
		}

	}
}

void AdjacencyList::DFS(int x)
{
	parentDFS[x] = -1;
	for (int k = 0; k < numOfVert; k++) // Mark all the vertices as not visited 
	{
		visitedDFS[k] = false;
	}
	DFSUtil(x, visitedDFS); // Call the recursive helper function 

	for (int i = 0; i < numOfVert; i++)
	{
		cout << i << ":" << parentDFS[i] << " "; // Print out parent array 
	}
}


void AdjacencyList ::operator=(const AdjacencyList& L)
{
	GraphList = L.GraphList; // Copy values over
	numOfVert = L.numOfVert; // Copy size
	myList = L.myList; // Copy values over
}

AdjacencyList::AdjacencyList(const AdjacencyList& L)
{
	GraphList = L.GraphList; // Copy values over
	numOfVert = L.numOfVert; // Copy size
	myList = L.myList; // Copy values over
}

void AdjacencyList::BFS(int x)
{
	parentBFS = new int[numOfVert]; // Initilize the parent Array of BFS
	parentBFS[x] = -1; // Set the position of what ever is passed in to -1 in the array
	bool *visited = new bool[numOfVert];
	for (int i = 0; i < numOfVert; i++) // Mark all the vertices as not visited 
	{
		visited[i] = false;
	}
	list<int> queue; // Create a queue for BFS 

	visited[x] = true; 	// Mark the current vertice as visited and enqueue it
	queue.push_back(x);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<int>::iterator i;

	while (!queue.empty())
	{
		x = queue.front(); // Dequeue a vertex from queue and print it 
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (i = GraphList[x].begin(); i != GraphList[x].end(); ++i)
		{
			if (!visited[*i])
			{
				parentBFS[*i] = x; // Insert into parent array
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
	for (int i = 0; i < numOfVert; i++)
	{
		cout <<i << ":" << parentBFS[i] << " "; // Print out parent array
	}

}
AdjacencyList::AdjacencyList(int verticeNum)
{
	numOfVert = verticeNum; // Set the size to the global variable
	GraphList = new list<int>[numOfVert]; // Initilize the GraphList
	myList = new list<int>[numOfVert]; // Initilize the list array
	visitedBFS = new bool[numOfVert]; // Initilize the visited BFS array
	visitedDFS = new bool[numOfVert]; // Initilize the visitedDFS array
	parentDFS = new int[numOfVert]; // Initilize the parent Array of DFS
	parentBFS = new int[numOfVert]; // Initilize the parent Array of BFS

}
void AdjacencyList::addEdge(int vertice, int edge)
{
	GraphList[vertice].push_back(edge);
	GraphList[edge].push_back(vertice);
	myList[vertice].push_back(edge);
}
void AdjacencyList::deleteEdge(int i)
{
	GraphList[i].pop_front();
}

int main()
{
	int numberOfVertices, vertice, edge; // Declare variables
	cin >> numberOfVertices; // Bring in the size

	AdjacencyList* GraphList = new AdjacencyList(numberOfVertices); // Create AdjacencyList Graph
	AdjacencyMatrix* GraphMatrix = new AdjacencyMatrix(numberOfVertices); // Create AdjacencyMatrix Graph

	while (!cin.eof()) // Goes through entire file
	{
		cin >> vertice >> edge; // Bring in the vertices and edges
		GraphList->addEdge(vertice, edge);
		GraphMatrix->addEdge(vertice, edge);
	}

	cout << "AdjacencyList : " << endl;
	cout << (*GraphList);
	cout << endl;

	cout << "AdjacencyList Copied " << endl;
	AdjacencyList* copiedList = new AdjacencyList(*GraphList);
	cout << (*copiedList);
	cout << endl;

	cout << "Breadth First Search for Adjacency List : " << endl;
	GraphList->BFS(0);
	cout << endl;

	cout << "Depth First Search for Adjacency List : " << endl;
	GraphList->DFS(0);
	cout << endl;

	cout << "AdjacencyMatrix : " << endl;
	cout << (*GraphMatrix);
	cout << endl;

	cout << "AdjacencyMatrix copied " << endl;
	AdjacencyMatrix* copiedMatrix = new AdjacencyMatrix(*GraphMatrix);
	cout << (*copiedMatrix);
	cout << endl;

	cout << "Depth First Search on Adjacency Matrix : " << endl;
	GraphMatrix->DFS(0);
	cout << endl;

	cout << "Breadth First Search for Adjacency Matrix : " << endl;
	GraphMatrix->BFS(0);
	cout << endl;
	return 0;
}
