#include "../cs225/catch/catch.hpp"

#include <iostream>
#include <cmath>
#include <vector>

#include "../Graph.h"
#include "../Vertex.h"
#include "../fileio.h"

using namespace std;

// Graph build_graph_1(){
//     int count = 0;
//     vector<Vertex *> vertices;
//     for (int x = 0; x < 3; x++) {
//         for (int y = 0; y < 3; y++) {
//             Vertex * a = new Vertex({y, x}, count);
//             count++;
//             vertices.push_back(a);
//         }
//     }

//     Graph graph = Graph(vertices);


//     graph.insertEdge(vertices[0], vertices[1]);
//     graph.insertEdge(vertices[0], vertices[3]);
//     graph.insertEdge(vertices[0], vertices[4]);
//     graph.insertEdge(vertices[1], vertices[2]);
//     graph.insertEdge(vertices[1], vertices[4]);
//     graph.insertEdge(vertices[1], vertices[3]);
//     graph.insertEdge(vertices[1], vertices[5]);
//     graph.insertEdge(vertices[2], vertices[4]);
//     graph.insertEdge(vertices[2], vertices[5]);
//     graph.insertEdge(vertices[3], vertices[4]);
//     graph.insertEdge(vertices[4], vertices[5]);
//     graph.insertEdge(vertices[1], vertices[6]);
//     graph.insertEdge(vertices[1], vertices[7]);
//     graph.insertEdge(vertices[1], vertices[8]);

//     return graph;
// } 


TEST_CASE("Test_ADJ_Graph1", "[Graph]") {

    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);


    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());

    
    REQUIRE(graph.areAdjacent(vertices[4]->getID(), vertices[0]->getID()) == true);
    REQUIRE(graph.areAdjacent(vertices[1]->getID(), vertices[5]->getID()) == true);
    REQUIRE(graph.areAdjacent(vertices[0]->getID(), vertices[8]->getID()) == false);

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }

}

TEST_CASE("Test_IncidentEdge_Graph1", "[Graph]") {

    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);


    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());

    vector<Edge * > edges = graph.incidentEdges(vertices[4]->getID());

    REQUIRE(edges[0]->getVertexSrc()->getID() == 0);
    REQUIRE(edges[0]->getVertexDes()->getID() == 4);
    REQUIRE(edges[0]->getDis() == edges[0]->getEdgeWeight(edges[0]->getVertexSrc()->getLat(),
        edges[0]->getVertexDes()->getLat(), edges[0]->getVertexSrc()->getLong(), edges[0]->getVertexDes()->getLong()));

    REQUIRE(edges[1]->getVertexSrc()->getID() == 1);
    REQUIRE(edges[1]->getVertexDes()->getID() == 4);
    REQUIRE(edges[1]->getDis() == edges[1]->getEdgeWeight(edges[1]->getVertexSrc()->getLat(),
        edges[1]->getVertexDes()->getLat(), edges[1]->getVertexSrc()->getLong(), edges[1]->getVertexDes()->getLong()));

    REQUIRE(edges[2]->getVertexSrc()->getID() == 2);
    REQUIRE(edges[2]->getVertexDes()->getID() == 4);
    REQUIRE(edges[2]->getDis() == edges[2]->getEdgeWeight(edges[2]->getVertexSrc()->getLat(),
        edges[2]->getVertexDes()->getLat(), edges[2]->getVertexSrc()->getLong(), edges[2]->getVertexDes()->getLong()));

    REQUIRE(edges[3]->getVertexSrc()->getID() == 3);
    REQUIRE(edges[3]->getVertexDes()->getID() == 4);
    REQUIRE(edges[3]->getDis() == edges[3]->getEdgeWeight(edges[3]->getVertexSrc()->getLat(),
        edges[3]->getVertexDes()->getLat(), edges[3]->getVertexSrc()->getLong(), edges[3]->getVertexDes()->getLong()));
    
    REQUIRE(edges[4]->getVertexSrc()->getID() == 4);
    REQUIRE(edges[4]->getVertexDes()->getID() == 5);
    REQUIRE(edges[4]->getDis() == edges[4]->getEdgeWeight(edges[4]->getVertexSrc()->getLat(),
        edges[4]->getVertexDes()->getLat(), edges[4]->getVertexSrc()->getLong(), edges[4]->getVertexDes()->getLong()));

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
}

