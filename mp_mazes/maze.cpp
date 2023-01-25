/* Your code here! */
#include "maze.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>

SquareMaze::SquareMaze(){
    _maze = new vector<wall>;
    _dset = new DisjointSets();
    _width = 0;
    _height = 0;
}

SquareMaze::~SquareMaze(){
    destroy();
}

void SquareMaze::destroy(){
    delete _maze;
    delete _dset;
    _maze = NULL;
    _dset = NULL;
}

int myrandom(int i){
    return std::rand() % i;
}

void SquareMaze::makeMaze(int width, int height){
    delete _maze;
    delete _dset;
    _maze = new vector<wall>;
    _dset = new DisjointSets();
    
    _width = width;
    _height = height;
    _dset->addelements(width * height);
    vector<int> unvisited;
    for(int i = 0; i < width * height; i++){
        _maze->push_back(wall(true, true));
        unvisited.push_back(i);
    }
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    std::srand(tv.tv_usec);
    std::random_shuffle(unvisited.begin(), unvisited.end(),myrandom);
    while(!unvisited.empty()){
        int rand = unvisited[unvisited.size()-1];
        //std::cout<<rand<<std::endl;
        unvisited.pop_back();
        int x = rand % _width;
        int y = rand / _width;
        if(((rand + 1) % _width != 0) && (_dset->find(rand) != _dset->find(rand + 1))){
            //std::cout<<"right"<<std::endl;
            _dset->setunion(rand,rand + 1);
            setWall(x,y,0,false);
        }
        
        if((rand < (_width * (_height -1))) && (_dset->find(rand) != _dset->find(rand + _width))){
            //std::cout<<"down"<<std::endl;
            _dset->setunion(rand,rand+_width);
            setWall(x,y,1,false);
        }
        // std::cout<<"______"<<std::endl;
        // _dset->print();
        // std::cout<<"______"<<std::endl;
    }    
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    switch (dir)
    {
    case 0:
        if(x < _width - 1){
            return !(*_maze)[_width * y + x]._right;
        }
        break;
    case 1:
        if(y < _height - 1){
            return !(*_maze)[_width * y + x]._down;
        }
        break;
    case 2:
        if(x > 0 && x < _width){
            return !(*_maze)[_width * y + x - 1]._right;
        }
        break;
    case 3:
        if(y > 0 && y < _height){
            return !(*_maze)[_width * (y - 1) + x]._down;
        }
        break;
    default:
        return false;
    }

    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        (*_maze)[_width * y + x]._right = exists;
    }
    else if(dir == 1){
        (*_maze)[_width * y + x]._down = exists;
    }
}

