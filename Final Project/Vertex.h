#pragma once

#include <utility>

class Vertex {
    private: 
        double latitude;
        double longitude;
        int id;
    public:
    Vertex();
    Vertex(std::pair<double, double>, int);
    Vertex(Vertex& other);
    Vertex operator=(Vertex other);
    //bool operator ==(Vertex other);
    double getLat();
    double getLong();
    int getID();


    
};