TEST_CASE("Test_DuplicatedEdge_Graph1", "[Graph]") {

    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);


    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());

    graph.insertEdge(vertices[5]->getID(), vertices[4]->getID());
    vector<Edge * > edges = graph.incidentEdges(vertices[4]->getID());

    REQUIRE(edges[0]->getVertexSrc()->getID() == 0);
    REQUIRE(edges[0]->getVertexDes()->getID() == 4);
    REQUIRE(edges[0]->getDis() == edges[0]->getEdgeWeight(edges[0]->getVertexSrc()->getLat(),
        edges[0]->getVertexDes()->getLat(), edges[0]->getVertexSrc()->getLong(), edges[0]->getVertexDes()->getLong()));

    REQUIRE(edges[1]->getVertexSrc()->getID() == 1);
    REQUIRE(edges[1]->getVertexDes()->getID() == 4);
    REQUIRE(edges[1]->getDis() == edges[1]->getEdgeWeight(edges[1]->getVertexSrc()->getLat(),
        edges[1]->getVertexDes()->getLat(), edges[1]->getVertexSrc()->getLong(), edges[1]->getVertexDes()->getLong()));

    REQUIRE(edges[2]->getVertexSrc()->getID() == 2);
    REQUIRE(edges[2]->getVertexDes()->getID() == 4);
    REQUIRE(edges[2]->getDis() == edges[2]->getEdgeWeight(edges[2]->getVertexSrc()->getLat(),
        edges[2]->getVertexDes()->getLat(), edges[2]->getVertexSrc()->getLong(), edges[2]->getVertexDes()->getLong()));

    REQUIRE(edges[3]->getVertexSrc()->getID() == 3);
    REQUIRE(edges[3]->getVertexDes()->getID() == 4);
    REQUIRE(edges[3]->getDis() == edges[3]->getEdgeWeight(edges[3]->getVertexSrc()->getLat(),
        edges[3]->getVertexDes()->getLat(), edges[3]->getVertexSrc()->getLong(), edges[3]->getVertexDes()->getLong()));
    
    REQUIRE(edges[4]->getVertexSrc()->getID() == 4);
    REQUIRE(edges[4]->getVertexDes()->getID() == 5);
    REQUIRE(edges[4]->getDis() == edges[4]->getEdgeWeight(edges[4]->getVertexSrc()->getLat(),
        edges[4]->getVertexDes()->getLat(), edges[4]->getVertexSrc()->getLong(), edges[4]->getVertexDes()->getLong()));

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
}


TEST_CASE("Test_BFS_Graph1", "[Graph]") {

    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);


    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());

    vector<Vertex *> vertices__ = graph.BFS(graph.getVertex(vertices[0]->getID()));

    vector<int> result;
    for (auto it = vertices__.begin(); it != vertices__.end(); it++){
        result.push_back((*it)->getID());
    }
    vector<int> solution = {0, 1, 3, 4, 2, 5, 6, 7, 8};

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
    
    REQUIRE(result == solution);
    

}

TEST_CASE("Test_BFS_Disconnected_Graph", "[Graph]") {
    vector<Vertex *> vertices2;
    
    Vertex * a = new Vertex({5, 3}, 0);
    Vertex * b = new Vertex({5, 6}, 1);
    Vertex * c = new Vertex({8, 6}, 2);
    Vertex * d = new Vertex({8, 7}, 3);
    Vertex * e = new Vertex({5, 0}, 4);
    Vertex * f = new Vertex({0, 0}, 5);
    Vertex * g = new Vertex({2, 3}, 6);
    vertices2.push_back(a);
    vertices2.push_back(b);
    vertices2.push_back(c);
    vertices2.push_back(d);
    vertices2.push_back(e);
    vertices2.push_back(f);
    vertices2.push_back(g);
    
    Graph graph2 = Graph(vertices2);


    graph2.insertEdge(vertices2[0]->getID(), vertices2[1]->getID());
    graph2.insertEdge(vertices2[1]->getID(), vertices2[2]->getID());
    graph2.insertEdge(vertices2[2]->getID(), vertices2[3]->getID());
    graph2.insertEdge(vertices2[0]->getID(), vertices2[3]->getID());
    graph2.insertEdge(vertices2[0]->getID(), vertices2[6]->getID());
    graph2.insertEdge(vertices2[0]->getID(), vertices2[4]->getID());
    //graph2.insertEdge(vertices2[4], vertices2[5]);

    vector<Vertex *> vertices__2 = graph2.BFS();
    vector<int> result;
    for (auto it = vertices__2.begin(); it != vertices__2.end(); it++){
        result.push_back((*it)->getID());
    }
    // for(size_t i = 0; i < vertices__2.size(); i++) {
    //     cout << vertices__2[i]->getID() << endl;
    // }
    
    for (auto it = vertices2.begin(); it != vertices2.end(); ++it) {
        delete (*it);
    }

    vector<int> solution = {0, 1, 3, 6, 4, 2, 5};
    REQUIRE(result == solution);

    

}

