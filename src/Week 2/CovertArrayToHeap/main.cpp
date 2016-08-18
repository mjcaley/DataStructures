#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;
    
    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }
    
    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }
    
    int get_parent(int node_id)
    {
        return std::floor( (static_cast<float>(node_id) - 1) / 2);
    }
    
    int get_left_child(int node_id)
    {
        return 2 * node_id + 1;
    }
    
    int get_right_child(int node_id)
    {
        return 2 * node_id + 2;
    }
    
    void sift_down(int node_id)
    {
        auto max_node_id = node_id;
        
        auto l = get_left_child(node_id);
        if (l < data_.size() &&
            data_[l] < data_[max_node_id])
        {
            max_node_id = l;
        }
        
        auto r = get_right_child(node_id);
        if (r < data_.size() &&
            data_[r] < data_[max_node_id])
        {
            max_node_id = r;
        }
        
        if (node_id != max_node_id)
        {
            swaps_.emplace_back( make_pair(node_id, max_node_id) );
            swap(data_[node_id], data_[max_node_id]);
            sift_down(max_node_id);
        }
    }
    
    void build_heap()
    {
        int size = std::floor( (static_cast<float>(data_.size()) - 1) / 2 );
        for (int i { static_cast<int>(data_.size() - 1) };
             i >= 0;
             --i)
        {
            sift_down(i);
        }
    }
    
    void GenerateSwaps() {
        swaps_.clear();
        build_heap();
    }
    
public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
