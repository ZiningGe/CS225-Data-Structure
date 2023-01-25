#include "Layout.h"

ForceDirected::ForceDirected(){

}

ForceDirected::ForceDirected(Graph * graph_input){
    forceDirected = new cs225::PNG(width, height);

    graph = graph_input;

    std::vector<Vertex *> traversal = graph->BFS();

    N = traversal.size(); // number of vertices
    K = sqrt((width - marginal * 2) * (height - marginal * 2) / N); // force constant
    num_Edges = graph->getNumOfEdge(); // total number of edges

    position = new std::map <Vertex *, std::vector<double> >;
    for (auto it = traversal.begin(); it != traversal.end(); ++it) {
            (*position)[*it] = {(double)((width / 2) - (5 * N) + (rand() % (10*N))), (double)((height / 2) - (5 * N) + (rand() % (10*N)))};
    }

    getDisplacement();

}

ForceDirected::~ForceDirected(){
    delete position;
    delete forceDirected;
}

double  ForceDirected::getRepForce(double dx, double dy){

    double dist = getDistance(dx, dy);

    return K * K / dist;
}

double ForceDirected::getAttForce(double dx, double dy){

    double dist = getDistance(dx, dy);

    return dist * dist / K;
}

void ForceDirected::getDisplacement(){
    double x1;
    double x2;
    double y1;
    double y2;
    double dx;
    double dy;
    for (int t = 1; t < (int)(num_Edges * iteration_multiplier); t++) {

    
    for(auto it1 = position->begin(); it1 != position->end(); it1++) {

        displacementX[it1->first] = 0.0;
        displacementY[it1->first] = 0.0;

        for(auto it2 = position->begin(); it2 != position->end(); it2++) {
            if(it1->first == it2->first) {
                continue;
            } else {

                x1 = position->at(it1->first)[0];
                y1 = position->at(it1->first)[1];
                x2 = position->at(it2->first)[0];
                y2 = position->at(it2->first)[1];
                dx = x1 - x2;
                dy = y1 - y2;

                double dist = getDistance(dx, dy);

                displacementX[it1->first] += (dx / dist) * getRepForce(dx, dy);
                displacementY[it1->first] += (dy / dist) * getRepForce(dx, dy);
                   
            }      
        } // end of loop for second vertex
    }  // end of loop for all pairs of vertices

        std::vector<Edge *> tempt = graph->getAllEdges();
        for (auto edge = tempt.begin(); edge != tempt.end(); ++edge) {
            Vertex * src = (*edge)->getVertexSrc();
            Vertex * des = (*edge)->getVertexDes();
            x1 = position->at(src)[0];
            y1 = position->at(src)[1];
            x2 = position->at(des)[0];
            y2 = position->at(des)[1];
            dx = x1 - x2;
            dy = y1 - y2;

            double dist = getDistance(dx, dy);

            displacementX[src] -= (dx / dist) * getAttForce(dx, dy);
            displacementY[src] -= (dy / dist) * getAttForce(dx, dy);
            displacementX[des] += (dx / dist) * getAttForce(dx, dy);
            displacementY[des] += (dy / dist) * getAttForce(dx, dy);
            
        } //end of edge loop

    for(auto itVertex = position->begin(); itVertex != position->end(); itVertex++) {
        double lengthDisp = getDistance(displacementX[itVertex->first], displacementY[itVertex->first]);
        position->at(itVertex->first)[0] += displacementX[itVertex->first] * inverseTime(t) / lengthDisp;
        position->at(itVertex->first)[1] += displacementY[itVertex->first] * inverseTime(t) / lengthDisp;

        position->at(itVertex->first)[0] = fmin(width - marginal, fmax(marginal, position->at(itVertex->first)[0]));
        position->at(itVertex->first)[1] = fmin(height - marginal, fmax(marginal, position->at(itVertex->first)[1]));
    }

    } //end of iteration loop

}

double ForceDirected::inverseTime(int t){
    //return 1;
    double interations = (double)num_Edges * iteration_multiplier;
    return 1 - ((1 / interations / interations) * t * t);
    //return (interations - t) / interations;
    // return 1 - ((double)t/((double)num_Edges * iteration_multiplier));
    // return fmin(50/t, 1);
    // return (pow(E, -(t / 100)));
} 

