#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

vector< pair< int , pair<double, double> > > readAirport(const char* fname);
vector< pair<int, int> > readRoutes(const char* fname);