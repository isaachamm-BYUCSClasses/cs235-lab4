//
// Created by Isaac Hamm on 2/4/22.
//
#ifndef LAB_4_PATHFINDER
#define LAB_4_PATHFINDER

#include "PathfinderInterface.h"
#include <vector>
#include <string>

using namespace std;

const int MAZE_SIZE = 5;

class Pathfinder: public PathfinderInterface {
private:

    int maze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
    vector<string> solution;

protected:
    const int OFF_PATH = 0;
    const int ON_PATH = 1;
    const int DEAD_END = 2;
    const int EXPLORED = 3;


public:
    Pathfinder();
    ~Pathfinder() {}

    string toString() const;
    void createRandomMaze();
    bool importMaze(string file_name);
    vector<string> solveMaze();

    bool FindMazePath(int array[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE], int x, int y, int z);

};

#endif