vector<int> SquareMaze::solveMaze(){
    vector<int> solution;

    vector<int> curpath;
    vector<int> dist;
    vector<int> previous;
    vector<bool> visited;
    int maxdist = 0;
    int dest_x = 0;
    int dest_y = 0;

    for(int i = 0; i < _width * _height; i++){
        visited.push_back(false);
        previous.push_back(-1);
        dist.push_back(0);
    }
    curpath.push_back(0);
    visited[0] = true;

    while(!curpath.empty()){
        int curr = curpath.front();
        curpath.erase(curpath.begin());
        int x = curr % _width;
        int y = curr / _width;
        
        if(y == _height - 1){
            if((dist[x+ y*_width] > maxdist) || ((dist[x+ y*_width] = maxdist) && x < dest_x)){
                maxdist = dist[x+ y*_width];
                dest_x = x;
                dest_y = y;
            }
            
        }

        if(canTravel(x, y, 0) && !visited[x + 1 + y*_width]){
            curpath.push_back(x + 1 + y*_width);
            visited[x + 1 + y*_width] = true;
            previous[x + 1 + y*_width] = x+ y*_width;
            dist[x + 1 + y*_width] = dist[x + y*_width] + 1;
        }

        if(canTravel(x, y, 1) && !visited[x + (y + 1)*_width]){
            curpath.push_back(x + (y + 1)*_width);
            visited[x + (y + 1)*_width] = true;
            previous[x + (y + 1)*_width] = x+ y*_width;
            dist[x + (y + 1)*_width] = dist[x + y*_width] + 1;
        }

        if(canTravel(x, y, 2) && !visited[x - 1 + y*_width]){
            curpath.push_back(x - 1 + y*_width);
            visited[x - 1 + y*_width] = true;
            previous[x - 1 + y*_width] = x+ y*_width;
            dist[x - 1 + y*_width] = dist[x + y*_width] + 1;
        }

        if(canTravel(x, y, 3) && !visited[x + (y - 1)*_width]){
            curpath.push_back(x + (y - 1)*_width);
            visited[x + (y - 1)*_width] = true;
            previous[x + (y - 1)*_width] = x+ y*_width;
            dist[x + (y - 1)*_width] = dist[x + y*_width] + 1;
        }

    }

    int dest = dest_x + dest_y * _width;
    vector<int> traversal;
    while(previous[dest] != -1){
        traversal.push_back(dest);
        dest = previous[dest];
    }
    traversal.push_back(0);
    std::reverse(traversal.begin(), traversal.end());

    for(int i = 0; i < int(traversal.size()-1); i++){
        if(traversal[i+1] == traversal[i] + 1){
            solution.push_back(0);
        }
        else if(traversal[i+1] == traversal[i] + _width){
            solution.push_back(1);
        }
        else if(traversal[i+1] == traversal[i] - 1){
            solution.push_back(2);
        }
        else if(traversal[i+1] == traversal[i] - _width){
            solution.push_back(3);
        }
    }
    return solution;
 }

PNG* SquareMaze::drawMaze() const{
    PNG * retval = new PNG(_width * 10 + 1, _height * 10 + 1);
    for (int x = 0; x < _width; x++){
        for (int y = 0; y < _height; y++){
            if(y == 0){
                for(int k = 0; k < 10; k++){
                    if((10 * x + k < 1) || (10 * x + k > 9)){
                        retval->getPixel(10 * x + k, 0).l = 0;
                    }
                }
            }
            if(x == 0){
                for(int k = 0; k < 10; k++){
                    retval->getPixel(0, 10 * y + k).l = 0;
                }
            }
            if(canTravel(x,y,0) == false){
                for(int k = 0; k <= 10; k++){
                    retval->getPixel(10 * (x + 1), 10 * y + k).l = 0;
                }
            }
            if(canTravel(x,y,1) == false){
                for(int k = 0; k <= 10; k++){
                    retval->getPixel(10 * x + k, 10 * (y + 1)).l = 0;
                }
            }
        }
    }
    return retval;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG * maze = drawMaze();
    vector<int> path = solveMaze();
    HSLAPixel red (0,1,0.5,1);
    int bx = 0;
    int by = 0;
    int x = 5;
    int y = 5;

    for(auto it = path.begin(); it != path.end(); it++){
        switch (*it)
        {
        case 0:
            for(int k =0; k < 10; k++){
                maze->getPixel(x,y) = red;
                x++;  
            }
            bx++;
            break;
        case 1:
            for(int k =0; k < 10; k++){
                maze->getPixel(x,y) = red;
                y++;
                
            }
            by++;
            break;
        case 2:
            for(int k =0; k < 10; k++){
                maze->getPixel(x,y) = red;
                x--;
                
            }
            bx--;
            break;
        case 3:
            for(int k =0; k < 10; k++){
                maze->getPixel(x,y) = red;
                y--;
                
            }
            by--;
            break;
        default:
            break;
        }
    }

    maze->getPixel(x,y) = red;
    //std::cout<<bx<< " "<<by<<std::endl;
    for(int k = 1; k <= 9; k++){
        maze->getPixel(bx * 10 + k, (by + 1) * 10).l = 1;
    }
    
    return maze;
}


