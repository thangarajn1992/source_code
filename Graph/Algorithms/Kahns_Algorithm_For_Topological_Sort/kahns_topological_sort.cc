// A C++ program to print topological
// sorting of a graph using indegrees.
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Class to represent a graph
class Graph {
	// No. of vertices'
	int V;

	// Pointer to an array containing
	// adjacency listsList
	vector<vector<int>> adj;

public:
	// Constructor
	Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

	// Function to add an edge to graph
	void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

	// prints a Topological Sort of the complete graph
	void topologicalSort() {
        // Create a vector to store indegrees of all vertices. 
        // Initialize all indegrees as 0.
        vector<int> in_degree(V, 0);

        // Traverse adjacency lists to fill indegrees of vertices. 
        // This step takes O(V+E) time
        for (int u = 0; u < V; u++) {
            for(int &v : adj[u]) {
                in_degree[v]++;
            }
        }

        // Create an queue and enqueue
        // all vertices with indegree 0
        queue<int> q;
        for (int v = 0; v < V; v++)
            if (in_degree[v] == 0)
                q.push(v);

        // Initialize count of visited vertices
        int cnt = 0;

        // Create a vector to store result 
        // (A topological ordering of the vertices)
        vector<int> top_order;

        // One by one dequeue vertices from queue and 
        // enqueue adjacents if indegree of
        // adjacent becomes 0
        while (!q.empty()) {
            // Extract front of queue
            // and add it to topological order
            int u = q.front(); q.pop();
            top_order.push_back(u);

            // Iterate through all its neighbouring nodes
            // decrease their in-degree by 1
            for(int &v : adj[u]) {
                // If in-degree becomes zero,
                // add it to queue
                in_degree[v]--;
                if (in_degree[v] == 0)
                    q.push(v);
            }
            cnt++;
        }

        // Check if there was a cycle
        if (cnt != V) {
            cout << "There exists a cycle in the graph\n";
            return;
        }

        // Print topological order
        for (int i = 0; i < top_order.size(); i++)
            cout << top_order[i] << " ";
        cout << endl;
    }
};

int main()
{
	// Create a graph given in the
	// above diagram
	Graph g(6);
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);

	cout << "Following is a Topological Sort of\n";
	g.topologicalSort();

	return 0;
}
/* 
Output:
Following is a Topological Sort of
4 5 2 0 3 1 
*/