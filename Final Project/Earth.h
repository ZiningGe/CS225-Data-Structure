#pragma once

#include <cmath>
#include <iostream>
#include "Graph.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
//#include "cs225/RGB_HSL.h"

class Earth {
    public:
        Earth();
        Earth(Graph *);
        ~Earth();
        cs225::PNG * draw();

    private:
        Graph * graph;
        cs225::PNG * landscape;
        std::vector<Vertex *> traversal;

        std::map <Vertex *, std::vector<double> > * position;
        void drawCircle(int x, int y, int r, int h);

        int width = 2000; // width of the output graph
        int height = 1100; // height of the output graph
        int marginal = 100; // marginals fo the output graph
        int N;

        /* variables that could be used */
        // double E = 2.1718281828; // natural number 

        double getDistance(double, double);
        long double getSlope(int, int, long double);

/* unused functions */
        // Vertex * findMaxPoint(Graph * base);
        // double getBearing(Vertex *, Vertex *);
        // double getDistance(Vertex *, Vertex *);
        // double convertToRadian(double num);
        // void convertToPNGCor();
};