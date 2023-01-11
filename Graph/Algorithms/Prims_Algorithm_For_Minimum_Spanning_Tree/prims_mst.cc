#include <iostream>
#include <vector>

using namespace std;

int prims_minimum_spanning_tree_cost(int V, vector<vector<int>> &adj)
{
    vector<int> parent(V); // array to store MST
    vector<bool> mstSet(V, false); // array to track vertices added into MST.
    vector<int> key(V, INT_MAX); // key value used to pick minimum edge from the cut
    int mstsum = 0;

    // picking the first vertice and adding it to MST.
    parent[0] = -1;
    key[0] = 0;

    // At each step we pick one vertice to be added into the MST.
    for(int count = 0; count < V; count++)
    {
        // pick the vertice with lowest key value and add to MST
        int u, mini = INT_MAX;
        for(int index = 0; index < V; index++)
        {
            if(mstSet[index] == false && key[index] < mini)
            {
                mini = key[index];
                u = index;
            }
        }
        cout << "Picked min index " << u << endl;
        mstSet[u] = true;
        mstsum += key[u];
       
        // Now update the key for all its neighbors, 
        // if this is better way for them
        for(int v = 0; v < V; v++)
        {
            if(adj[u][v] > 0 && mstSet[v] == false &&
               key[v] > adj[u][v])
            {
                key[v] = adj[u][v];
                parent[v] = u;
            }
        }
    }

    //Printing MST 
    for(int v = 1; v < V; v++)
        cout << parent[v] << "-" << v << "\t" << adj[v][parent[v]] << endl;

    return mstsum;
}

int main()
{
    vector<vector<int>> adj = {   
                                    { 0, 2, 0, 6, 0 }, 
                                    { 2, 0, 3, 8, 5 }, 
                                    { 0, 3, 0, 0, 7 }, 
                                    { 6, 8, 0, 0, 9 }, 
                                    { 0, 5, 7, 9, 0 } 
                                };
    int prims_mst = prims_minimum_spanning_tree_cost(5, adj);
    cout << "Minimum Spanning Tree cost Using Prim's Algorithm: " << prims_mst << endl;
    return 0;
}