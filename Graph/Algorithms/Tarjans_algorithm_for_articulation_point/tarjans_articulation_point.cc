#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adj;
    int V;

public:
    // Constructor
    Graph(int v) {
        this->V = v;
        adj.resize(V);
    }

    // Utility function to add an edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // A recursive function that find articulation
    // points using DFS traversal
    // u --> The vertex to be visited next
    // visited --> keeps track of visited vertices
    // disc --> Stores discovery times of visited vertices
    // low -- >> earliest visited vertex (the vertex with minimum
    // discovery time) that can be reached from subtree
    // rooted with current vertex
    // parent --> Stores the parent vertex in DFS tree
    // isAP --> Stores articulation points
    void APUtil(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, 
                int &time, int parent, vector<bool> &isAP) {
        // Count of children in DFS Tree
        int children = 0;

        // Mark the current node as visited
        visited[u] = true;

        // Initialize discovery time and low value
        disc[u] = low[u] = ++time;

        // Go through all vertices adjacent to this
        for (int v : adj[u]) {
            // If v is not visited yet, then make it a child of u
            // in DFS tree and recur for it
            if (!visited[v]) {
                children++;
                APUtil(v, visited, disc, low, time, u, isAP);

                // Check if the subtree rooted with v has
                // a connection to one of the ancestors of u
                low[u] = min(low[u], low[v]);

                // If u is not root and low value of one of
                // its child is more than or equal discovery value of u.
                // (No back edge to one of ancestor of u)
                if (parent != -1 && low[v] >= disc[u])
                    isAP[u] = true;
            }

            // Update low value of u for parent function calls.
            else if (v != parent)
                low[u] = min(low[u], disc[v]);
        }

        // If u is root of DFS tree and has two or more children.
        if (parent == -1 && children > 1)
            isAP[u] = true;
    }

    void AP() {
        vector<int> disc(V,0);
        vector<int> low(V);

        vector<bool> visited(V, false);
        vector<bool> isAP(V, false);
        int time = 0, par = -1;

        // To handle disconnected graph
        for (int u = 0; u < V; u++)
            if (!visited[u])
                APUtil(u, visited, disc, low, time, par, isAP);

        // Printing the APs
        for (int u = 0; u < V; u++)
            if (isAP[u] == true)
                cout << u << " ";
    }
};

int main()
{
	// Create graphs given in above diagrams
    Graph g1(5);
	cout << "Articulation points in first graph \n";
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	g1.AP();

	cout << "\nArticulation points in second graph \n";
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.AP();

	cout << "\nArticulation points in third graph \n";
    Graph g3(7);
	g3.addEdge(0, 1);
	g3.addEdge(1, 2);
	g3.addEdge(2, 0);
	g3.addEdge(1, 3);
	g3.addEdge(1, 4);
	g3.addEdge(1, 6);
	g3.addEdge(3, 5);
	g3.addEdge(4, 5);
	g3.AP();

	return 0;
}

/*
Output:
Articulation points in first graph 
0 3 
Articulation points in second graph 
1 2 
Articulation points in third graph 
1
*/