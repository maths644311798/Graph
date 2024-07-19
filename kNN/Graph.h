//Graph.h
#include<fstream>
#include<vector>
#include<array>
#include<set>

//k nearest neighbor, n * n cells
class Graph
{
    public:

    struct Node
    {
        public:
        //longitude, latitude
        float x, y;
    };

    
    class CompareNode
    {
    public:
        bool operator( )(const Node& p1, const Node& p2)
        {
            return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
        }
    };

    struct Cell
    {
        public:
        Node left_down_corner, right_up_corner;
        std::set<Node, CompareNode> in_cell_node;
        std::set<Node, CompareNode> k_nearest_node;
    };

    size_t k, n;
    Node left_down_corner, right_up_corner;
    std::set<Node, CompareNode> node;
    std::vector<Cell> cell;

    Graph(size_t o_k, size_t o_n, Node o_left_down_corner, Node o_right_up_corner);

    void Serialize(std::ofstream of);

};

std::ostream &operator<<(std::ostream &os, typename Graph::Node &o_node);
std::ostream &operator<<(std::ostream &os, typename Graph::Cell &o_cell);
