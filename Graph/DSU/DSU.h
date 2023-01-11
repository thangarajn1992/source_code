#ifndef DSU_H
#define DSU_H
/*  Class for Disjoint Set Union or Union Find */
/*  We use path compression in Find operation and Union by Rank in Union Operation */

class DSU {
    int* parent;
    int* rank;
public:
    // constructor for data struct union/disjoint set
    DSU(int object_count);

    // Find function - Returns the representative of the component this object 
    // belongs to. This also does path compression along the way for the nodes
    // while traversing to the representative.
    int find(int object);


    // Unite Function - Unites two objects if they are part of same component.
    // Union by Rank is done here to avoid components from going to lengthy list
    // We merge component with lower rank with the component with higher rank
    void unite(int obj1, int obj2);
};
#endif /* DSU_H */