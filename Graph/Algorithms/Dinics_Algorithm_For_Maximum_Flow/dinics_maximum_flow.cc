// C++ implementation of Dinic's Algorithm
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Residual Graph
class Graph {
	int V; // number of vertex
	vector<int> level; // stores level of a node
	vector<vector<int>> adj;

public:
    // Constructor
	Graph(int V) {
        this->V = V;
		adj.resize(V);
        for(int i = 0; i < V; i++)
            adj[i].resize(V);
        level.resize(V);
	}

	// add edge to the graph
	void addEdge(int u, int v, int C) {
		adj[u][v] = C;
	}

    // Finds if more flow can be sent from s to t.
    // Also assigns levels to nodes.
	bool BFS(int s, int t) {
	    for (int i = 0; i < V; i++)
		    level[i] = -1;

	    level[s] = 0; // Level of source vertex

	    // Create a queue, enqueue source vertex
	    // and mark source vertex as visited here
	    // level[] array works as visited array also.
	    queue<int> q;
	    q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < adj[u].size(); v++) {
                if (level[v] == -1 && adj[u][v] > 0) {
                    // Level of current vertex is,
                    // level of parent + 1
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        }

        // IF we can not reach to the sink we
        // return false else true
        return level[t] != -1;
    }

    // A DFS based function to send flow after BFS has
    // figured out that there is a possible flow and
    // constructed levels. This function called multiple
    // times for a single call of BFS.
    // flow : Current flow send by parent function call
    // start[] : To keep track of next edge to be explored.
    //		 start[i] stores count of edges explored
    //		 from i across multiple DFS calls per BFS.
    // u : Current vertex
    // t : Sink
	int sendFlow(int u, int flow, int t, vector<int> &start) {
        // Sink reached
        if (u == t)
            return flow;
            
        // Traverse all adjacent edges one -by - one.
        for (; start[u] < adj[u].size(); start[u]++) {
            // Pick next edge from adjacency list of u
            int v = start[u];

            if (level[v] == level[u] + 1 && adj[u][v] > 0) {
                // find minimum flow from u to t
                int curr_flow = min(flow, adj[u][v]);

                int temp_flow = sendFlow(v, curr_flow, t, start);

                // flow is greater than zero
                if (temp_flow > 0) {
                    adj[u][v] -= temp_flow;
                    adj[v][u] += temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }

    // Returns maximum flow in graph
	int DinicMaxflow(int s, int t) {
        // Corner case
        if (s == t)
            return -1;

        int total = 0; // Initialize result

        // Augment the flow while there is path
        // from source to sink
        while (BFS(s, t) == true) {
            // store how many edges are visited
            // from V { 0 to V }
            vector<int> start(V+1, 0);

            // while flow is not zero in graph from S to D
            while (int flow = sendFlow(s, INT_MAX, t, start))
            {
                // Add path flow to overall flow
                total += flow;
            }
        }
        // return maximum flow
        return total;
    }
};

int main()
{
	Graph g(6);
	g.addEdge(0, 1, 16);
	g.addEdge(0, 2, 13);
	g.addEdge(1, 2, 10);
	g.addEdge(1, 3, 12);
	g.addEdge(2, 1, 4);
	g.addEdge(2, 4, 14);
	g.addEdge(3, 2, 9);
	g.addEdge(3, 5, 20);
	g.addEdge(4, 3, 7);
	g.addEdge(4, 5, 4);

    cout << "Maximum flow " << g.DinicMaxflow(0, 5) << endl;

	// next exmp
    Graph g1(6);
	g1.addEdge(0, 1, 3 );
	g1.addEdge(0, 2, 7 ) ;
	g1.addEdge(1, 3, 9);
	g1.addEdge(1, 4, 9 );
	g1.addEdge(2, 1, 9 );
	g1.addEdge(2, 4, 9);
	g1.addEdge(2, 5, 4);
	g1.addEdge(3, 5, 3);
	g1.addEdge(4, 5, 7 );
	g1.addEdge(0, 4, 10);

    cout << "Maximum flow " << g1.DinicMaxflow(0, 5) << endl;

	// next exp
    Graph g2(6);
	g2.addEdge(0, 1, 10);
	g2.addEdge(0, 2, 10);
	g2.addEdge(1, 3, 4 );
	g2.addEdge(1, 4, 8 );
	g2.addEdge(1, 2, 2 );
	g2.addEdge(2, 4, 9 );
	g2.addEdge(3, 5, 10 );
	g2.addEdge(4, 3, 6 );
	g2.addEdge(4, 5, 10 );

    cout << "Maximum flow " << g2.DinicMaxflow(0, 5) << endl;
	
	return 0;
}
/*
Output:
Maximum flow 23
Maximum flow 14
Maximum flow 19 
*/