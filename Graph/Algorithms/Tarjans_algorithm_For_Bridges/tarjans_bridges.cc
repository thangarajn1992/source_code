// A C++ program to find bridges in a given undirected graph
#include<iostream>
#include <vector>

#define NO_PARENT -1
using namespace std;

// A class that represents an undirected graph
class Graph
{
	int V; // No. of vertices
	vector<vector<int>> adj; // A dynamic array of adjacency lists

public:
    // Constructor
	Graph(int V) {
       this->V = V;
       adj.resize(V);
    }

    // to add an edge to graph
	void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // prints all bridges
	void bridge() {
        // Mark all the vertices as not visited
        vector<bool> visited(V, false);
        vector<int> disc(V);
        vector<int> low(V);
        vector<int> parent(V, NO_PARENT);
        int time = 0;

        // To handle disconnected graphs
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                bridgeUtil(i, time, visited, disc, low, parent);
        }

    // A recursive function that finds and prints bridges using
    // DFS traversal
    // u --> The vertex to be visited next
    // time --> current time
    // visited[] --> keeps track of visited vertices
    // disc[] --> Stores discovery times of visited vertices
    // parent[] --> Stores parent vertices in DFS tree
	void bridgeUtil(int u, int &time, vector<bool> &visited, vector<int> &disc, 
                    vector<int> &low, vector<int> &parent) {
        
        // Mark the current node as visited
        visited[u] = true;

        // Initialize discovery time and low value
        disc[u] = low[u] = ++time;

        for (int &v : adj[u])
        {
            // If v is not visited yet, then recur for it
            if (!visited[v])
            {
                parent[v] = u;
                bridgeUtil(v, time, visited, disc, low, parent);

                // Check if the subtree rooted with v has a
                // connection to one of the ancestors of u
                low[u] = min(low[u], low[v]);

                // If the lowest vertex reachable from subtree
                // under v is below u in DFS tree, then u-v
                // is a bridge
                if (low[v] > disc[u])
                    cout << u <<" " << v << endl;
            }

            // Update low value of u for parent function calls.
            else if (v != parent[u])
                low[u] = min(low[u], disc[v]);
        }
    }
};

int main()
{
	// Create graphs given in above diagrams
	cout << "\nBridges in first graph \n";
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	g1.bridge();

	cout << "\nBridges in second graph \n";
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.bridge();

	cout << "\nBridges in third graph \n";
	Graph g3(7);
	g3.addEdge(0, 1);
	g3.addEdge(1, 2);
	g3.addEdge(2, 0);
	g3.addEdge(1, 3);
	g3.addEdge(1, 4);
	g3.addEdge(1, 6);
	g3.addEdge(3, 5);
	g3.addEdge(4, 5);
	g3.bridge();

	return 0;
}

/*
Output:
Bridges in first graph 
3 4
0 3

Bridges in second graph 
2 3
1 2
0 1

Bridges in third graph 
1 6
*/