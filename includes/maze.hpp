#pragma once

#include "graph.hpp"
#include <string>

class Maze {
public:
    int height, width;
    Graph graph;

    Maze(int width, int height);
    void printASCII();
    std::vector<std::vector<char>> createCharMatrix();
};

Maze GenerateRawMaze(int width, int height);
Maze GenerateMaze(int width, int height, const char *algorithm);