cs225::PNG * ForceDirected::draw(){

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            forceDirected->getPixel(x, y) = cs225::HSLAPixel(2, 0, 1);
        }
    } // white background

    for (auto it = position->begin(); it != position->end(); ++it) {
        int size = graph->sizeOfIncedentEdges(it->first);

        double longx = it->second.at(0); // center x of the source point
        double laty = it->second.at(1); // center y of the source point

        int radius;
        radius = fmin(fmax(size, 15), 30);
        int xvalueLong = (int)longx - radius;
        int yvalueLat = (int)laty - radius;

        int hue = 0;
        double lum = 0.5;
        if (size > 25) {hue = 280;}
        else if (size > 20) {hue = 0;}
        else if (size > 15) {hue = 30;}
        else if (size > 10) {hue = 210;}
        else if (size > 5) {hue = 180;}
        else {hue = 135;}

        if (it == position->begin()) {
            hue = 23;
            lum = 0.2;
            //size = 40;
        }

        for (int x = xvalueLong; x <= xvalueLong + 2 * radius; x++) {
            for (int y = yvalueLat; y <= yvalueLat + 2 * radius; y++) {
                if (getDistance(x - longx, y - laty) > radius) {continue;}
                forceDirected->getPixel(x, y) = cs225::HSLAPixel(hue, 1, lum); 
            }
        }
    }
    // finish drawing circles

    // start drawing lines
    std::vector<Edge *> edges = graph->getAllEdges();

    for (auto itEdge = edges.begin(); itEdge != edges.end(); itEdge++) {
        Vertex * src = (*itEdge)->getVertexSrc();
        Vertex * des = (*itEdge)->getVertexDes();

        if (position->at(src)[0] > position->at(des)[0]) {std::swap(src, des);}

        int src_x = position->at(src)[0];
        int src_y = position->at(src)[1];
        int des_x = position->at(des)[0];
        int des_y = position->at(des)[1];

        if (src_x == des_x) {
                if (des_y >= src_y) {
                    for (int y = src_y; y <= des_y; y++) {
                        if (forceDirected->getPixel(src_x, y).h == 2) // white pixel
                            forceDirected->getPixel(src_x, y) = cs225::HSLAPixel(45, 0, 0);
                    }
                }
                else {
                    for (int y = src_y; y >= des_y; y--) {
                        if (forceDirected->getPixel(src_x, y).h == 2) // white pixel
                            forceDirected->getPixel(src_x, y) = cs225::HSLAPixel(45, 0, 0);
                    }
                }
        } // finishing drawing vertical lines

        else { // Y = aX + b
            long double a = ((long double)des_y - (long double)src_y) / ((long double)des_x - (long double)src_x);
            long double b = (long double)src_y - (a * (long double)src_x);

            int curr_x = src_x;
            int curr_y = src_y;

            while (curr_x <= des_x) {

                if (forceDirected->getPixel(curr_x, curr_y).h == 2){
                    forceDirected->getPixel(curr_x, curr_y) = cs225::HSLAPixel(45, 0, 0);
                } // encounter white pixel


                if (a <= 0) { // going uprightward
                    if (curr_y < des_y) {break;}
                    long double rightSlope = getSlope(curr_x + 1, curr_y, b);
                    long double upSlope = getSlope(curr_x, curr_y - 1, b);
                    if (abs(abs(rightSlope) - abs(a)) < abs(abs(upSlope) - abs(a))) {
                        curr_x++;
                        continue;
                    } //moving rightward
                    else if (abs(abs(rightSlope) - abs(a)) > abs(abs(upSlope) - abs(a))) {
                        curr_y--;
                        continue;
                    } //moving upward
                    else {
                        curr_x++;
                        curr_y--;
                        continue;
                    }
                } // going uprightward
                else { // going downrightward
                    if (curr_y > des_y) {break;}
                    long double rightSlope = getSlope(curr_x + 1, curr_y, b);
                    long double downSlope = getSlope(curr_x, curr_y + 1, b);
                    if (abs(abs(rightSlope) - abs(a)) < abs(abs(downSlope) - abs(a))) {
                        curr_x++;
                        continue;
                    } //moving rightward
                    else if (abs(abs(rightSlope) - abs(a)) > abs(abs(downSlope) - abs(a))) {
                        curr_y++;
                        continue;
                    } //moving downward
                    else {
                        curr_x++;
                        curr_y++;
                        continue;
                    }
                } // going downrightward
            }// finish while loop
        } // finishing drawing sloped line
    } // finish drawing lines

    return forceDirected;
}

long double ForceDirected::getSlope(int x, int y, long double y_intercept) {
    return ((long double)y - y_intercept) / ((long double)x);
}

double ForceDirected::getDistance(double a, double b) {
    return sqrt(a * a + b * b);
}

// unused functions

// get the bearing from -Pi to Pi
// double ForceDirected::getBearing(Vertex * origin, Vertex * destination){
//     double longO = origin->getLong();
//     longO = convertToRadian(longO);
//     double longDes = destination->getLong();
//     longDes = convertToRadian(longDes);

//     double dlat = destination->getLat() - origin->getLat();

//     if (dlat > 180) {dlat -= 360;}
//     else if (dlat < -180) {dlat += 360;}

//     dlat = convertToRadian(dlat);

//     double s = cos(longDes) * sin(dlat);
//     double c = cos(longO) * sin(longDes) - sin(longO) * cos(longDes) * cos(dlat);

//     return atan2(s, c);
// }

// double ForceDirected::getDistance(Vertex * a, Vertex * b) {
//     double latA = convertToRadian(a->getLat());
//     double latB = convertToRadian(b->getLat());
//     double longA = convertToRadian(a->getLong());
//     double longB = convertToRadian(b->getLong());

//     double dlat = latB - latA;
//     double dlong = longB - longA;
//     double v = pow(sin(dlat / 2), 2) + cos(latA) * cos(latB) * pow(sin(dlong / 2), 2);
//     double result = 2 * atan2(sqrt(v), sqrt(1 - v));
//     result *= 6378;
//     return result;
// }

// double ForceDirected::convertToRadian(double num){
//     return num * 3.14159265 / 180;
// }

// void ForceDirected::convertToPNGCor() {
//     for (auto it = position->begin(); it != position->end(); ++it) {
//         double xvalue = it->second.at(0);
//         double yvalue = it->second.at(1);
//         if (xvalue > 0) {xvalue = fmin(xvalue + width/2, width - marginal);}
//         else if (xvalue <= 0) {xvalue = fmax(xvalue + width/2, marginal);}
//         if (yvalue > 0) {yvalue = fmax((yvalue - height/2) * -1, marginal);}
//         else if (yvalue <= 0) {yvalue = fmin((yvalue - height/2) * -1, height - marginal);}
//         it->second = {xvalue, yvalue};
//     }

//     return;
// }