// Online C++ compiler to run C++ program online
// A C++ program to find strongly connected components in a
// given directed graph using Tarjan's algorithm (single
// DFS)
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// A class that represents an directed graph
class Graph {
	int V; // No. of vertices
	vector<vector<int>> adj; // A dynamic array of adjacency lists

 	/*	
	A recursive function that finds and prints strongly
	connected components using DFS traversal 
	u 		--> The vertex to be visited next 
	disc 	--> Stores discovery times of visited vertices 
	low  	--> earliest visited vertex (the vertex with minimum
			   	discovery time) that can be reached from
			   	subtree rooted with current vertex
	*st 	--> To store all the connected ancestors (could be part of SCC)
	stackMember --> bit/index array for faster check whether a node is in stack
	*/
	void SCCUtil(int u, vector<int> &disc, vector<int> &low,
				stack<int> &st, vector<bool> &stackMember) {
		// A static variable is used for simplicity, we can
		// avoid use of static variable by passing a pointer.
		static int time = 0;
		
		// Initialize discovery time and low value
		disc[u] = low[u] = ++time;
		st.push(u);
		stackMember[u] = true;

		for(int &v : adj[u]) {
			// If v is not visited yet, then recur for it
			if (disc[v] == -1) {
				SCCUtil(v, disc, low, st, stackMember);
				// Check if the subtree rooted with 'v' has a
				// connection to one of the ancestors of 'u'
				low[u] = min(low[u], low[v]);
			}

			// Update low value of 'u' only of 'v' is still in
			// stack (i.e. it's a back edge, not cross edge).
			else if (stackMember[v] == true)
			{
				low[u] = min(low[u], disc[v]);
			}
		}

		// head node found, pop the stack and print an SCC		
		if (low[u] == disc[u]) {
			int w = 0; // To store stack extracted vertices
			while (st.top() != u) {
				w = (int)st.top();
				cout << w << " ";
				stackMember[w] = false;
				st.pop();
			}
			w = (int)st.top();
			cout << w << "\n";
			stackMember[w] = false;
			st.pop();
		}		
	}

public:
	// Constructor
	Graph(int V) {
		this->V = V;
		adj.resize(V);		
	}

	// function to add an edge to graph
	void addEdge(int v, int w) {
		adj[v].push_back(w);
	}

	// prints strongly connected components
	void SCC() {
		vector<int> disc(V, -1);
		vector<int> low(V, -1);
		vector<bool> stackMember(V, false);
		stack<int> st;

		// Call the recursive helper function to find strongly
		// connected components in DFS tree with vertex 'i'
		for (int i = 0; i < V; i++)
			if (disc[i] == -1)
				SCCUtil(i, disc, low, st, stackMember);		
	}
};

// Driver program to test above function
int main()
{
	cout << "\nSCCs in first graph \n";
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
	g1.SCC();

	cout << "\nSCCs in second graph \n";
	Graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.SCC();

	cout << "\nSCCs in third graph \n";
	Graph g3(7);
	g3.addEdge(0, 1);
	g3.addEdge(1, 2);
	g3.addEdge(2, 0);
	g3.addEdge(1, 3);
	g3.addEdge(1, 4);
	g3.addEdge(1, 6);
	g3.addEdge(3, 5);
	g3.addEdge(4, 5);
	g3.SCC();

	cout << "\nSCCs in fourth graph \n";
	Graph g4(11);
	g4.addEdge(0, 1);
	g4.addEdge(0, 3);
	g4.addEdge(1, 2);
	g4.addEdge(1, 4);
	g4.addEdge(2, 0);
	g4.addEdge(2, 6);
	g4.addEdge(3, 2);
	g4.addEdge(4, 5);
	g4.addEdge(4, 6);
	g4.addEdge(5, 6);
	g4.addEdge(5, 7);
	g4.addEdge(5, 8);
	g4.addEdge(5, 9);
	g4.addEdge(6, 4);
	g4.addEdge(7, 9);
	g4.addEdge(8, 9);
	g4.addEdge(9, 8);
	g4.SCC();
    
	cout << "\nSCCs in fifth graph \n";
	Graph g5(5);
	g5.addEdge(0, 1);
	g5.addEdge(1, 2);
	g5.addEdge(2, 3);
	g5.addEdge(2, 4);
	g5.addEdge(3, 0);
	g5.addEdge(4, 2);
	g5.SCC();
    
    cout << "\nSCCs in sixth graph \n";
    Graph g6(10);
    g6.addEdge(0,1);
    g6.addEdge(1,2);
    g6.addEdge(2,3);
    g6.addEdge(2,0);
    g6.addEdge(3,0);
    g6.addEdge(2,4);
    g6.addEdge(4,5);
    g6.addEdge(5,6);
    g6.addEdge(6,2);
    g6.addEdge(6,4);
    g6.addEdge(5,7);
    g6.addEdge(7,8);
    g6.addEdge(8,9);
    g6.addEdge(8,5);
    g6.addEdge(9,5);
    g6.SCC();
       
	return 0;
}