#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze maze;
    maze.makeMaze(3, 3);
    vector<int> solution = maze.solveMaze();
    // for(auto it = solution.begin(); it != solution.end(); it++){
    //     std::cout<<*it<<std::endl;
    // }
    PNG * actualOutput = maze.drawMazeWithSolution();
    actualOutput->writeToFile("test" + string(".png"));
    return 0;
}
