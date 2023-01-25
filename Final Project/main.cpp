#include <iostream>
#include <cmath>
#include <vector>
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include "fileio.h"
#include "Layout.h"
#include <stdlib.h>
#include "Earth.h"



using namespace std;

int main(int argc, char** argv) {
    
    //graph 3

    char* input_airport_file = argv[1];
    char* input_routes_file = argv[2];
    char* output_dir = argv[3];
    int delta = atoi(argv[4]);
    int number_of_buckets = atoi(argv[5]);
    int source_ID = atoi(argv[6]);
    int des_ID = atoi(argv[7]);


    vector < pair< int , pair<double, double> > > airport = readAirport(input_airport_file);
    vector< pair<int, int> > routes = readRoutes(input_routes_file);
    Graph graph3 = Graph(airport, routes);

    cout << endl << "running BFS" << endl;
    vector<Vertex *> vertices__3 = graph3.BFS();
    //output
    char output_filename[10] = "BFS.txt";
    char output_dir_temp1[100];
    strcpy(output_dir_temp1, output_dir);
    char* output_dir_filename = strncat(output_dir_temp1, output_filename, 100);
    ofstream myfile (output_dir_filename);
    if (myfile.is_open())
    {
        myfile << "Number of airports: "<< vertices__3.size() << "\n\n";
        myfile << "Airport ID Traversal:\n";
        for(size_t i = 0; i < vertices__3.size(); i++) {
            myfile << vertices__3[i]->getID() << endl;
        }
        
        myfile.close();
        cout << "BFS.txt successfully saved" << endl;
    }
    else cout << "Unable to open file" << endl;


//testing SSSP
    cout << endl << "running SSSP" << endl;
    std::vector<int> shortest_path3 = graph3.SSSP(source_ID, des_ID, delta, number_of_buckets);

    char output_filename2[10] = "SSSP.txt";
    char output_dir_temp2[100];
    strcpy(output_dir_temp2, output_dir);
    char* output_dir_filename2 = strncat(output_dir_temp2, output_filename2, 100);
    ofstream myfile2 (output_dir_filename2);
    if (myfile2.is_open())
    {
        if(graph3.getMinDist(des_ID) == std::numeric_limits<double>::max()){
            myfile2 << "There is no shortest path from airport " << source_ID << " to airport " << des_ID << "\n";
        }
        else{
            myfile2 << "Source airports: "<< source_ID << "\n";
            myfile2 << "Destination airports: "<< des_ID << "\n\n";
            myfile2 << "Minimum distance:\n";
            myfile2 << graph3.getMinDist(des_ID) << " KM\n\n";
            myfile2 << "Shortest path:\n";
            for(auto it = shortest_path3.begin(); it != shortest_path3.end(); it++){
                 myfile2 << *it << " " ;
            }
        }
        cout << "SSSP.txt successfully saved" << endl;
        myfile2.close();
    }
    else cout << "Unable to open file" << endl;;

// sssp output image
    //vector< pair<int, int> > emptyroutes;
    Graph Visualgraph = Graph(graph3.BFS());
    for(size_t i = 0; i < shortest_path3.size()-1; i++){
        //cout<< shortest_path3[i] << " " << shortest_path3[i+1] << endl;
        Visualgraph.insertEdge(shortest_path3[i], shortest_path3[i+1]);
    }
    Earth land = Earth(&Visualgraph);
    cs225::PNG * visualization = land.draw();
    char output_filename5[30] = "SSSP visualization.png";
        char output_dir_temp5[100];
        strcpy(output_dir_temp5, output_dir);
        char* output_dir_filename5 = strncat(output_dir_temp5, output_filename5, 100);

        visualization->writeToFile(output_dir_filename5);



//running force directed graph with shrinked graph
    cout << endl << "running force directed graph" << endl;

    char output_filename3[10] = "FDG.txt";
    char output_dir_temp3[100];
    strcpy(output_dir_temp3, output_dir);
    char* output_dir_filename3 = strncat(output_dir_temp3, output_filename3, 100);
    ofstream myfile3 (output_dir_filename3);

    if (myfile3.is_open()) {
        Vertex * initialPoint = graph3.getVertex(source_ID);
        vector<Vertex *> verticesBFS = graph3.BFS(initialPoint);

        int num = 100; // number of vertices

        if ((int)verticesBFS.size() < num) {
            myfile3 << endl << "The graph cannot be drawn due to the lack of vertices." << endl;
            cout << "FDG.txt cannot be generated" << endl;
            myfile3.close();
            return 0;
        }
        verticesBFS.resize(num);


        
        myfile3 << "Number of Airports: " << verticesBFS.size() << endl;
        Graph fdg = Graph(verticesBFS);

        for (size_t in = 0; in < verticesBFS.size(); in++) {
            for (size_t in2 = 1; in2 < verticesBFS.size(); in2++) {
                if (graph3.areAdjacent(verticesBFS[in], verticesBFS[in2])) {
                    fdg.insertEdge(verticesBFS[in]->getID(), verticesBFS[in2]->getID());
                }
            }
        } //connect all the vertices;

        myfile3 << "Number of Routes: " << fdg.getNumOfEdge() << endl;

        ForceDirected outputFDG = ForceDirected(&fdg);

        cs225::PNG * outputImage = outputFDG.draw();

        char output_filename4[30] = "ForceDirectedGraph_Output.png";
        char output_dir_temp4[100];
        strcpy(output_dir_temp4, output_dir);
        char* output_dir_filename4 = strncat(output_dir_temp4, output_filename4, 100);

        outputImage->writeToFile(output_dir_filename4);
        myfile3 << endl <<  "The graph has been drawn" << endl;
        cout << "FDG.txt successfully saved" << endl << endl;
        myfile3.close();
    }
    else cout << "Unable to open file" << endl;

    return 0;
}