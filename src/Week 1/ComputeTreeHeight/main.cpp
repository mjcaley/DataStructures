#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>



struct Node
{
    Node(int id) : id(id) {};
    int id;
    std::vector< std::unique_ptr<Node> > children;
};
using uNode = std::unique_ptr<Node>;

class TreeHeight
{
    
    int n;
    uNode root;
    
public:
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
                root = uNode(leaves[i]);
            }
            else
            {
                leaves[p]->children.emplace_back( uNode(leaves[i]) );
            }
        }
    }
    
    int height()
    {
        return height(*root);
    }
    
    int height(Node& node)
    {
        if (node.children.empty())
        {
            return 1;
        }
        else
        {
            int h { 0 };
            for (auto& child : node.children)
            {
                h = std::max(h, height(*child));
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
