#pragma once

#include <cmath>
#include <iostream>
#include "Graph.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"

class ForceDirected {
    public:
        ForceDirected();
        ForceDirected(Graph *);
        ~ForceDirected();
        double getRepForce(double, double);
        double getAttForce(double, double);
        void getDisplacement();
        cs225::PNG * draw();

    private:
        Graph * graph;
        cs225::PNG * forceDirected;
        std::map <Vertex *, std::vector<double> > * position;
        std::map <Vertex *, double > displacementX;
        std::map <Vertex *, double > displacementY;

        int width = 4000; // width of the output graph
        int height = 4000; // height of the output graph
        int marginal = 200; // marginals fo the output graph
        int iteration_multiplier = 5; // mutiplier for the main loop of displacement
        int N; // number of vertices
        int num_Edges; // number of edges
        int K; // force constant

        /* variables that could be used */
        // double E = 2.1718281828; // natural number 

        double getDistance(double, double);
        double inverseTime(int t);
        long double getSlope(int, int, long double);

/* unused functions */
        // Vertex * findMaxPoint(Graph * base);
        // double getBearing(Vertex *, Vertex *);
        // double getDistance(Vertex *, Vertex *);
        // double convertToRadian(double num);
        // void convertToPNGCor();
};