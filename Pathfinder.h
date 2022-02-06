//
// Created by Isaac Hamm on 2/4/22.
//
#pragma once
#include "PathfinderInterface.h"
#include <vector>
#include <string>

using namespace std;

const int MAZE_SIZE = 5;

class Pathfinder: public PathfinderInterface {
private:
    int maze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
    vector<string> solution;

public:
    Pathfinder() {}
    ~Pathfinder() {}

    string toString();
    void createRandomMaze();
    bool importMaze(string file_name);
    vector<string> solveMaze();



};
