// Your code starts here //

#include "Graph.h"

using namespace std;

/**
 * default constructor of Graph
 */
Graph::Graph() {

}

/**
 * custom constructor of Graph
 *
 * @param vertices vector of vertices to be inserted
 */
Graph::Graph(vector<Vertex*> vertices){

    vector<Vertex*> tempVe;
    
    for (size_t i = 0; i < vertices.size(); i++) {
        Vertex * temp = new Vertex(*vertices[i]);
        tempVe.push_back(temp);
        insertVertex(temp);
    }

    idmap = new map<int, Vertex *>();
    visited = new map<Vertex*, bool>();
    parents_ = new std::map<Vertex*, Vertex*>;
    tent_ = new std::map<Vertex*, double>; // add tent_ attribute to the graph class;
    buckets_ = new std::vector< std::map<Vertex*, double>* >; //add buckets_ attribute to the graph class;

    for (size_t i = 0; i < tempVe.size(); i++) {
        (*idmap)[tempVe[i]->getID()] = tempVe[i];
        (*visited)[tempVe[i]] = false;
        (*parents_)[tempVe[i]] = NULL;
        (*tent_)[tempVe[i]] = 0.0;
    }

}

/**
 * custom constructor of Graph 
 *
 * @param vertices vector of vertex pointers
 * @param edges verctor of edge pointers
 */
Graph::Graph(vector<Vertex*> vertices, vector<Edge*> edges) {
    idmap = new map<int, Vertex *>();
    visited = new map<Vertex*, bool>();
    parents_ = new std::map<Vertex*, Vertex*>;
    tent_ = new std::map<Vertex*, double>; // add tent_ attribute to the graph class;
    buckets_ = new std::vector< std::map<Vertex*, double>* >; //add buckets_ attribute to the graph class;

    vector<Vertex*> tempVe;

    for (size_t i = 0; i < vertices.size(); i++) {
        Vertex * temp = new Vertex(*vertices[i]);
        tempVe.push_back(temp);
        insertVertex(temp);
    }

    for (size_t i = 0; i < tempVe.size(); i++) {
        (*idmap)[tempVe[i]->getID()] = tempVe[i];
        (*visited)[tempVe[i]] = false;
        (*parents_)[tempVe[i]] = NULL;
        (*tent_)[tempVe[i]] = 0.0;
    }


    for (size_t i = 0; i < edges.size(); i++) {
        insertEdge(idmap->at(edges[i]->getVertexSrc()->getID()), idmap->at(edges[i]->getVertexDes()->getID()));
    }
}

/**
 * custom constructor of Graph 
 *
 * @param airport vector of vector informations (id, lat, long)
 * @param routes vector of edges (pairs of vertices)
 */
Graph::Graph(vector< pair< int , pair<double, double> > > airport, vector< pair<int, int> > routes) {
    idmap = new map<int, Vertex *>();
    visited = new map<Vertex*, bool>();
    parents_ = new std::map<Vertex*, Vertex*>;
    tent_ = new std::map<Vertex*, double>; // add tent_ attribute to the graph class;
    buckets_ = new std::vector< std::map<Vertex*, double>* >; //add buckets_ attribute to the graph class;


    vector<Vertex*> tempVe;

    for(auto it = airport.begin(); it != airport.end(); it++) {
        Vertex * v = new Vertex(it->second, it->first);
        insertVertex(v);
        tempVe.push_back(v);
    }

    for (size_t i = 0; i < tempVe.size(); i++) {
        (*idmap)[tempVe[i]->getID()] = tempVe[i];
        (*visited)[tempVe[i]] = false;
        (*parents_)[tempVe[i]] = NULL;
        (*tent_)[tempVe[i]] = 0.0;
    }

    for(auto it = routes.begin(); it != routes.end(); it++) {
        insertEdge((*idmap)[it->first], (*idmap)[it->second]);
    }
}


/**
 * destructor of Graph
 */
Graph::~Graph() {

    for (map<Edge *, pair<Vertex *, Vertex *> >::iterator it = edgeMap.begin(); it != edgeMap.end(); ++it) {
        delete it->first;
    } // delete all the edges

    for (map<Vertex *, vector<Edge *> >::iterator it2 = vmap.begin(); it2 != vmap.end(); ++it2) {
        delete it2->first;
    } // delete all the vertices

    // edgeMap.clear();
    // vmap.clear();
    // tent_->clear();
    // parents_->clear();
    if(buckets_ != NULL){
        for(vector< std::map<Vertex*, double>* >::iterator it = buckets_->begin(); it != buckets_->end(); ++it) {
            delete (*it);
        }
    }
    
    delete tent_;
    delete buckets_;
    delete parents_;
    delete idmap;
    delete visited;
    //buckets_->clear();



    

    // delete tent_ & buckets_ & parents_
    
}

