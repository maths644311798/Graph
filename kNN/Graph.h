//Graph.h
#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <cmath>
#include <numbers>
#include <iomanip>


//k nearest neighbor, n * n cells
class Graph
{
    public:

    struct Node
    {
        public:
        //longitude, latitude
        double x, y;
    };

    
    class CompareNode
    {
    public:
        bool operator()(const Node& p1, const Node& p2) const
        {
            return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
        }
    };

    struct Cell
    {
        public:
        Node left_down_corner, right_up_corner;
        std::vector<const Node*> in_cell_node;
        std::set<Node, CompareNode> k_nearest_node;

        Cell(){};

        Cell(const Node &ld_c, const Node &ru_c)
        :left_down_corner(ld_c), right_up_corner(ru_c)
        {}
    };

    size_t k, n;
    Node left_down_corner, right_up_corner;
    std::set<Node, CompareNode> node;
    std::vector<Cell> cell;

    Graph(){}

    Graph(size_t o_k, size_t o_n)
    :k(o_k), n(o_n)
    {}

    Graph(size_t o_k, size_t o_n, Node o_left_down_corner, Node o_right_up_corner);

    inline static double DistanceSquare(const Node &p, const Node &q)
    {
        return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
    }

    inline static double Distance(const Node &p, const Node &q)
    {
        return std::sqrt(Distance(p, q));
    }


    void ComputeCell();

    void Serialize(std::ostream &of);
    void Deserialize(std::istream &input);

};

std::ostream &operator<<(std::ostream &os, const Graph::Node &o_node);
std::ostream &operator<<(std::ostream &os, const Graph::Cell &o_cell);

std::istream &operator>>(std::istream &is, Graph::Node &i_node);
std::istream &operator>>(std::istream &is, Graph::Cell &i_cell);