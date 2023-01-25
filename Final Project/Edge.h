#pragma once

#include "Vertex.h"

class Edge
{
private:
    Vertex * src;
    Vertex * des;
    double distance;
    
    double convertToRadian(double);

public:
    Edge();
    Edge(Vertex * a, Vertex * b);
    ~Edge();
    Vertex * getVertexSrc();
    Vertex * getVertexDes();
    double getDis();
    double getEdgeWeight(double lat1, double lat2, double long1, double long2);
    //double getDis(Vertex a, Vertex b);
};

