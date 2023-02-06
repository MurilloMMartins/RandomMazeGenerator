#include "graph.hpp"
#include <iostream>
#include <limits>
#include <queue>

Graph::Graph(int vertex_ammount){
    this->adjacency.resize(vertex_ammount);
    this->size = vertex_ammount;
}

void Graph::addEdge(int source, int dest, int weight, bool is_directed){
    if(source > this->size or dest > this->size)
        return;

    this->adjacency[source].push_back(std::make_pair(dest, weight));
    if(!is_directed)
        this->adjacency[dest].push_back(std::make_pair(source, weight));
}

std::list<std::pair<int,int>> Graph::getChildren(int vertex){
    return adjacency[vertex];
}

int Graph::getSize(){
    return this->size;
}

Graph Graph::GeneratePrimMST(){
    Graph MST(size);

    std::priority_queue<std::pair<int,int>, 
                        std::vector<std::pair<int,int>>,
                        std::greater<std::pair<int,int>>> min_weight;
    std::vector<int> key(size, INT32_MAX);
    std::vector<int> parent(size, -1);
    std::vector<bool> visited(size, false);

    min_weight.push(std::make_pair(0, 0));
    key[0] = 0;

    while(!min_weight.empty()){
        int minIndex = min_weight.top().second;
        min_weight.pop();

        if(visited[minIndex] == true)
            continue;

        visited[minIndex] = true;
        for(std::pair<int,int> i : adjacency[minIndex]){
            int vertex = i.first;
            int weight = i.second;

            if(visited[vertex] == false and key[vertex] > weight){
                key[vertex] = weight;
                min_weight.push(std::make_pair(weight, vertex));
                parent[vertex] = minIndex;
            }
        }
    }

    for(int i = 1; i < size; i++)
        MST.addEdge(i, parent[i], key[i], false);

    return MST;
}

void Graph::print(){
    for(int i = 0; i < this->size; i++){
        std::cout << i << ": ";
        for(std::pair<int,int> j : this->adjacency[i]){
            std::cout << j.first << "(" << j.second << ")-> ";
        }
        std::cout << std::endl;
    }
}