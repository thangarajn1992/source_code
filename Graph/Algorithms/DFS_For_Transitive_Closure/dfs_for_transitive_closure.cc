// C++ program to print transitive closure of a graph
#include <iostream>
#include <vector>

using namespace std;

class Graph {
	int V; // No. of vertices
	vector<vector<bool>> tc; // To store transitive closure
	vector<vector<int>> adj; // array of adjacency lists
	

public:
    // Constructor
	Graph(int V) {
        this->V = V;
        adj.resize(V);

        tc.resize(V);
        for(int v = 0; v < V; v++)
            tc[v].resize(V, false);
    }

	// function to add an edge to graph
	void addEdge(int v, int w) { 
        adj[v].push_back(w); 
    }

    // A recursive DFS traversal function that finds
    // all reachable vertices for s.
    void DFSUtil(int s, int u) {
        // Mark reachability from s to u as true.
        tc[s][u] = true;

        // Find all the vertices reachable through u
        for(int &v : adj[u])
        {
            if (tc[s][v] == false) {
                if (v == s) {
                    tc[s][v] = 1;
                }
                else {
                    DFSUtil(s, v);
                }
            }
        } 
    }

	// The function to find transitive closure. It uses
    // recursive DFSUtil()
	void transitiveClosure() {
        // Call the recursive helper function to print DFS
        // traversal starting from all vertices one by one
        for (int i = 0; i < V; i++)
            DFSUtil(i, i); // Every vertex is reachable from self.

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << tc[i][j] << " ";
            cout << endl;
        }
    }
};

int main()
{

	// Create a graph given in the above diagram
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);
	cout << "Transitive closure matrix is \n";
	g.transitiveClosure();
	return 0;
}

/*
Output:
Transitive closure matrix is 
1 1 1 1 
1 1 1 1 
1 1 1 1 
0 0 0 1 
*/