TEST_CASE("Test_SSSP_Simple_Graph1", "[Graph]") {
    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);
    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[6]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());
    
    vector<int> shortest_path = graph.SSSP(1, 2, 10, 15000);
    vector<int> solution = {1,2};
    REQUIRE(shortest_path == solution);
    vector<Edge * > edges = graph.incidentEdges(vertices[2]->getID());
    REQUIRE(graph.getTent(vertices[2]->getID()) == edges[0]->getEdgeWeight(edges[0]->getVertexSrc()->getLat(),
        edges[0]->getVertexDes()->getLat(), edges[0]->getVertexSrc()->getLong(), edges[0]->getVertexDes()->getLong()));

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
}

TEST_CASE("Test_SSSP_S2S_Graph1", "[Graph]") {
    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);
    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[6]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());
    
    vector<int> shortest_path = graph.SSSP(1, 1, 10, 15000);
    vector<int> solution = {1};
    REQUIRE(shortest_path == solution);
    REQUIRE(graph.getTent(1) == 0);

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
}

TEST_CASE("Test_SSSP_Complicated_Graph1", "[Graph]") {
    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);
    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[6]->getID());
    graph.insertEdge(vertices[6]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());

    vector<int> shortest_path2 = graph.SSSP(1, 7, 10, 15000);
    vector<int> solution2 = {1,3,6,7};
    REQUIRE(shortest_path2 == solution2);
    vector<Edge * > edge1 = graph.incidentEdges(vertices[1]->getID());
    vector<Edge * > edge2 = graph.incidentEdges(vertices[3]->getID());
    vector<Edge * > edge3 = graph.incidentEdges(vertices[6]->getID());
    
    double dis1 = edge1[3]->getEdgeWeight(edge1[3]->getVertexSrc()->getLat(),
        edge1[3]->getVertexDes()->getLat(), edge1[3]->getVertexSrc()->getLong(), edge1[3]->getVertexDes()->getLong());
    double dis2 = edge2[3]->getEdgeWeight(edge2[3]->getVertexSrc()->getLat(),
        edge2[3]->getVertexDes()->getLat(), edge2[3]->getVertexSrc()->getLong(), edge2[3]->getVertexDes()->getLong());
    double dis3 = edge3[1]->getEdgeWeight(edge3[1]->getVertexSrc()->getLat(),
        edge3[1]->getVertexDes()->getLat(), edge3[1]->getVertexSrc()->getLong(), edge3[1]->getVertexDes()->getLong());

    REQUIRE(graph.getTent(vertices[7]->getID()) == dis1 + dis2 + dis3);

    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
}


TEST_CASE("Test_SSSP_Disconnected_Graph1", "[Graph]") {

    //graph 1
    int count = 0;
    vector<Vertex *> vertices;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Vertex * a = new Vertex({y, x}, count);
            count++;
            vertices.push_back(a);
        }
    }

    Graph graph = Graph(vertices);


    graph.insertEdge(vertices[0]->getID(), vertices[1]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[0]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[2]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[3]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[2]->getID(), vertices[5]->getID());
    graph.insertEdge(vertices[3]->getID(), vertices[4]->getID());
    graph.insertEdge(vertices[4]->getID(), vertices[5]->getID());
    //graph.insertEdge(vertices[1], vertices[6]);
    graph.insertEdge(vertices[1]->getID(), vertices[7]->getID());
    graph.insertEdge(vertices[1]->getID(), vertices[8]->getID());

    vector<int> shortest_path = graph.SSSP(1, 6, 10, 15000);
    vector<int> solution = {6};
    REQUIRE(shortest_path == solution);
    REQUIRE(graph.getTent(vertices[6]->getID()) == numeric_limits<double>::max());
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        delete (*it);
    }
}