/**
 * get Vertex function
 *
 * @param id the id of the Vertex
 * @return vertex pointer of that id
 */
Vertex * Graph::getVertex(int id) {
    return (*idmap)[id];
}

/**
 * insert vertex function
 *
 * @param v vertex pointer to be inserted
 */
void Graph::insertVertex(Vertex * v) {
    vmap[v] = {};
}

// void Graph::removeVertex(Vertex * v) {
//     std::vector<Edge *> Edges = vmap.at(v);
//     for(size_t i = 0 ; i < Edges.size(); i++) {
//         Vertex * temp; // connected vertex
//         if(v->getID() == Edges[i]->getVertexSrc()->getID()) {
//             temp = Edges[i]->getVertexDes();
//         } else {
//             temp = Edges[i]->getVertexSrc();
//         }

//         vector<Edge *> edges2 = vmap[temp];
//         for(size_t i = 0; i < edges2.size(); i++) {
//             if (edges2[i]->getVertexDes() == v || edges2[i]->getVertexSrc() == v)
//                 vmap[temp].erase(vmap[temp].begin()+i);
//         }
       
//         // for(vector<Edge *>::iterator it = vmap[temp].begin() ; it != vmap[temp].end(); ++it) {
//         //     if (it->getVertexDes() == v || it->getVertexSrc() == v)
//         //         vmap[temp].erase(it);
//         // }
//         Edge * tempEdge = Edges[i];
//         edgeMap.erase(Edges[i]);
//         delete tempEdge;
//     } // loop for every adjacent edge
//     Edges.clear();
//     Vertex * tempVer = v;
    
//     //v = NULL;
//     vmap.erase(v);
//     delete v;
// }

/**
 * insert edge function
 *
 * @param v one of vertex pointer that form the edge
 * @param w the other vertex pointer
 */
void Graph::insertEdge(Vertex * v, Vertex * w) {
    if(v == NULL || w == NULL){
        return;
    }
    if (areAdjacent(v, w)) {    return; } // link already existed
    Edge * newEdge = new Edge(v, w);
    vmap[v].push_back(newEdge);
    vmap[w].push_back(newEdge);
    edgeMap[newEdge] = {v, w};
}

void Graph::insertEdge(int id1, int id2) {
    insertEdge(idmap->at(id1), idmap->at(id2));
}

// void Graph::removeEdge(Vertex *v, Vertex *w) {
//     // vector<Edge *> Edgev = vmap->find(v);
//     // vector<Edge *> Edgew = vmap->find(w);
    
//     // Edge * e = new Edge(*v, *w);
//     // edgeMap->erase(e);
//     vector<Edge*> Edges = vmap.at(v);
//     for(size_t i = 0 ; i < Edges.size(); i++) {
//         Edge * temp = Edges[i];
//         if (temp->getVertexDes() == w || temp->getVertexSrc() == w)
            
//     }

// }

/**
 * get the incident edges of a vertex 
 *
 * @param v vertex pointer
 * @return vector of edges that are formed by this vertex
 */
std::vector<Edge * > Graph::incidentEdges(Vertex *v) {
    return vmap.at(v);
}

std::vector<Edge * > Graph::incidentEdges(int id) {
    return incidentEdges(idmap->at(id));
}

int Graph::sizeOfIncedentEdges(Vertex * v){
    return (int)vmap[v].size();
}

std::vector<Edge *> Graph::getAllEdges(){
    vector<Edge *> result;
    result.clear();
    for (auto it = edgeMap.begin(); it != edgeMap.end(); ++it) {
        result.push_back(it->first);
    }

    return result;
}

int Graph::getNumOfEdge() {
    return (int)edgeMap.size();
}

/**
 * get current tentative distance from source to vertex V
 *
 * @param V pointer to destination vertex
 * @return the distance from the source to vertex V
 */
double Graph::getTent(Vertex* V){
    return (*tent_)[V];
}

double Graph::getTent(int id){
    return getTent(idmap->at(id));
}

/**
 * check if two vertices are adjacent
 *
 * @param v vertex pointer
 * @param w the other vertex pointer
 * @return boolean value whether the two vertices are adjacent
 */
