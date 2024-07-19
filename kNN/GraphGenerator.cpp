//Generate a random graph
#include<fstream>
#include <ctime>
#include <random>
#include "Graph.h"

const size_t total_node = 20000;

void RandomGraph(Graph &graph)
{
    std::default_random_engine engine_x, engine_y;
    std::uniform_real_distribution<double> distribute_x(graph.left_down_corner.x, graph.right_up_corner.x);
    std::uniform_real_distribution<double> distribute_y(graph.left_down_corner.y, graph.right_up_corner.y);
    engine_x.seed(time(nullptr));
    engine_y.seed(time(nullptr) + 1);
    for(size_t i = 0; i < total_node; ++i)
    {
        graph.node.emplace(distribute_x(engine_x), distribute_y(engine_y));
    }
}

Graph graph(4, 90, {0, 0}, {1.5, 1.5});

int main()
{
    RandomGraph(graph);
    graph.ComputeCell();
    std::ofstream of("graph.csv");
    graph.Serialize(of);
    of.close();
    return 0;
}