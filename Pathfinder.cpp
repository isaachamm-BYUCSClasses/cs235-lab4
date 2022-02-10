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
#include <algorithm>
#include <time.h>
#include "stdlib.h"

using namespace std;

//int CheckCoords(int array [MAZE_SIZE][MAZE_SIZE][MAZE_SIZE], int x, int y, int z);
//
//int FindMazePath(int maze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE], int x, int y, int z);

Pathfinder::Pathfinder() {
    for (int i = 0; i < MAZE_SIZE; ++i) {   //This is to generate a maze of all 1s if no maze is imported
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                maze[k][j][i] = 1;
            }
        }
    }
}

string Pathfinder::toString() const {
    stringstream generator; //stringstream that will take the input in to create the maze.
    vector<int> x;          //these vectors represent the coordinates
    vector<int> y;
    vector<int> z;
    int mazeGen[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
    string space = " ";
    string newLine = "\n";
    string map;


    if (maze [0][0][0] == 1) {
        for (int i = 0; i < MAZE_SIZE; ++i) {           //These loops are to turn the maze into a string
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    generator << maze[k][j][i] << space;
                }
                generator << newLine;
            }
            if (i < MAZE_SIZE - 1) {
                generator << newLine;
            }
        }
        map = generator.str();
    }
    else {
        for (int i = 0; i < MAZE_SIZE; ++i) {   //This is to generate a maze of all 1s if no maze is imported
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    mazeGen[k][j][i] = 1;
                }
            }
        }

        for (int i = 0; i < MAZE_SIZE; ++i) {           //These loops are to turn the maze into a string
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    generator << mazeGen[k][j][i] << space;
                }
                generator << newLine;
            }
            if (i < MAZE_SIZE - 1) {
                generator << newLine;
            }
        }
        map = generator.str();
    }
    //cout << map << endl;    <- This is to help test

    return map;
}

void Pathfinder::createRandomMaze() {

    srand(time(0));

    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                srand(time(0));
                maze[k][j][i] = rand() % 2;
            }
        }
    }
    maze[0][0][0] = 1;
    maze[MAZE_SIZE - 1][MAZE_SIZE - 1][MAZE_SIZE -1] = 1;

    solveMaze();

}

bool Pathfinder::importMaze(string file_name) {

    solution.clear();
    stringstream stringToNumber;
    string line;
    int counter = 0;

    ifstream ifs(file_name);
    if (ifs.is_open()) {
        while (!ifs.eof()) {
//            ifs >> line;
//            ifs >> mazeNum;
            getline(ifs, line);
            stringToNumber << line << endl;
            counter ++;
        }
        ifs.close();
    }
    if (counter != 29) {         //checks the size of the maze
//        maze[0][0][0] = 4;
        return false;
    }


    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                stringToNumber >> maze[k][j][i];    //this SHOULD parse each number into the maze array.
                if (maze[k][j][i] == 0 || maze[k][j][i] == 1) {   //this is to make sure that the maze is valid based on number of things
                    continue;
                } else {
//                    maze[0][0][0] = 4;
                    return false;
                }
            }
        }
    }
    if (maze[0][0][0] == 1 &&
        maze[MAZE_SIZE - 1][MAZE_SIZE - 1][MAZE_SIZE - 1] == 1) {  //checks that the maze starts and ends with 1
        return true;
    } else {
//        maze[0][0][0] = 4;
        return false;
    }
}


vector<string> Pathfinder::solveMaze() {
    int mazeCopy[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];

    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                mazeCopy[k][j][i] = maze[k][j][i];
                }
            }
        }

    if (FindMazePath(mazeCopy, 0, 0, 0)) {
        reverse(solution.begin(), solution.end());
        return solution;
    }
    else {
        solution.clear();
        return solution;
    }
}

