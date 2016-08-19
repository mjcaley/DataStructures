#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector<DisjointSetsElement> sets;
    
    DisjointSets(int size): size(size), max_table_size(0), sets(size)
    {
        for (int i = 0; i < size; i++)
        {
            sets[i].parent = i;
        }
        recalculate_max_table_size();
    }
    
    void recalculate_max_table_size()
    {
        auto result = std::max_element(sets.begin(),
                                       sets.end(),
                                       [](const DisjointSetsElement& left, const DisjointSetsElement& right)
                                       {
                                           return left.size < right.size;
                                       });
        max_table_size = std::max(max_table_size, result->size);
    }
    
    int getParent(int table) {
        // find parent and compress path
        if (table != sets[table].parent)
        {
            sets[table].parent = getParent(sets[table].parent);
        }
        
        return sets[table].parent;
    }
    
    void merge(int destination, int source)
    {
        //cout << "merging destination: " << destination+1 << " and source: " << source+1 << endl;
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        //cout << "destination parent is " << realDestination+1 << " source parent is " << realSource+1 << endl;
        //cout << "destination size is " << sets[realDestination].size << " source size is " << sets[realSource].size << endl;
        if (realDestination != realSource)
        {
            if (sets[realDestination].size > sets[realSource].size)
            {
                sets[realSource].parent = realDestination;
                sets[realDestination].size += sets[realSource].size;
                sets[realSource].size = 0;
                max_table_size = max(max_table_size, sets[realDestination].size);
                //cout << "destination tree bigger than source tree " << sets[realDestination].size << ' ' << sets[realSource].size << endl;
            }
            else
            {
                sets[realDestination].parent = realSource;
                sets[realSource].size += sets[realDestination].size;
                sets[realDestination].size = 0;
                max_table_size = max(max_table_size, sets[realSource].size);
                //cout << "source tree bigger than destination tree " << sets[realSource].size << ' ' << sets[realDestination].size << endl;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }
    
    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;
        
        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }
    
    return 0;
}
