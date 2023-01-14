// C++ Program for Floyd Warshall Algorithm
#include <iostream>
#include <vector>

using namespace std;

/* A utility function to print solution */
void printSolution(vector<vector<int>> &dist)
{
    int V = dist.size();

	cout << "The following matrix shows the shortest "
			"distances between every pair of vertices \n";

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INT_MAX)
				cout << "NR" << " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << endl;
	}
}

// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall(vector<vector<int>> &dist)
{
    int V = dist.size();
	/* 
    Add all vertices one by one to the set of intermediate vertices.

	---> Before start of an iteration, we have shortest 
    distances between all pairs of vertices such that the
	shortest distances consider only the
	vertices in set {0, 1, 2, .. k-1} as
	intermediate vertices.

	----> After the end of an iteration,
	vertex no. k is added to the set of
	intermediate vertices and the set becomes {0, 1, 2, ..
	k} 
    */
	for (int k = 0; k < V; k++) {
		// Pick all vertices as source one by one
		for (int i = 0; i < V; i++) {
			// Pick all vertices as destination for the
			// above picked source
			for (int j = 0; j < V; j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of dist[i][j]
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && 
                    dist[i][j] > (dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
                }
			}
		}
	}

	// Print the shortest distance matrix
	printSolution(dist);
}

/*
Output:
The following matrix shows the shortest distances between every pair of vertices 
0 5 8 9 
NR 0 3 4 
NR NR 0 1 
NR NR NR 0 
*/



int main()
{
	vector<vector<int>> adj = { { 0, 5, INT_MAX, 10 },
						        { INT_MAX, 0, 3, INT_MAX },
						        { INT_MAX, INT_MAX, 0, 1 },
						        { INT_MAX, INT_MAX, INT_MAX, 0 } 
                              };

	floydWarshall(adj);
	return 0;
}