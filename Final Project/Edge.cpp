
#include <cmath>
#include <iostream>
#include <utility>
#include "Edge.h"

#define PI 3.14159265357
#define R 6371 // earth Radius

/**
 * default edge constructor
 */
Edge::Edge() {
    src = new Vertex();
    des = new Vertex();
    distance = 0;
}

/**
 * custom edge contructor with two vertecies
 *
 * @param a the vertex forming the edge
 * @param b the other vertex 
 */
Edge::Edge(Vertex * a, Vertex * b)
{
    // if (a == NULL || b == NULL) {
    //     std::cout<<"null detected"<<std::endl;
    // }
    src = a;
    des = b;
    
    double lat1 = a->getLat();
    double lat2 = b->getLat();
    double long1 = a->getLong();
    double long2 = b->getLong();

    distance = getEdgeWeight(lat1, lat2, long1, long2);
    
    //fmin(abs(a->getLong() - b->getLong()))
}

/**
 * Get the source vertex
 *
 * @return Vertex * the source vertex
 */
Vertex * Edge::getVertexSrc() {
    return src;
}

/**
 * Get the destination vertex
 *
 * @return Vertex * the destination vertex
 */
Vertex * Edge::getVertexDes() {
    return des;
}

/**
 * desctructor of edge
 */
Edge::~Edge()
{
}

/**
 * get distance of the edge
 * 
 * @return distance 
 */
double Edge::getDis() {
    return distance;
}

/**
 * get the weight of the edge
 *
 * @param lat1 latitude of the first vertex
 * @param lat2 latitude of the second vertex
 * @param long1 longitude of the first vertex
 * @param long2 longitude of the second vertex
 * @return double weight of the edge
 */
double Edge::getEdgeWeight(double lat1_o, double lat2_o, double long1_o, double long2_o){
    double lat1 = convertToRadian(lat1_o);
    double lat2 = convertToRadian(lat2_o);
    double long1 = convertToRadian(long1_o);
    double long2 = convertToRadian(long2_o); // convert them to radian values

    double dlat = lat2 - lat1;
    double dlong = long2 - long1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    double result = 2 * atan2(sqrt(a), sqrt(1 - a));
    result *= R;
    return result;
}

/**
 * convert a doulbe to radian
 *
 * @param num the number to be passed in
 * @return radian mode of the num
 */
double Edge::convertToRadian(double num){
    return num * PI / 180;
}
