#include "maze.hpp"
#include <iostream>
#include <string.h>

Maze::Maze(int width, int height) : graph(width * height){
    this->width = width;
    this->height = height;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int currentCell = i*width + j;
            
            int rightCell = i*width + (j+1);
            if(j == width-1)
                rightCell = -1;
            
            int belowCell = (i+1)*width + j;
            if(i == height-1)
                belowCell = -1;
            
            if(rightCell != -1){
                int weight = rand();
                graph.addEdge(currentCell, rightCell, weight, false);
            }

            if(belowCell != -1){
                int weight = rand();
                graph.addEdge(currentCell, belowCell, weight, false);
            }
        }
    }
}

std::vector<std::vector<char>> Maze::createCharMatrix(){
    int mazeArrWidth = (2*this->width)+1;
    int mazeArrHeight = (2*this->height)+1;
    
    std::vector<std::vector<char>> matrix(mazeArrHeight, std::vector<char>(mazeArrWidth, '#'));

    for(int i = 0; i < this->graph.getSize(); i++){
        int row = (i/this->width)*2 + 1;
        int column = (i%this->width)*2 + 1;
        matrix[row][column] = ' ';

        for(auto child : this->graph.getChildren(i)){
            if(child.first == i+1)
                matrix[row][column+1] = ' ';
            else if(child.first == i+this->width)
                matrix[row+1][column] = ' ';
        }
    }

    return matrix;
}

void Maze::printASCII(){
    int mazeArrWidth = (2*this->width)+1;
    int mazeArrHeight = (2*this->height)+1;
    char mazeArr[mazeArrHeight][mazeArrWidth];
    memset(mazeArr, '#', sizeof(mazeArr));

    for(int i = 0; i < this->graph.getSize(); i++){
        int row = (i/this->width)*2 + 1;
        int column = (i%this->width)*2 + 1;
        mazeArr[row][column] = ' ';

        for(auto child : this->graph.getChildren(i)){
            if(child.first == i+1)
                mazeArr[row][column+1] = ' ';
            else if(child.first == i+this->width)
                mazeArr[row+1][column] = ' ';
        }
    }

    for(int i = 0; i < mazeArrHeight; i++){
        for(int j = 0; j < mazeArrWidth; j++){
            printf("%c", mazeArr[i][j]);
        }
        printf("\n");
    }
}

Maze GenerateRawMaze(int width, int height){
    Maze raw_maze(width, height);
    return raw_maze;
}

Maze GenerateMaze(int width, int height, const char *algorithm){
    Maze maze(width, height);

    if(strcmp(algorithm, "prim") == 0)
        maze.graph = maze.graph.GeneratePrimMST();
    else
        std::cout << "MAZE LIBRARY WARNING: No algorithm named \"" << algorithm << "\" found, raw maze returned" << std::endl;
    
    return maze;
}