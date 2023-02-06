#include <iostream>
#include <fstream>
#include <string.h>
#include "graph.hpp"
#include "maze.hpp"

#define DEFAULT_MAZE_HEIGHT 20
#define DEFAULT_MAZE_WIDTH 20

Graph generate_maze_graph(int width, int height);

int main(int argc, char *argv[]){
    srand(time(NULL));

    int width = DEFAULT_MAZE_WIDTH;
    int height = DEFAULT_MAZE_HEIGHT;
    if(argc == 3){
        if(atoi(argv[1]) > 0 || atoi(argv[2]) > 0){
            width = atoi(argv[1]);
            height = atoi(argv[2]);
        }
    }
    std::cout << "Width: " << width << " Height: " << height << std::endl;
    
    Maze maze = GenerateMaze(width, height, "prim");
    std::vector<std::vector<char>> mat = maze.createCharMatrix();

    for(auto i : mat){
        for(auto j : i)
            std::cout << j;
        std::cout << std::endl;
    }

    int resize = 10;
    std::ofstream file("maze2.ppm", std::ios::out | std::ios::binary);
    file << "P6" << std::endl;
    file << resize*mat[0].size() << ' ' << resize*mat.size() << std::endl; 
    file << "255" << std::endl;
    
    for(std::vector<char> row : mat){
        for(int i = 0; i < resize; i++){
            for(char character : row){
                for(int j = 0; j < resize; j++){
                    if(character == '#')
                        file << (char) 255 << (char) 255 << (char) 255;
                    else if(character == ' ')
                        file << (char) 0 << (char) 0 << (char) 0;
                }
            }
        }
    }

    file.close();

    return 0;
}