bool Graph::areAdjacent(Vertex *v, Vertex *w) {
   vector<Edge*> Edges = vmap.at(v);
    for(size_t i = 0 ; i < Edges.size(); i++) {
        Edge * temp = Edges[i];
        if (temp->getVertexDes() == w || temp->getVertexSrc() == w)
            return true;
    }

    return false;
}

bool Graph::areAdjacent(int id1, int id2) {
    return areAdjacent(idmap->at(id1), idmap->at(id2));
}

/**
 * Breath First Search of the Graph 
 *
 * @return a vector of all vertex pointers including all connected components
 */
std::vector<Vertex *> Graph::BFS(){
    std::vector<Vertex *> retval;
    //visited = new map<Vertex*, bool>();
    for(map<Vertex *, vector<Edge *> >::iterator it = vmap.begin(); it != vmap.end(); it++){
        visited->at(it->first) = false;
    }
    if(getVertex(0) != NULL){
        std::vector<Vertex *> zero_BFS = BFS_helper(getVertex(0));
        retval.insert(retval.end(), zero_BFS.begin(), zero_BFS.end());
    }

    for(map<Vertex *, vector<Edge *> >::iterator it = vmap.begin(); it != vmap.end(); it++){
        if((*visited)[it->first] == false) {
            std::vector<Vertex *> temp = BFS_helper(it->first);
            retval.insert(retval.end(), temp.begin(), temp.end());
        }
    }

    return retval;
}

/**
 * Breath First Search of the Graph
 *
 * @param source vertex pointer
 * @return vector of all vertex pointers that are in the connected component of source
 */
std::vector<Vertex *> Graph::BFS(Vertex * source) {
    if(source == NULL) {
        return vector<Vertex *>();
    }
    //std::vector<Vertex *> retval;
    //visited = new map<Vertex*, bool>();
    for(map<Vertex *, vector<Edge *> >::iterator it = vmap.begin(); it != vmap.end(); it++){
        (*visited)[it->first] = false;
    }

    return BFS_helper(source);
}

/**
 * Breath First Search helper function
 *
 * @param source vertex pointer
 * @return vector of all vertex pointers that are in the connected component of source
 */
std::vector<Vertex *> Graph::BFS_helper(Vertex* source){
    vector<Vertex *> traversal;
    
    std::queue<Vertex*> queue;
    queue.push(source);
    (*visited)[source] = true;

    while(!queue.empty()){
        Vertex* temp = queue.front();
        traversal.push_back(temp);
        queue.pop();
        for(vector<Edge*>::iterator it = vmap[temp].begin(); it != vmap[temp].end(); it++){
            Vertex* push_ = (*it)->getVertexSrc() == temp ? (*it)->getVertexDes() : (*it)->getVertexSrc();
            if((*visited)[push_] == false){
                queue.push(push_);
                (*visited)[push_] = true;
            }

        }
    }


    return traversal;
}

/**
 * Single Source Shortest Path
 *
 * @param src id of the source vertex
 * @param des id of the destination vertex
 * @param delta range of each bucket
 * @param Bnumber number of buckets
 * @return vector of the IDs of the vertices that represent the shortest path
 */
vector<int> Graph::SSSP(int src, int des, int delta, int Bnumber){
    Vertex * source = this->getVertex(src);
    Vertex* destination = this->getVertex(des);
    if(source == NULL || destination == NULL){
        return vector<int>();
    }
    // parents_ = new std::map<Vertex*, Vertex*>;
    // tent_ = new std::map<Vertex*, double>; // add tent_ attribute to the graph class;
    // buckets_ = new std::vector< std::map<Vertex*, double>* >; //add buckets_ attribute to the graph class;
    
    for (int i = 0; i < Bnumber; i++){
        std::map<Vertex*, double>* temp = new std::map<Vertex*, double>;
        buckets_->push_back(temp);
    }
    for(map<Vertex *, vector<Edge *> >::iterator it = vmap.begin(); it != vmap.end(); it++){
        (*tent_)[it->first] = std::numeric_limits<double>::max();
        (*parents_)[it->first] = NULL;
    }
    relax(source, 0, NULL, delta);
    while(isEmpty((*buckets_)) != -1){
    // print tent_  
    //     for(map<Vertex*, double>:: iterator it = tent_->begin(); it != tent_->end(); it++){
    //         cout<< it->first->getID() << " " << it->second << endl;
    //     }
        int index = isEmpty(*buckets_);
        std::map<Vertex*, double> temp;
        
        while(!(*buckets_)[index]->empty()){
            
            std::map<Vertex*, std::pair<double, Vertex*> > Req = findRequests(*(*buckets_)[index], true, delta);
            for(std::map<Vertex*, double> :: iterator it = (*buckets_)[index]->begin(); it != (*buckets_)[index]->end(); it++){
                temp[it->first] = it->second;
            }
            (*buckets_)[index]->clear();
            relaxRequests(Req, delta);

            Req = findRequests(temp, false, delta);
            relaxRequests(Req, delta);
        }
    }

    // std::map<Vertex*, std::pair<double, Vertex*> > retval;
    // for(map<Vertex *, vector<Edge *> >::iterator it = vmap.begin(); it != vmap.end(); it++){
    //     retval[it->first] = make_pair((*tent_)[it->first], (*parents_)[it->first]);
    // }
    std::vector<int> retval;
    retval.push_back(des);
    Vertex* curr = destination;
    while((*parents_)[curr] != NULL){
        retval.push_back((*parents_)[curr]->getID());
        curr = (*parents_)[curr];

    }
    std::reverse(retval.begin(), retval.end());
        return retval;
}

