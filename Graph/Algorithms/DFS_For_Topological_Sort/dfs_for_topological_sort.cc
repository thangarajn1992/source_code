// A C++ program to print topological sorting of a DAG
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Class to represent a graph
class Graph {
	// No. of vertices'
	int V;

	// Pointer to an array containing adjacency listsList
	vector<vector<int>> adj;

public:
	// Constructor
	Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

	// function to add an edge to graph
	void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    // A recursive function used by topologicalSort
    void topologicalSortUtil(int u, vector<bool> &visited,
                             stack<int>& Stack)
    {
        // Mark the current node as visited.
        visited[u] = true;

        // Recur for all the vertices
        // adjacent to this vertex
        for(int &v : adj[u])
            if (!visited[v])
                topologicalSortUtil(v, visited, Stack);

        // Push current vertex to stack
        // which stores result
        Stack.push(u);
    }

    // The function to do Topological Sort.
    // It uses recursive topologicalSortUtil()
    void topologicalSort()
    {
        stack<int> Stack;

        // Mark all the vertices as not visited
        vector<bool> visited(V, false);

        // Call the recursive helper function
        // to store Topological
        // Sort starting from all
        // vertices one by one
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                topologicalSortUtil(i, visited, Stack);

        // Print contents of stack
        while (Stack.empty() == false) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};

int main()
{
	// Create a graph given in the above diagram
	Graph g(6);
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);

	cout << "Following is a Topological Sort of the given "
			"graph \n" ;
    g.topologicalSort();
    cout << endl;

	return 0;
}

/* 
Output:
Following is a Topological Sort of the given graph 
5 4 2 3 1 0 
*/