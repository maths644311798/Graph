//Graph.cpp
#include<iostream>
#include "Graph.h"

Graph::Graph(size_t o_k, size_t o_n, Node o_left_down_corner, Node o_right_up_corner)
: k(o_k), n(o_n), left_down_corner(o_left_down_corner), right_up_corner(o_right_up_corner)
{
    cell.reserve(n * n);
}

std::ostream &operator<<(std::ostream &os, const Graph::Node &o_node)
{
    os << std::setprecision(12) << o_node.x << "," << o_node.y;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Graph::Cell &o_cell)
{
    os << o_cell.left_down_corner << "\n";
    os << o_cell.right_up_corner;
    //The inside nodes and k nearest nodes are computed and are not stored in files.
    return os;
}

std::istream &operator>>(std::istream &is, Graph::Node &i_node)
{
    char c, temp[200];
    //assume the format is longitude, latitude, name, comment
    is >> i_node.x >> c >> i_node.y;
    //Names and comments are abandoned
    is.getline(temp, 200, ',');
#ifdef DEBUG_INFO
    if(std::strlen(temp) > 190)
        std::cout << "Long name: " << temp << "\n";
#endif
    is.getline(temp, 200, '\n');
#ifdef DEBUG_INFO
    if(std::strlen(temp) > 190)
        std::cout << "Long comment: " << temp << "\n";
#endif
    return is;
}

std::istream &operator>>(std::istream &is, Graph::Cell &i_cell)
{
    char c;
    is >> i_cell.left_down_corner;
    c = is.get();
    if(c == '\r')
        c = is.get();
    is >> i_cell.right_up_corner;
    return is;
}

void Graph::ComputeCell()
{
    std::cout << "Computing Cell\n";
    size_t index = 0;
    cell.resize(0);
    double x_interval = (right_up_corner.x - left_down_corner.x) / n;
    double y_interval = (right_up_corner.y - left_down_corner.y) / n;
    for(size_t i = 0; i < n * n; ++i)
    {
        Node ld_c({(i / n) * x_interval + left_down_corner.x, (i % n) * y_interval + left_down_corner.y});
        Node ru_c({ld_c.x + x_interval, ld_c.y + y_interval});
        cell.emplace_back( ld_c, ru_c );
    }

    struct NodeWithCenter
    {
        public:
        const Node *p;
        const Node *Center;
    } node_with_center[node.size()];

    for(auto &p : node)
    {
        size_t cell_x = std::floor((p.x - left_down_corner.x) / x_interval);
        size_t cell_y = std::floor((p.y - left_down_corner.y) / y_interval);
        cell[cell_x * n + cell_y].in_cell_node.push_back(&p);
        node_with_center[index++].p = &p;
    }
    //find k nearest neighbor

    class CentralizedCompare
    {
        public:
        bool operator()(const NodeWithCenter& p1, const NodeWithCenter& p2) const
        {
            return DistanceSquare(*p1.p, *p1.Center) < DistanceSquare(*p2.p, *p2.Center);
        }
    };

    for(auto &one_cell : cell)
    {
        Node Center({(one_cell.left_down_corner.x + one_cell.right_up_corner.x) / 2,
                    (one_cell.left_down_corner.y + one_cell.right_up_corner.y) / 2});
        std::set<NodeWithCenter, CentralizedCompare> nearest_pointer;
        for(auto &p : node)
        {
            nearest_pointer.emplace(&p, &Center);
        }
        index = 0;
        for(auto it = nearest_pointer.cbegin(); index < k; ++index)
        {
            one_cell.k_nearest_node.emplace(*it->p);
        }
    }
}

void Graph::Serialize(std::ostream &of)
{
    of << k << "," << n << "\n";
    of << left_down_corner << "\n";
    of << right_up_corner << "\n";
    of << node.size() << "\n";
    for(auto &o_node : node)
    {
        of << o_node << "\n";
    }
}


void Graph::Deserialize(std::istream &input)
{
    char c;

    //test
    std::cout << "Deserializing\n";

    Node temp;
    input >> temp;
    node.emplace(temp);
#ifdef DEBUG_INFO
    std::cout << "First Node " << temp << "\n";
#endif
    left_down_corner = temp;
    right_up_corner = temp;

#ifdef DEBUG_INFO
    size_t counter = 1;
#endif

    while(!input.eof() && (input >> temp))
    {
        node.emplace(temp);
        left_down_corner.x = std::min(left_down_corner.x, temp.x);
        left_down_corner.y = std::min(left_down_corner.y, temp.y);
        right_up_corner.x = std::max(right_up_corner.x, temp.x);
        right_up_corner.y = std::max(right_up_corner.y, temp.y);
#ifdef DEBUG_INFO
        ++counter;
#endif
    }

#ifdef DEBUG_INFO
    std::cout << "counter = " << counter << "\n";
    std::cout << k << " " << n << "\n";
    std::cout << "left_down " << left_down_corner << "\n";
    std::cout << "right up " << right_up_corner << "\n";
    std::cout << "total node " <<  node.size() << '\n';
#endif
}