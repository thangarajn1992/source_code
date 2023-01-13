#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
    int V;    // No. of vertices
    vector<vector<int>> adj;    // An array of adjacency lists

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v's list.
    }
  
    // The main function that finds and prints strongly connected
    // components
    void printSCCs() {
        stack<int> St;
    
        // Mark all the vertices as not visited (For first DFS)
        vector<bool> visited(V, false);
    
        // Fill vertices in stack according to their finishing times
        for(int v = 0; v < V; v++)
            if(visited[v] == false)
                fillOrder(v, visited, St);
    
        // Create a reversed graph
        Graph gr = getTranspose();
    
        // Mark all the vertices as not visited (For second DFS)
        for(int v = 0; v < V; v++)
            visited[v] = false;
    
        // Now process all vertices in order defined by Stack
        while (St.empty() == false)
        {
            // Pop a vertex from stack
            int v = St.top(); St.pop();
    
            // Print Strongly connected component of the popped vertex
            // Note that we are using a transpose graph to do DFS here.
            if (visited[v] == false)
            {
                gr.DFSUtil(v, visited, true);
                cout << endl;
            }
        }   
    }

    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing 
    // time
    void fillOrder(int v, vector<bool>& visited, stack<int> &St) {
        // Mark the current node as visited and print it
        visited[v] = true;
    
        // Recur for all the vertices adjacent to this vertex
        for(int &neigh : adj[v])
            if(visited[neigh] == false)
                fillOrder(neigh, visited, St);
    
        // All vertices reachable from v are processed by now, push v 
        St.push(v); // Only difference between DFSUtil and fillOrder
    }
  
    // A recursive function to print DFS starting from v
    void DFSUtil(int v, vector<bool> &visited, bool print) {
        // Mark the current node as visited and print it
        visited[v] = true;
        if(print)
            cout << v << " ";
    
        // Recur for all the vertices adjacent to this vertex
        for(int &neigh : adj[v])
            if (visited[neigh] == false)
                DFSUtil(neigh, visited, print);
    }

    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose() {
        Graph g(V);
        for (int v = 0; v < V; v++)
        {
            // Recur for all the vertices adjacent to this vertex
            for(int &neigh : adj[v])
                g.adj[neigh].push_back(v);
        }
        return g;
    }

    // Function that does BFS traversal iteratively
    void BFSUtil(int v, vector<bool> &visited) {
        // Create a queue for BFS
        queue<int> q;
    
        // Mark the current node as visited and enqueue it
        visited[v] = true;
        q.push(v);
    
        while (q.empty() == false)
        {
            // Dequeue a vertex from queue
            v = q.front(); q.pop();
    
            // Get all adjacent vertices of the dequeued vertex v
            // If a adjacent has not been visited, then mark it
            // visited and enqueue it
            for (int &neigh : adj[v])
            {
                if (visited[neigh] == false)
                {
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }
    }

    // The main function that returns true if entire graph
    // is strongly connected
    // Logic: 
    //  Do DFS in graph and check whether all nodes are visited
    //  Do DFS in transpose graph and check whether all nodes are visited.
    bool isSC_using_DFS()
    {
        // Step 1: Mark all the vertices as not visited (For first DFS)
        vector<bool> visited(V,false);
    
        // Step 2: Do DFS traversal starting from the first vertex.
        DFSUtil(0, visited, false);
    
        // If DFS traversal doesn't visit all vertices, then return false.
        for (int v = 0; v < V; v++)
            if (visited[v] == false)
                return false;
    
        // Step 3: Create a reversed graph
        Graph gr = getTranspose();
    
        // Step 4: Mark all the vertices as not visited
        // (For second DFS)
        for(int v = 0; v < V; v++)
            visited[v] = false;
    
        // Step 5: Do DFS for reversed graph starting from
        // first vertex. Starting Vertex must be same starting
        // point of first DFS
        gr.DFSUtil(0, visited, false);
    
        // If all vertices are not visited in second DFS, then
        // return false
        for (int v = 0; v < V; v++)
            if (visited[v] == false)
                return false;
    
        return true;
    }

    // Function that checks whether entire graph is a SCC using BFS
    // Logic: 
    //  Do BFS in graph and check whether all nodes are visited
    //  Do BFS in transpose graph and check whether all nodes are visited.
    bool isSC_using_BFS() {
        // Step 1: Mark all the vertices as not visited (For first BFS)
        vector<bool> visited(V,false);
    
        // Step 2: Do BFS traversal starting from the first vertex.
        BFSUtil(0, visited);
    
        // If BFS traversal doesn't visit all
        // vertices, then return false.
        for (int v = 0; v < V; v++)
            if (visited[v] == false)
                return false;
    
        // Step 3: Create a reversed graph
        Graph gr = getTranspose();
    
        // Step 4: Mark all the vertices as not
        // visited (For second BFS)
        for(int v = 0; v < V; v++)
            visited[v] = false;
    
        // Step 5: Do BFS for a reversed graph starting from the first vertex.
        // Starting Vertex must be same starting point of first BFS
        gr.BFSUtil(0, visited);
    
        // If all vertices are not visited in second BFS, then return false
        for (int v = 0; v < V; v++)
            if (visited[v] == false)
                return false;
    
        return true;
    }
};

int main()
{
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "Following are strongly connected components in given graph" << endl;
    g.printSCCs();
    cout << "Is Strongly Connected graph (DFS): ";
    g.isSC_using_DFS() ? cout << "Yes" : cout << "No";
    cout << endl;

    cout << "Is Strongly Connected graph (BFS): ";
    g.isSC_using_BFS() ? cout << "Yes" : cout << "No";
    cout << endl;    
    cout << endl;
    
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 0);
    g1.addEdge(2, 4);
    g1.addEdge(4, 2);

    cout << "Following are strongly connected components in given graph" << endl;
    g1.printSCCs();
    cout << "Is Strongly Connected graph (DFS): ";
    g1.isSC_using_DFS() ? cout << "Yes" : cout << "No";
    cout << endl;

    cout << "Is Strongly Connected graph (BFS): ";
    g1.isSC_using_BFS() ? cout << "Yes" : cout << "No";
    cout << endl;

    return 0;
}
  

