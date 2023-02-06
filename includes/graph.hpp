#pragma once

#include <vector>
#include <list>

class Graph {
private:
    std::vector<std::list<std::pair<int,int>>> adjacency;
    int size;
public:
    Graph(int vertex_ammount);
    
    void addEdge(int source, int dest, int weight, bool is_directed);
    
    std::list<std::pair<int,int>> getChildren(int vertex);
    int getSize();

    Graph GeneratePrimMST();
    
    void print();
};
