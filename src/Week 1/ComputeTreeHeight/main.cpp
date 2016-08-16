#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


struct Node
{
    Node(int id) : id(id) {};
    int id;
    std::vector<Node*> children;
};

class TreeHeight
{
    
    int n;
    Node* root;
    
    void delete_tree(Node* node)
    {
        if (node->children.empty())
        {
            return;
        }
        else
        {
            for (auto& child : node->children)
            {
                delete_tree(child);
                delete child;
                child = nullptr;
            }
        }
    }
    
public:
    ~TreeHeight()
    {
        delete_tree(root);
        delete root;
        root = nullptr;
    }
    
    void read() {
        std::cin >> n;
        
        std::vector<Node*> leaves(n);
        int id { 0 };
        std::generate(leaves.begin(), leaves.end(), [&id](){ return new Node(id++); });
        
        for (int i = 0; i < n; i++)
        {
            int p;
            std::cin >> p;
            
            if (p == -1)
            {
                root = leaves[i];
            }
            else
            {
                leaves[p]->children.emplace_back(leaves[i]);
            }
        }
    }
    
    int height()
    {
        return height(root);
    }
    
    int height(Node* node)
    {
        if (node->children.empty())
        {
            return 1;
        }
        else
        {
            int h { 0 };
            for (auto& child : node->children)
            {
                h = std::max(h, height(child));
            }
            return 1 + h;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    TreeHeight tree;
    tree.read();
    std::cout << tree.height() << std::endl;
}