/**
 * check which bucket is the first non-empty bucket
 *
 * @param buckets vector of maps that have vertex pointer as the key and its tentative distance as the value
 * @return the index that indicates which bucket is empty
 */
int Graph::isEmpty(std::vector< std::map<Vertex*, double>* > Buckets){
    for(size_t i = 0; i < Buckets.size(); i++){
       if(!Buckets[i]->empty()){
           return i;
       }
    }
    return -1;
}

/**
 * find vector of heavy or light edges from a given bucket
 *
 * @param sources source map that have vertex pointer as the key and its tentative distance as the value
 * @param light help determine whether we want to find heavy or light edges
 * @param delta the range of the bucket
 * @return vector of heavy or light edges from the bucket
 */
std::map<Vertex*, std::pair<double, Vertex*> > Graph::findRequests(std::map<Vertex*, double> sources, bool light, int delta){
    std::map<Vertex*, std::pair<double, Vertex*> > Req;
    for(std::map<Vertex*, double>:: iterator it = sources.begin(); it != sources.end(); it++){
        for (std::vector<Edge *>::iterator it2 = vmap[it->first].begin(); it2 != vmap[it->first].end(); it2++){
            if(((*it2)->getDis() <= delta) == light){
                if((*it2)->getVertexSrc() != it->first) {
                    Req[(*it2)->getVertexSrc()]= make_pair((*tent_)[it->first] + (*it2)->getDis(), (*it2)->getVertexDes());
                } else {
                    Req[(*it2)->getVertexDes()] = make_pair((*tent_)[it->first] + (*it2)->getDis(), (*it2)->getVertexSrc());
                }    
            }
        }
    }
    return Req;
}

/**
 * relax all the edges from request
 *
 * @param request vector of heavy or light edges
 * @param delta range of the bucket
 */
void Graph::relaxRequests(std::map<Vertex*, std::pair<double, Vertex*> > Req, int delta){
    for(std::map<Vertex*, std::pair<double, Vertex*> >:: iterator it = Req.begin(); it != Req.end(); it++){
        relax(it->first, it->second.first, it->second.second, delta);
    }
}

/**
 * update bucket and tentative distance
 *
 * @param V vertex pointer
 * @param dis new shortest distance of V
 * @param S parent of V
 * @param delta range of the bucket
 */
void Graph::relax(Vertex* V, double dis, Vertex* S, int delta){
    // cout << "ID is " << V->getID() <<endl;
    // cout << "dist is " << dis <<endl;
    int original_ = (*tent_)[V] / delta;
    int new_ = dis / delta; 
    if(dis < (*tent_)[V]){
        //if in, remove from old bucket
        if(dis != 0 && (*tent_)[V] != std::numeric_limits<double>::max()){
            (*buckets_)[original_]->erase(V);
        } 
        //insert into new bucket
        (*(*buckets_)[new_])[V] = dis;  
        (*tent_)[V] = dis;
        (*parents_)[V] = S;

    }
}

/**
 * get the minimum distance of the vertex from the source vertex
 *
 * @param id the id of the vertex
 * @return the shortest distance of this vertex from the source
 */
double Graph::getMinDist(int id){
    if(getVertex(id) == NULL) {
        return -1;
    }
    return (*tent_)[getVertex(id)];
}