bool Pathfinder::FindMazePath(int maze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE], int x, int y, int z) {
//    cout << "Find Maze Path @ [" << x << "] [" << y << "] [" << z << "]" << endl;
//    cout << this->maze[x][y][z] << endl;

    if (x > (MAZE_SIZE - 1) || y > (MAZE_SIZE - 1) ||      // Out of bounds
        z > (MAZE_SIZE - 1) || x < 0 || y < 0 || z < 0) {
        return false;
    }
    else if (maze [x][y][z] != 1) {                         // Wrong path (0s)
        return false;
    }
    else if (x == (MAZE_SIZE - 1) && y == (MAZE_SIZE - 1) && z == (MAZE_SIZE - 1)) {    //Base case - at 4,4,4
        maze [x][y][z] = EXPLORED;
        stringstream solutionString;
        solutionString << "(" << x << ", " << y << ", " << z << ")";
        solution.push_back(solutionString.str());
//        cout << "YAY" << endl;
        return true;
    }
    else {
        maze [x][y][z] = EXPLORED;

        if (FindMazePath(maze, (x + 1), y, z) ||
            FindMazePath(maze, (x - 1), y, z) ||
            FindMazePath(maze, x, (y + 1), z) ||
            FindMazePath(maze, x, (y - 1), z) ||
            FindMazePath(maze, x, y, (z + 1)) ||
            FindMazePath(maze, x, y, (z - 1))) {
            stringstream solutionString;
            solutionString << "(" << x << ", " << y << ", " << z << ")";
            solution.push_back(solutionString.str());
            return true;
        }
        else {
            maze[x][y][z] = DEAD_END;
        }
        return false;
    }

}




//
//    if (maze[0][0][0] == 2) {
//        solution.push_back("false maze\n");
//        return solution;
//    }
//
//    int x = 0;
//    int y = 0;
//    int z = 0;
//    string nextStep;
//
//    if (solution.empty()) {
//        solution.push_back("(0, 0, 0)");
//    }
////        nextStep = solution.end();
//
//    vector<int> storeNum;
//    for (int i = 0; i < nextStep.size(); ++i) {          //parses the ints from the string
//        if (isdigit(nextStep.at(i))) {
//            int coordinate = (nextStep.at(i) - '0');    //turns the char from the string into an int
//            storeNum.push_back(coordinate);
//        }
//    }
//
////    x = storeNum.at(0);         //assigns the coordinate values
////    y = storeNum.at(1);
////    z = storeNum.at(2);
//
//    int checker; //used to return info from the function checkNextSpot
//
//    if (x + 1 < MAZE_SIZE) {
//        checker = CheckCoords(maze, (x + 1), y, z);
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            x += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            x += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//    if (x - 1 >= 0) {
//        checker = CheckCoords(maze, (x - 1), y, z);
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            x -= 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            x -= 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//    if (y + 1 < MAZE_SIZE) {
//        checker = CheckCoords(maze, x, (y + 1), z);
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            y += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            y += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//    if (y - 1 >= 0) {
//        checker = CheckCoords(maze, x, (y - 1), z);
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            y -= 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            y -= 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//    if (z + 1 < MAZE_SIZE) {
//        checker = CheckCoords(maze, x, y, (z + 1));
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            z += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            z += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//    if (z - 1 >= 0) {
//        checker = CheckCoords(maze, x, y, (z - 1));
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            z -= 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            z -= 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//    if (x + 1 < MAZE_SIZE) {
//        checker = CheckCoords(maze, (x + 1), y, z);
//        if (checker == 0) {
//            maze[x][y][z] = 2;
//            x += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        if (checker == 1) {
//            maze[x][y][z] = 2;
//            x += 1;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//}

//    Turning into a function
//    if (maze[x][y][z] == 1) {
//        if (x == (MAZE_SIZE - 1) && y == (MAZE_SIZE - 1) && z == (MAZE_SIZE - 1)) {
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            return solution;
//        }
//        else {
//            maze[x][y][z] = 2;
//            stringstream solutionString;
//            solutionString << "(" << x << ", " << y << ", " << z << ")";
//            nextStep = solutionString.str();
//            solution.push_back(nextStep);
//            solveMaze();
//        }
//
//    }
//
//
//}




//
//int CheckCoords(int array[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE], int x, int y, int z) {
//
//    if (array[x][y][z] == 1) {
//        if (x == (MAZE_SIZE - 1) && y == (MAZE_SIZE - 1) && z == (MAZE_SIZE - 1)) {
//            return 0;
//        }
//        else {
//            return 1;
//        }
//    }
// Don't need this because the check occurs in the upper function now
//    if (x < 0 || y < 0 || z < 0 ||              //checks for invalid values (outside of maze)
//            x > MAZE_SIZE || y > MAZE_SIZE || z > MAZE_SIZE) {
//        return 2;
//    }
