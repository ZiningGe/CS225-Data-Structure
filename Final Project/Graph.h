// Your code starts here //

#pragma once

//#include <cstdarg>
#include <iostream>
//#include <stdexcept>
#include <cmath>
#include <vector>
#include<time.h>
//#include <list>
#include <stack>
#include <queue>
#include <map>
#include <utility>
#include <limits>

#include "Edge.h"
#include "Vertex.h"
#include <algorithm>

class Graph { 
     public:
        Graph();
        Graph(std::vector<Vertex*> vertices);
        Graph(std::vector<Vertex*> vertices, std::vector<Edge*> edges);
        Graph(std::vector< std::pair< int , std::pair<double, double> > >, std::vector< std::pair<int, int> >);
        ~Graph();
        void insertVertex(Vertex * v);
        //void removeVertex(Vertex * v);
        void insertEdge(Vertex * v, Vertex * w);
        void insertEdge(int id1, int id2);
        //void removeEdge(Vertex *v, Vertex *w);
        std::vector<Edge * > incidentEdges(Vertex *v);
        std::vector<Edge * > incidentEdges(int id);
        bool areAdjacent(Vertex *v, Vertex *w);
        bool areAdjacent(int, int);
        std::vector<Vertex *> BFS();
        std::vector<Vertex *> BFS(Vertex * source);
        std::vector<Vertex *> BFS_helper(Vertex* source);
        std::vector<int> SSSP(int src, int des, int delta, int Bnumber);
        
        std::map<Vertex*, std::pair<double, Vertex*> > findRequests(std::map<Vertex*, double> sources, bool light, int delta);
        void relaxRequests(std::map<Vertex*, std::pair<double, Vertex*> > Req, int delta);
        void relax(Vertex* V, double dis, Vertex* S, int delta);

        Vertex * getVertex(int id);
        double getMinDist(int id);
        int sizeOfIncedentEdges(Vertex * v);
        std::vector<Edge *> getAllEdges();
        int getNumOfEdge();
        double getTent(Vertex* V);
        double getTent(int);

        
        // void makeMaze(int w, int h);
        // bool canTravel(int x, int y, int dir);
        // bool canTravel(int index, int dir);
        // void setWall (int x, int y, int dir, bool exists);
        // vector<int> solveMaze();
        // cs225::PNG * drawMaze() const;
        // cs225::PNG * drawMazeWithSolution();
    private:
        std::map<Vertex *, std::vector<Edge *> > vmap;
        std::map<Edge *, std::pair<Vertex *, Vertex *> > edgeMap;
        std::map<int, Vertex *> * idmap;
        std::map<Vertex*, bool>  * visited;

        std::map<Vertex*, double> * tent_;
        std::vector< std::map<Vertex*, double>* > * buckets_;
        std::map<Vertex*, Vertex*> * parents_;
        int isEmpty(std::vector< std::map<Vertex*, double>* > Buckets);
};