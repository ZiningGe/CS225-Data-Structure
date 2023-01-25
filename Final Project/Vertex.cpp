#include "Vertex.h"

/**
 * default constructor of vertex
 */
Vertex::Vertex() {
    id = 0;
    latitude = 0;
    longitude = 0;
}

/**
 * copy constructor of vertex
 */
Vertex::Vertex(Vertex& other) {
    id = other.getID();
    latitude = other.getLat();
    longitude = other.getLong();
}

/**
 * custom constructor of vertex
 *
 * @param coordinates pair of the coordinates of the Vertex
 * @param index the id of the vertex
 */
Vertex::Vertex(std::pair<double, double> coordinate, int index) {
    id = index;
    latitude = coordinate.first;
    longitude = coordinate.second;
}

/**
 * operator= of vertex
 *
 * @param other the Vertex to be assigned  
 * @return Vertex the copied vertex
 */
Vertex Vertex::operator=(Vertex other){
    id = other.getID();
    latitude = other.getLat();
    longitude = other.getLong();
    return *this;
}

/**
 * get the id of vertex
 *
 * @return id 
 */
int Vertex::getID(){
    return id;
}

/**
 * get latitude of vertex
 *
 * @return latitude
 */
double Vertex::getLat() {
    return latitude;
}

/**
 * get longitude of vertex
 *
 * @return longitude;
 */
double Vertex::getLong() {
    return longitude;
}

