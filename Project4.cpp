// Project4.cpp : This file contains the program to create and display a Binary Tree data structure 
//


#include <iostream>
using namespace std;

class Tree // Contains Array of Parents with Index as children
{
protected:
	int* parentArr; // The parent array
	int root; //Root of the tree at the moment
	int size; // The size of the Array
public:
	Tree(int nodes); //Non default constructor
	~Tree(); // Destuctor
	Tree(const Tree& other); //Copy Constructor
	int LCA(int i, int j); // Returns Least Common Ancestor
	int getParent(int i); // Return the parent of whatever child is passed in
	int getRoot(); // Return the root of the tree
	void setRoot(int newRoot); // sets the root of the tree
	void setParent(int node, int parent); // Set the new parent for the previously parent's tree
	void nodesAtLevel(int i); // Return the level that the node is currently placed in
	int level(int i); //  the level of node i
	int height(); // Return the height of the tree
	void preOrderV(int node); // Print out the tree in pre order traversal (Optional)
	void preOrder();
	void Children(int child);// For printing out Children
	void Siblings(int sib); // For printing out Siblings

	friend ostream&  operator<<(ostream& os, const Tree& P) //inside the class (MUST DO)
	{
		for (int i = 0; i < P.size; i++)
		{
			cout << i << " : " << P.parentArr[i] << endl; // Display Children and Parents Children as index and Parent as the value
		}
		return os;
	}

};
Tree:: ~Tree() // Destruct and delete pointers/ Dynamically created objects
{
	if (parentArr != NULL)
	{
		delete [] parentArr;
		size = 0;
		root = 0;
		
	}
}
Tree:: Tree(const Tree& other) // Copy arrays, roots and size
{
	root = other.root;
	size = other.size;
	parentArr = new int[size];
	for (int i = 0; i < size; i++)
	{
		parentArr[i] = other.parentArr[i];
	}
}
void Tree::Children(int child) // Prints children of parent
{
	for (int i = 0; i < size; i++)
	{
		if (parentArr[i] == child)
		{
			cout << i << ", ";
		}
		
	}
}
void Tree::Siblings(int sib) // Print the siblings
{
	for (int i = 0; i < size; i++)
	{
		if (parentArr[sib] == parentArr[i] && i != sib)
		{
			cout << i << ", ";
		}
	
	}
}
Tree::Tree(int nodes) // Initializes the size and parent array to a size of whatever is passed in
{
	size = nodes;
	parentArr = new int[nodes];
}

int Tree::LCA(int node1, int node2) // Returns the Least Common Ancestor of two nodes that are passed in
{
	int n2 = node2; // Set a temp node to what we pass in
	while (node1 != -1) 
	{
		while (node2 != -1)
		{
			if (node1 == node2)
			{
				return node1;
			}
			else
			{
				node2 = parentArr[node2];
			}
		}
		node2 = n2; // Reset the node back to the what was passed in to restart the loop
		node1 = parentArr[node1];
	}
}

int Tree:: getParent(int i) // Returns the parent of a specific node
{
	return parentArr[i];
}

int Tree::getRoot() //Returns the root of the parent Array
{
	return root;
}

void Tree::setRoot(int newRoot) // Set the root in the array
{
	root = newRoot;
}

void Tree::setParent(int n, int p) // Sets the parent of the array
{
	parentArr[n] = p;
}

void Tree::nodesAtLevel(int node) // Prints what nodes are at the node that is passed in
{
	for (int i = 0; i < size; i++)
	{
		if (node == level(i))
		{
			cout << i << ",";
		}
	}
}

int Tree::level(int i) // Returns the level of the node that is passed in
{
	if (parentArr[i] != -1)
	{
		return 1 + level(parentArr[i]);
	}
	else
	{
		return 1;
	}
}

int Tree::height() //Returns the height of the tree
{
	int hight = 0;
	int counter = size;
	for (int i = 0; i < size; i++)
	{
		if (parentArr[counter] == -1)
		{
			hight = level(i);
		}
		else
		{
			counter--;
		}
	}
	return hight;
}

void Tree:: preOrderV(int parentNode) //Prints the parent array in order
{
	for (int i = 0; i < size; i++)
	{
		if (parentArr[i] == parentNode)
		{
			cout << i << " ";
			preOrderV(i);
		}
	}
}
void Tree::preOrder()
{
	cout << root << " ";
	preOrderV(root);
}
int main()
{
		Tree* myTree;
		int	numNodes, node, parent;
		cin >> numNodes;
		 myTree = new Tree(numNodes);
		for (int i = 0; i < numNodes; i++) 
		{
			cin >> node >> parent;
			(*myTree).setParent(node, parent);
			if (parent == -1) 
			{
				(*myTree).setRoot(node);
			}
		}
		cout << "The tree that we just read is	" << endl;
		cout << *myTree << endl;
		cout << "Printing other methods " << endl;
		Tree* newTree = new Tree(*myTree);
		cout << "The tree that we just copied is " << endl;
		cout << *newTree << endl;
		cout << "The root of the tree is : " << (*myTree).getRoot() << endl;
		cout << "The least common ancestor of nodes 3 and 8 is: " << (*newTree).LCA(3, 8) << endl;
		cout << "The least common ancestor of nodes 13 and 8 is: " << (*newTree).LCA(13, 8) << endl;
		cout << "The least common ancestor of nodes 13 and 11 is: " << (*myTree).LCA(13, 11) << endl;
		cout << "The children of node 12 is: "; (*myTree).Children(12); cout << endl;
		cout << "The children of node 10 is: "; (*myTree).Children(10); cout << endl;
		cout << "The siblings of node 3 is: "; (*myTree).Siblings(3); cout << endl;
		cout << "The siblings of node 12 is: "; (*myTree).Siblings(12); cout << endl;
		cout << "The nodes at level 3 are: "; (*myTree).nodesAtLevel(3); cout << endl;

		cout << "The height of the tree is: " << (*myTree).height() << endl;
		cout << "The level of node 3 in the tree is : " << (*myTree).level(3) << endl;
		cout << "The level of node 12 in the tree is : " << (*myTree).level(12) << endl;
		cout << "The preorder traversal of the tree is " << endl; (*myTree).preOrder();
		delete myTree;
		delete newTree;
		return 0;
}