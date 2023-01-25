#include "fileio.h"

using namespace std;

/**
 * read airport data that has each aiport's ID, latitude, and longitude
 *
 * @param fname the filename of the data in txt
 * @return vector of the airports
 */
vector< pair< int , pair<double, double> > > readAirport(const char* fname){


    vector< pair< int , pair<double, double> > > airports;
    double arr[3];

    ifstream f;
    f.open(fname);
    if(!f.is_open()){
        cout << "unable to read the file" << endl;
        return vector< pair< int , pair<double, double> > >();
    }

    while(!f.eof()){
        
        for(int j = 0; j < 3; j++){
            f >> arr[j];
        }
        airports.push_back( make_pair(int(arr[0]), make_pair(arr[1], arr[2])) );
    }

    // for(int i = 0; i < airports.size(); i++){
    //         cout << airports[i].first << " " << airports[i].second.first << " " << airports[i].second.second << endl;
    // }
    f.close();
    
    return airports;
    
}

/**
 * read routes data that have the ids of two airports
 *
 * @param fname the filename of the data in txt
 * @return vector of the routes in format of pair of the ids of airports
 */
vector< pair<int, int> >  readRoutes(const char* fname){
    //read routes file
    //string name = "routes.txt";
    // cout<< fname << endl;
    // int n = fname.length();
    // char char_array[n+1];
    // strcpy(char_array, fname.c_str());

    vector< pair<int, int> > routes;
    int arr[2];

    ifstream f;
    f.open(fname);
    if(!f.is_open()){
        cout << "unable to read the file" << endl;
        return vector< pair<int, int> >();
    }

    
    while(!f.eof()){
        //cout << f << endl;
        for(int j = 0; j < 2; j++){
            f >> arr[j];
        }
        if(arr[0] != -1 && arr[1] != -1){
            routes.push_back( make_pair(arr[0], arr[1]) );
        }
    }

    // cout<< routes.size() << endl;
    // for(int i = 0; i < 67663; i++){
    //         cout << routes[i].first << " " << routes[i].second << endl;
    // }
    f.close();
    return routes;
    
}