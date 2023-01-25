#include "Earth.h"

Earth::Earth(){

}

Earth::Earth(Graph * graph_input){
    landscape = new cs225::PNG(width, height);

    graph = graph_input;

    traversal = graph->BFS();

    N = traversal.size(); // number of vertices


    position = new std::map <Vertex *, std::vector<double> >;

    for (auto it = traversal.begin(); it != traversal.end(); ++it) {
            (*position)[*it] = {((*it)->getLong() + 180) * 5 + marginal, ((*it)->getLat() - 90) * (-5) + marginal};
    }

}

Earth::~Earth(){
    delete position;
    delete landscape;
}

void Earth::drawCircle(int xvalue, int yvalue, int r, int h){
    int xvalueLong = xvalue - r;
    int yvalueLat = yvalue - r;

    int hue = h;
    double lum = 0.5;


    // if (it == position->begin()) {
    //     hue = 23;
    //     lum = 0.2;
    //     //size = 40;
    // }

    for (int x = xvalueLong; x <= xvalueLong + 2 * r; x++) {
        for (int y = yvalueLat; y <= yvalueLat + 2 * r; y++) {
            if (getDistance(x - xvalue, y - yvalue) > r) {continue;}
            landscape->getPixel(x, y) = cs225::HSLAPixel(hue, 1, lum); 
        }
    }
}

cs225::PNG * Earth::draw(){


    for (auto it = position->begin(); it != position->end(); ++it) {

        double longx = it->second.at(0); // center x of the source point
        double laty = it->second.at(1); // center y of the source point

        drawCircle(longx, laty, 10, 200);

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

        drawCircle(src_x, src_y, 10, 0);
        drawCircle(des_x, des_y, 10, 0);

        if (src_x == des_x) {
                if (des_y >= src_y) {
                    for (int y = src_y; y <= des_y; y++) {
                            landscape->getPixel(src_x, y) = cs225::HSLAPixel(45, 0, 0);
                    }
                }
                else {
                    for (int y = src_y; y >= des_y; y--) {
                            landscape->getPixel(src_x, y) = cs225::HSLAPixel(45, 0, 0);
                    }
                }
        } // finishing drawing vertical lines

        else { // Y = aX + b



            long double a = ((long double)des_y - (long double)src_y) / ((long double)des_x - (long double)src_x);
            long double b = (long double)src_y - (a * (long double)src_x);

            int curr_x = src_x;
            int curr_y = src_y;

            while (curr_x <= des_x) {

                landscape->getPixel(curr_x, curr_y) = cs225::HSLAPixel(45, 0, 0);

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

    return landscape;
}

long double Earth::getSlope(int x, int y, long double y_intercept) {
    return ((long double)y - y_intercept) / ((long double)x);
}

double Earth::getDistance(double a, double b) {
    return sqrt(a * a + b * b);
}