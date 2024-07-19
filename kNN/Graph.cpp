//Graph.cpp
#include "Graph.h"

Graph::Graph(size_t o_k, size_t o_n, Node o_left_down_corner, Node o_right_up_corner)
: k(o_k), n(o_n), left_down_corner(o_left_down_corner), right_up_corner(o_right_up_corner)
{

}

std::ostream &operator<<(std::ostream &os, const Graph::Node &o_node)
{
    os << o_node.x << "," << o_node.y;
}

std::ostream &operator<<(std::ostream &os, const Graph::Cell &o_cell)
{
    os << o_cell.left_down_corner << "\n";
    os << o_cell.right_up_corner;
    //The inside nodes and k nearest nodes are computed and are not stored in files.
}


void Graph::Serialize(std::ofstream of)
{
    of << k << "," << n << "\n";
    of << left_down_corner << "\n";
    of << right_up_corner << "\n";
    for(auto &o_node : node)
    {
        of << o_node << "\n";
    }
    for(auto &o_cell : cell)
    {
        of << o_cell << "\n";
    }
}

