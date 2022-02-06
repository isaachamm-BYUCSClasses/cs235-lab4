//
// Created by Isaac Hamm on 2/4/22.
//

#include "Pathfinder.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>

using namespace std;

string Pathfinder::toString() {
    stringstream generator; //stringstream that will take the input in to create the maze.
    vector<int> x;          //these vectors represent the coordinates
    vector<int> y;
    vector<int> z;
    string space = " ";
    string newLine = "\n";


    if (maze[0][0][0] == 0) {
        for (int i = 0; i < MAZE_SIZE; ++i) {   //This is to generate a maze of all 1s if no maze is imported
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    maze[i][j][k] = 1;
                }
            }
        }
    }

    for (int i = 0; i < MAZE_SIZE; ++i) {           //These loops are to turn the maze into a string
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                generator << maze[i][j][k] << space;
            }
            generator << newLine;
        }
        generator << newLine;
    }
    string map = generator.str();
    //cout << map << endl;    <- This is to help test

    return map;
}

void Pathfinder::createRandomMaze() {
//  Pretty sure I don't need this –> int randomMaze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];

    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                maze[i][j][k] = rand() % 2;
            }
        }
    }
    maze[0][0][0] = 1;
    maze[MAZE_SIZE - 1][MAZE_SIZE - 1][MAZE_SIZE -1] = 1;
}

bool Pathfinder::importMaze(string file_name) {
    stringstream stringToNumber;
    string line;
    int mazeNum;

    ifstream ifs(file_name);
    if (ifs.is_open()) {
        while (!ifs.eof()) {
//            ifs >> line;
//            ifs >> mazeNum;
            getline(ifs, line);
            stringToNumber << line << endl;
        }
    }


    string check;
    int counter = 0;
    while (stringToNumber >> check) {
        if (check == "0" || check == "1") {
            counter ++;                     //this is to make sure that the maze is valid based on number of things
            continue;
        }
        else {
            return false;
        }
    }
    if (counter != pow(MAZE_SIZE, 3)) {         //checks the size of the maze
        return false;
    }

        for (int i = 0; i < MAZE_SIZE; ++i) {
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    stringToNumber >> maze[k][j][i];    //this SHOULD parse each number into the maze array.
                }
            }
        }
        if (maze[0][0][0] == 1 && maze[MAZE_SIZE - 1][MAZE_SIZE - 1][MAZE_SIZE - 1]) {  //checks that the maze starts and ends with 1
            return true;
        }
        else {
            return false;
        }

}

vector<string> Pathfinder::solveMaze() {
    int x = 0;
    int y = 0;
    int z = 0;
    string nextStep;

    stringstream parseValues;
    parseValues << solution.back();
    (parseValues >> x >> y >> z);

    if (maze[x][y][z] == 1) {
        if (x == (MAZE_SIZE - 1) && y == (MAZE_SIZE - 1) && z == (MAZE_SIZE - 1)) {
            stringstream solutionString;
            solutionString << "(" << x << ", " << y << ", " << z << ")";
            nextStep = solutionString.str();
            solution.insert(solution.begin(), nextStep);
            return solution;
        }
        else {
            stringstream solutionString;
            solutionString << "(" << x << ", " << y << ", " << z << ")";
            nextStep = solutionString.str();
            solution.push_back(nextStep);
        }
        if (maze[x][y][z] == 0) {
            solution.pop_back();    //TODO – I don't think this is right... BC it would take off the former value.
        }
    }


}