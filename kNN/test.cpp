//test
#include<iostream>
#include<fstream>
#include"Graph.h"

int main()
{
    Graph graph;
    std::ifstream in_file("graph.csv");
    graph.Deserialize(in_file);
    graph.ComputeCell();
    in_file.close();
    //check

    { 
        auto it = graph.node.begin();
        for(size_t i=0; i < 10; ++i)
        {
            std::cout << *it << "\n";
            it++;
        }
    }

    {
        auto it = graph.cell.begin();
        for(size_t i=0; i < 10; ++i)
        {
            std::cout << *it << "\n";
            it++;
        }
    }

    return 0;
}