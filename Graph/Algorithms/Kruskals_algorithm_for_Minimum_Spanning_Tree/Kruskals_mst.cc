#include <iostream>
#include <vector>
#include "../../DSU/DSU.h"

using namespace std;

/* 
    Input: Number of vertices (V), vector of Edges in the form of {w, u, v}
    Output: Minimum Spanning Tree Cost
*/
int kruskals_minimum_spanning_tree_cost(int V, vector<vector<int>> &edges)
{
    // Created disjoint set union to merge nodes as and when needed without 
    // creating a loop
    DSU s(V);
    int ans = 0;
    
    // Kruskals uses greedy approach, by selecting the edges with least cost
    // without causing a loop. Until either all the edges are processed or nodes
    // are covered.

    // For weighted graph, edges are in format {w, u, v} representing the edge between
    // u and v has weight w
    sort(edges.begin(), edges.end());

    for(vector<int> &edge : edges)
    {
        int w = edge[0], u = edge[1], v = edge[2];

        if(s.find(u) != s.find(v)) // not part of same group (not causing cycle)
        {
            s.unite(u,v);
            ans += w; // adding this edge to be part of MST.
            cout << " United " << u << " <---> " << v << endl;
        }
    }
    return ans;
}

int main()
{
    vector<vector<int>> edges;
    edges.push_back({10, 0, 1});
    edges.push_back({15, 1, 3});
    edges.push_back({4, 2, 3});
    edges.push_back({6, 2, 0});
    edges.push_back({5, 0, 3});

    int mst_cost = kruskals_minimum_spanning_tree_cost(4, edges);
    cout << "Minimum Spanning Tree Cost Using Kruskal's MST Algorithm: " << mst_cost <<endl;

    return 0;
}