#include <iostream>
#include <vector>

using namespace std;

// The main function that finds shortest
// distances from src to all other vertices
// using Bellman-Ford algorithm. The function
// also detects negative weight cycle
// edges are in format (u, v, w)
void bellman_ford_shortest_path(vector<vector<int>> &edges, int V, int src)
{
    // Initialize distance of all vertices as infinite.
    vector<int> dist(V, INT_MAX);

    // initialize distance of source as 0
    dist[src] = 0;
 
    // Relax all edges (|V| - 1) times. A simple
    // shortest path from src to any other
    // vertex can have at-most (|V| - 1) edges
    for (int i = 0; i < V - 1; i++) 
    {
        for (vector<int> &edge : edges) 
        {
            int u = edge[0], v = edge[1], w = edge[2];

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
 
    // check for negative-weight cycles.
    // The above step guarantees shortest distances if graph doesn't
    // contain a negative weight cycle.  
    // If we get a shorter path, then there is a cycle.
    for (vector<int>&edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];

        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            cout << "Graph contains negative weight cycle" << endl;
    }
 
    cout << "Vertex Distance from Source " << src << endl;
    for (int v = 0; v < V; v++)
        cout << v << "\t\t" << dist[v] << endl;
}

int main()
{
    vector<vector<int>> edges = {   {0, 1, -1}, {0, 2, 4}, {1, 2, 3},
                                    {1, 3, 2}, {1, 4, 2}, {3, 2, 5},
                                    {3, 1, 1}, {4, 3, -3}
                                };
    
    bellman_ford_shortest_path(edges, 5, 0);
    return 0;
}

/*
Output:
Vertex Distance from Source 0
0               0
1               -1
2               2
3               -2
4               1
*/