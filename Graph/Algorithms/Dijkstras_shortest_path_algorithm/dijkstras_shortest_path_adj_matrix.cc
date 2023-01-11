#include <iostream>
#include <vector>

using namespace std;

int NO_PARENT = -1;

// Function to print shortest path from source to currentVertex
// using parents array
void printPath(int currentVertex, vector<int> parents)
{
    // Base case : Source node has been processed
    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << currentVertex << " ";
}

// Function that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix representation
void dijkstra(vector<vector<int>> adj, int src)
{
    int V = adj[0].size();
 
    // dist[i] will hold the shortest distance from src to i.
    // Initialize all distances as INT_MAX
    vector<int> dist(V, INT_MAX);
 
    // added[i] will be true if vertex i is included in shortest path tree
    // or shortest distance from src to i is finalized.
    // Initialize all added[] as false
    vector<bool> added(V, false);
 
    // Parent array to store shortest path tree
    vector<int> parents(V);

    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // The starting vertex does not have a parent
    parents[src] = NO_PARENT;
 
    // Find shortest path for all vertices
    for (int v = 1; v < V; v++) 
    {
        // Pick the minimum distance vertex from the set of vertices 
        // not yet processed. nearestVertex is always equal to startNode 
        // in the first iteration.
        int u = -1;
        int mindist = INT_MAX;
        for (int index = 0; index < V; index++) 
        {
            if (added[index] == false && dist[index] < mindist) 
            {
                u = index;
                mindist = dist[index];
            }
        }
 
        // Mark the selected vertex as processed
        added[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // selected vertex.
        for (int index = 0; index < V; index++) 
        {
            if(adj[u][index] > 0 && dist[index] > dist[u] + adj[u][index])
            {
                parents[index] = u;
                dist[index] = dist[u] + adj[u][index];
            }
        }
    }

    // Print the shortest path for each vertex
    for(int index = 0; index < V; index++)
    {
        if(index != src)
        {
            cout << "\n" << src << " -> " << index << "\t\t";
            cout << dist[index] << "\t\t";
            printPath(index, parents);
        }
    }
}

int main()
{
    vector<vector<int>> adj = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                                { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                                { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                                { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                                { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                                { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                                { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                                { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                                { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstra(adj, 0);
    return 0;
}

/* Output:
0 -> 1          4               0 1 
0 -> 2          12              0 1 2 
0 -> 3          19              0 1 2 3 
0 -> 4          21              0 7 6 5 4 
0 -> 5          11              0 7 6 5 
0 -> 6          9               0 7 6 
0 -> 7          8               0 7 
0 -> 8          14              0 1 2 8
*/