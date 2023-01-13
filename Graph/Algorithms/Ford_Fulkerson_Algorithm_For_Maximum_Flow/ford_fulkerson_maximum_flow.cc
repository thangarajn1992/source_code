// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* Returns true if there is a path from source 's' to sink
't' in residual graph. Also fills parent vector to store the path */
bool bfs(vector<vector<int>> &residual_adj, int s, int t, vector<int> &parent)
{
    int V = residual_adj.size();
	// Create a visited array and mark all vertices as not visited
	vector<bool> visited(V, false);

	queue<int> q;

	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	while (!q.empty()) {
		int u = q.front(); q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && residual_adj[u][v] > 0) {
				// If we find a connection to the sink node,
				// then there is no point in BFS anymore We
				// just have to set its parent and can return
				// true
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// We didn't reach sink in BFS starting from source, so
	// return false
	return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int>> &adj, int s, int t)
{
    int V = adj.size();
    int max_flow = 0; // There is no flow initially

    // This array is filled by BFS and to store path
	vector<int> parent(V); 

	// Create a residual graph and fill the residual graph
	// with given capacities in the original graph as
	// residual capacities in residual graph
    vector<vector<int>> residual_adj = adj;

	// Augment the flow while there is path from source to
	// sink
	while (bfs(residual_adj, s, t, parent)) {
		// Find minimum residual capacity of the edges along
		// the path filled by BFS. Or we can say find the
		// maximum flow through the path found.
		int path_flow = INT_MAX;
		for (int v = t; v != s; v = parent[v]) {
			path_flow = min(path_flow, residual_adj[parent[v]][v]);
		}

		// update residual capacities of the edges and
		// reverse edges along the path
		for (int v = t; v != s; v = parent[v]) {
			residual_adj[parent[v]][v] -= path_flow;
            // needed if we need to revert back some flow later
			residual_adj[v][parent[v]] += path_flow; 
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	// Return the overall flow
	return max_flow;
}

// Driver program to test above functions
int main()
{
	// Let us create a graph shown in the above example
	vector<vector<int>> adj 
		= { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
			{ 0, 4, 0, 0, 14, 0 }, { 0, 0, 9, 0, 0, 20 },
			{ 0, 0, 0, 7, 0, 4 }, { 0, 0, 0, 0, 0, 0 } };

	cout << "The maximum possible flow is "
		<< fordFulkerson(adj, 0, 5);

	return 0;
}
/*
Output:
The maximum possible flow is 23
*/