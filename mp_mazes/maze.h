/* Your code here! */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>
#include <queue>
using cs225::PNG;
using cs225::HSLAPixel;

class SquareMaze{
    public:
        SquareMaze();
        ~SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
    private:
        struct wall{
            wall(bool right, bool down){
                _right = right;
                _down = down;
            }
            bool _right = true;
            bool _down = true;
        };
        int _width;
        int _height;
        vector<wall>* _maze;
        DisjointSets* _dset;
        void destroy();
    
};
