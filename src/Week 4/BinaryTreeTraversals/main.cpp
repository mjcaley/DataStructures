#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;


class TreeOrders {
    int n;
    vector <int> key;
    vector <int> left;
    vector <int> right;
    
public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }
    
    void traverse_in_order(int node, vector<int>& result)
    {
        if (node == -1)
        {
            return;
        }
        traverse_in_order(left[node], result);
        result.emplace_back(key[node]);
        traverse_in_order(right[node], result);
    }
    
    vector <int> in_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        traverse_in_order(0, result);
        
        return result;
    }
    
    void traverse_pre_order(int node, vector<int>& result)
    {
        if (node == -1)
        {
            return;
        }
        result.emplace_back(key[node]);
        traverse_pre_order(left[node], result);
        traverse_pre_order(right[node], result);
    }
    
    vector <int> pre_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        traverse_pre_order(0, result);
        
        return result;
    }
    
    void traverse_post_order(int node, vector<int>& result)
    {
        if (node == -1)
        {
            return;
        }
        traverse_post_order(left[node], result);
        traverse_post_order(right[node], result);
        result.emplace_back(key[node]);
    }
    
    vector <int> post_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        traverse_post_order(0, result);
        
        return result;
    }
};

void print(vector <int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}
