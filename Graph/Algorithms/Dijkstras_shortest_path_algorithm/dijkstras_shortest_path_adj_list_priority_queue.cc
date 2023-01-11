#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, int> iPair;

// Prints shortest paths from src to all other vertices
void dijkstra(vector<vector<iPair>> adj, int src)
{
    int V = adj.size(); // No. of vertices

    // Create a priority queue to store vertices that
    // are being preprocessed.
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
  
    // Create a vector for distances and initialize all
    // distances as INT_MAX
    vector<int> dist(V, INT_MAX);
  
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;
  
    /* Looping till priority queue becomes empty (or all
    distances are not finalized) */
    while (!pq.empty()) {
        // The first pair in queue is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();
  
        for (iPair &i : adj[u]) {
            // Get vertex label and weight of current
            // adjacent of u.
            int v = i.first;
            int w = i.second;
  
            // If there is a shorter path to v through u.
            if (dist[v] > dist[u] + w) {
                // Updating distance of v
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
  
    // Print shortest distances stored in dist[]
    printf("Vertex \tDistance from Source\n");
    for (int v = 0; v < V; v++)
        printf("%d \t\t %d\n", v, dist[v]);
}



int main()
{
    // adj[u] = {{v1, w1}, {v2, w2}};
    vector<vector<iPair>> adj = {   {{1, 4}, {7, 8}},
                                    {{0, 4}, {2, 8}, {7, 11}},
                                    {{1, 8}, {3, 7}, {5, 4}, {8, 2}},
                                    {{2, 7}, {4, 9}, {5, 14}},
                                    {{3, 9}, {5, 10}},
                                    {{2, 4}, {3, 14}, {4, 10}, {6, 2}},
                                    {{5, 2}, {7, 1}, {8, 6}},
                                    {{0, 8}, {1, 11}, {6, 1}, {8, 7}},
                                    {{2, 2}, {6, 6}, {7, 7}} 
                                };

    dijkstra(adj, 0);
    return 0;
}

/* Output:
Vertex  Distance from Source
0                0
1                4
2                12
3                19
4                21
5                11
6                9
7                8
8                14
*/