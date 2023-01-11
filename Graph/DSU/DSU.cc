#include "DSU.h"

// constructor for data struct union/disjoint set
DSU::DSU(int object_count) {
    parent = new int[object_count];
    rank = new int[object_count];

    for(int object_num = 0; object_num < object_count; object_num++)
    {
        parent[object_num] = -1;
        rank[object_num] = 0;
    }
}

// Find function - Returns the representative of the component this object 
// belongs to. This also does path compression along the way for the nodes
// while traversing to the representative.
int
DSU::find(int object) {
    // this object is the representative of this component
    if(parent[object] == -1)
        return object;

    return parent[object] = find(parent[object]);
}

// Unite Function - Unites two objects if they are part of same component.
// Union by Rank is done here to avoid components from going to lengthy list
// We merge component with lower rank with the component with higher rank
void 
DSU::unite(int obj1, int obj2)
{
    int parent1 = find(obj1);
    int parent2 = find(obj2);

    if(parent1 != parent2) // if they are not part of same component
    {
        if(rank[parent1] < rank[parent2])
            parent[parent1] = parent2; // Merging parent1 to parent2
        else if(rank[parent2] < rank[parent1])
            parent[parent2] = parent1; // merging parent2 to parent1
        else 
        {
            // if both ranks are same, merge parent2 to parent1 and increase parent1 rank
            parent[parent2] = parent1;
            rank[parent1]++;
        }
    }
}


